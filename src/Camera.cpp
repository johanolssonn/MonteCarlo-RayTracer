#include "Camera.h"

 Camera::Camera(bool useEyePoint1)
	 :	_useEyePoint1{useEyePoint1} {
	 
	 if (useEyePoint1)
		 _eyePoint = Vertex{ -2.0, 0.0, 0.0, 0.0 }; //e1
	 else
	 	 _eyePoint = Vertex{ -1.0, 0.0, 0.0, 0.0 }; //e2
 }

 void Camera::createImage(Scene &scene)
 {
	 render(scene);
	 imageToFile();
 }
 bool Camera::trace(Ray &ray, std::vector<Triangle> &triangles)// , const int &depth)
 {
	 return true;
 }

 Direction Camera::reflect(Direction &I, const Direction &N)
 {
	 return I - 2 * glm::dot(I, N) * N;
 }

Ray Camera::sampleHemisphere(Vertex hitPos, glm::vec3 hitNormal){

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(0.0, 1.0);

    float rand1 = dis(gen);
    float rand2 = dis(gen);

    float theta = acos(sqrt(1.0 - rand1));
    float phi = 2.0 * M_PI * rand2;

    float xs = sin(theta) * cos(phi);
    float ys = cos(theta);
   	float zs = sin(theta) * sin(phi);

    glm::vec3 y = hitNormal;
    glm::vec3 h = y; //will be modified

    if(abs(h.x) <= abs(h.y) && abs(h.x) <= abs(h.z))
        h.x = 1.0;
    else if(abs(h.y) <= abs(h.x) && abs(h.y) <= abs(h.z))
        h.y = 1.0;
    else
        h.z = 1.0;

    glm::vec3 x = normalize(cross(h,y));
    glm::vec3 z = normalize(cross(h,y));

    Direction randDirection = glm::normalize(xs * x + ys * y + zs * z);
	//hitPos += Vertex((float)0.01 * hitNormal, 1.0);
    return Ray(hitPos, randDirection);

}

 ColorDbl Camera::castRay(Scene &scene, Ray &ray, Light &lightSource,  int depth) {

	 if (depth > MAXDEPTH) { return ray.getColor(); }
	 else
	 {
		 float a = scene.findIntersection(ray); //DIST TO TRIANGLE
		 //float b = scene.findIntersectedSphere(ray); //DIST TO SPHERE
		 //if (a < b && a < INFINITY && ray._triangle->getSurfaceType() == LAMBERTIAN) // If a triangle is closer than any sphere.
		 if (a < INFINITY && ray._color._surfType == LAMBERTIAN) // If a triangle is closer than any sphere.
		 {
			 const Direction normal = ray._hitNormal; //Triangle normal at intersection point
			 Vertex hitPoint = ray._end;
			 Direction lightDir = glm::normalize(lightSource.getCenter() - glm::vec3(hitPoint));
			 hitPoint += Vertex((float)0.01 * normal, 1.0);
			 Ray shadow_ray(hitPoint, lightDir); // Create a shadow ray with intersectionpoint as start and direction towards light as direction.

			 // RADIOSITY
			 Ray radioRay = sampleHemisphere(hitPoint, normal);

			 //std::cout << "ray: " << radioRay._dir.x << radioRay._dir.y << radioRay._dir.z;

			 float angle = glm::angle(radioRay._dir, normal);

			 //std::cout << "angle: " << angle;

			 //std::cout << "PreColor: " << ray.getColor();

			 //ColorDbl radioRayClr = castRay(scene, radioRay, lightSource, depth + 1);
			 ColorDbl emittance = ray.getColor().diffuse() * cos(angle);

			 //std::cout << "PostColor: " << ray.getColor();

			 //std::cout << "Emittance: " << emittance;

			 //double r = emittance._r, g = emittance._g, b = emittance._b;

			 ColorDbl lightIntensity = scene.getLightIntensity(hitPoint, normal, lightDir);
			 //std::cout << lightIntensity;
			 float c = scene.findIntersection(shadow_ray);
			 const int intersectedTriangleType = shadow_ray.getColor()._surfType;
			 if (intersectedTriangleType == LIGHTSOURCE)
			 {
				 return ray.getColor() * lightIntensity + emittance;
			 }
			 else {
				 return ColorDbl(0.0, 0.0, 0.0) + emittance; }
			 //color = primary_ray.getColor() / M_PI * lightIntensity*lightColor * std::max(0.f, glm::dot(N, L))/*;*/
			 //color = primary_ray.getColor();

		 }
		 else if (a < INFINITY && ray._color._surfType == SPECULAR)
		 {
			 //recursive
			 const Direction normal = ray._hitNormal; //Triangle normal at intersection point
			 Direction R = reflect(ray._dir, normal);
			 Vertex hitPoint = ray._end;
			 hitPoint += Vertex((float)0.01 * normal, 1.0);
			 Ray reflection_ray(hitPoint, R);
			 return castRay(scene, reflection_ray, lightSource, depth + 1)*(float)0.8;
		 }
		/* else if (b < a && b < INFINITY && ray._triangle->getSurfaceType() == LAMBERTIAN) //IF THE RAY HITS A SPHERE
		 {
			 ray._triangle = nullptr;
			 return ray.getColor();
		 }*/
		 else //IF THE RAY HITS A LIGHTSOURCE
		 {
			 return lightSource.getColor();
		 }
	 }
 }
void Camera::render(Scene &scene) {

	float fov = atan(1 / glm::length(_eyePoint)); // this gives fov/2 in radians
	std::cout << "fov = " << fov << std::endl;

	float scale = tan(fov);
		for (int j = 0; j < HEIGHT; ++j) {
			for (int i = 0; i < WIDTH; ++i, ++_pixelBuffer) {

				
				// generate primary ray
				float y = (1 - 2 * (i + 0.5) / (float)WIDTH)*scale;
				float z = (1 - 2 * (j + 0.5) / (float)HEIGHT)*scale;
				Vertex ray_origin = _eyePoint;
				Direction ray_dir = Direction{ 0.0, y,z } -Direction{ ray_origin };
				ray_dir = glm::normalize(ray_dir);
				Ray primary_ray(ray_origin, ray_dir);

				Light lightSource = scene.getLight();
				//ColorDbl color(0.0, 0.0, 0.0);
				ColorDbl finalColor = castRay(scene, primary_ray, lightSource, 0);

				finalColor /= (double)(3 * 2 * 2);
				double maximum = 0.0;
				maximum = glm::max(maximum, glm::max(finalColor._r, glm::max(finalColor._g, finalColor._b)));
				*_pixelBuffer = Pixel(finalColor);
			}
		}
		_pixelBuffer = _pixelArray; //Reset the buffer to beginning of _pixelArray
	
}

void Camera::imageToFile()
{
	std::ofstream img("picture.ppm", std::ios::out | std::ios::binary); //Second argument is so that colors are correct on Windows.
	img << "P6\n" << WIDTH << " " << HEIGHT << "\n255\n";
	for (uint32_t i = 0; i < WIDTH* HEIGHT; ++i, ++_pixelBuffer) {
		ColorDbl clr = _pixelBuffer->_color;
		char r = (char)(255 * Scene::clamp(clr._r, 0, 1));
		char g = (char)(255 * Scene::clamp(clr._g, 0, 1));
		char b = (char)(255 * Scene::clamp(clr._b, 0, 1));

		img << r << g << b;
	}
	img.close();
}

