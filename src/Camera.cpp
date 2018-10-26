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

 void Camera::render(Scene &scene) {

	 generatePrimaryRays(scene);
	 castRays(scene);
 }

 void Camera::generatePrimaryRays(Scene &scene)
 {
	 float fov = atan(1 / glm::length(_eyePoint)); // this gives fov/2 in radians
	 Light lightSource = scene.getLight();

	 float scale = tan(fov);
	 for (int j = 0; j < HEIGHT; ++j) {
		 for (int i = 0; i < WIDTH; ++i, ++_pixelBuffer) {

			 Pixel p;
			 // generate primary ray
			 float y = (1 - 2 * (i + 0.5) / (float)WIDTH)*scale;
			 float z = (1 - 2 * (j + 0.5) / (float)HEIGHT)*scale;
			 Vertex ray_origin = _eyePoint;
			 Direction viewDirection(1.0, 0.0, 0.0);
			 Direction ray_dir = glm::normalize(viewDirection + glm::vec3(0.0, y, z));
			 Ray primary_ray(ray_origin, ray_dir);

			 p.addRay(primary_ray);

			 //finalColor /= (double)(3 * 2 * 2);
			 //double maximum = 0.0;
			 //maximum = glm::max(maximum, glm::max(finalColor._r, glm::max(finalColor._g, finalColor._b)));
			 *_pixelBuffer = p;
		 }
	 }
	 _pixelBuffer = _pixelArray; //Reset the buffer to beginning of _pixelArray
 }

 void Camera::castRays(Scene &scene)
 {

	 int count = 0, total = WIDTH * HEIGHT;
	 Light lightSource = scene.getLight();
	 for (int i = 0; i < WIDTH*HEIGHT; i++, ++_pixelBuffer, count++)
	 {
		 float progress = 100.0f * (float)count / total;
		 std::cout << "\r" << progress << "%";
		 ColorDbl finalColor(0.0, 0.0, 0.0);
		 for (Ray &r : _pixelBuffer->getRays())
		 {
			 finalColor = finalColor + castRay(scene, r, lightSource, 0);
		 }
		 _pixelBuffer->_color = finalColor;
	 }
	 _pixelBuffer = _pixelArray;

 }

 ColorDbl Camera::castRay(Scene &scene, Ray &ray, Light &lightSource, int depth) {

	 if (depth > MAXDEPTH) { return ray.getColor(); }
	 else
	 {
		 float closestIntersection = scene.findIntersection(ray); //DIST TO TRIANGLE
		 if (closestIntersection < INFINITY && ray._color._surfType == LAMBERTIAN) // If a triangle is closer than any sphere.
		 {
			 const Direction normal = ray._hitNormal; //Triangle normal at intersection point
			 Vertex hitPoint = ray._end;
			 Direction lightDir = glm::normalize(lightSource.getCenter() - glm::vec3(hitPoint));
			 hitPoint += Vertex((float)0.01 * normal, 1.0);
			 Ray shadow_ray(hitPoint, lightDir); // Create a shadow ray with intersectionpoint as start and direction towards light as direction.

												 // RADIOSITY
			 Ray radioRay = sampleHemisphere(hitPoint, normal);
			 float angle = glm::angle(radioRay._dir, normal);
			 ColorDbl radioRayClr = castRay(scene, radioRay, lightSource, depth + 1);
			 ColorDbl emittance = radioRayClr.diffuse() * cos(angle);
			 //ColorDbl emittance = ray.getColor().diffuse();

			 ColorDbl lightIntensity = scene.getLightIntensity(hitPoint, normal, lightDir);
			 float c = scene.findIntersection(shadow_ray);
			 const int intersectedTriangleType = shadow_ray.getColor()._surfType;
			 if (intersectedTriangleType == LIGHTSOURCE)
			 {
				 return ray.getColor() * lightIntensity + emittance;
			 }
			 else {
				 return ColorDbl(0.0, 0.0, 0.0) + emittance;
			 }

		 }
		 else if (closestIntersection < INFINITY && ray._color._surfType == SPECULAR)
		 {
			 //recursive
			 const Direction normal = ray._hitNormal; //Triangle normal at intersection point
			 Direction R = reflect(ray._dir, normal);
			 Vertex hitPoint = ray._end;
			 hitPoint += Vertex((float)0.01 * normal, 1.0);
			 Ray reflection_ray(hitPoint, R);
			 return castRay(scene, reflection_ray, lightSource, depth + 1).specular();
		 }
		 else //IF THE RAY HITS A LIGHTSOURCE
		 {
			 return lightSource.getColor();
		 }
	 }
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

