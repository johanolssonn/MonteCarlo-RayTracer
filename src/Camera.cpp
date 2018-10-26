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
	 std::random_device rd;
	 std::mt19937 gen(rd());
	 std::uniform_real_distribution<> dis(0.0, 1.0);

	 float fov = atan(1 / glm::length(_eyePoint)); // this gives fov/2 in radians
	 Light lightSource = scene.getLight();

	 float scale = tan(fov);
	 for (int j = 0; j < HEIGHT; ++j) {
		 for (int i = 0; i < WIDTH; ++i, ++_pixelBuffer) {

			 Pixel p;
			 for (int rr = 0; rr < _randomRays; rr++)
			 {
				 // generate primary ray
				 float rand1 = dis(gen);
				 float rand2 = dis(gen);
				 float y = (1 - 2 * (i + rand1) / (float)WIDTH)*scale;
				 float z = (1 - 2 * (j + rand2) / (float)HEIGHT)*scale;
				 Vertex ray_origin = _eyePoint;
				 Direction viewDirection(1.0, 0.0, 0.0);
				 Direction ray_dir = glm::normalize(viewDirection + glm::vec3(0.0, y, z));
				 Ray primary_ray(ray_origin, ray_dir);

				 p.addRay(primary_ray);
			 }
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
		 //finalColor = ColorDbl(sqrt(finalColor._r), sqrt(finalColor._g), sqrt(finalColor._b)) / _randomRays;
		 finalColor = finalColor / _randomRays;
		 _pixelBuffer->_color = finalColor;
		 _maxClr = glm::max(_maxClr, glm::max(finalColor._r, glm::max(finalColor._g, finalColor._b)));
	 }
	 _pixelBuffer = _pixelArray;

 }

 ColorDbl Camera::castRay(Scene &scene, Ray &ray, Light &lightSource, int depth) {
	ColorDbl clr(0.0, 0.0, 0.0);
	float closestIntersection = scene.findIntersection(ray); //DIST TO TRIANGLE
	const int intersectedSurfaceType = ray.getColor()._surfType;
	if(closestIntersection < INFINITY && intersectedSurfaceType == LIGHTSOURCE) //IF THE RAY HITS A LIGHTSOURCE
	{
		clr = ray.getColor();
	}
	else if (closestIntersection < INFINITY)
	{
		const Direction normal = ray._hitNormal; //Surface normal at intersection point
		Vertex hitPoint = ray._end; //Hitpoint on the intersected surface
		Ray out;
		if (intersectedSurfaceType == LAMBERTIAN)
		{
			out = sampleHemisphere(hitPoint, normal); //Gets a ray with random outgoing direction
			out._hitNormal = normal;
		}
		else //(intersectedSurfaceType == SPECULAR)
		{
			Direction R = reflectRay(ray._dir, normal); //get a reflection direction that is equal to incoming direction
			hitPoint += Vertex((float)0.01 * normal, 1.0);
			out = Ray(hitPoint, R);
		}

		float angle = glm::angle(out._dir, normal);
		ColorDbl emittance = ray.getColor().reflect() * cos(angle);
		clr = clr + emittance;

		//SHADOW RAY
		Direction lightDir = glm::normalize(lightSource.getCenter() - glm::vec3(hitPoint));
		hitPoint += Vertex((float)0.01 * normal, 1.0);
		Ray shadow_ray(hitPoint, lightDir); // Create a shadow ray with intersectionpoint as start and direction towards light as direction.
		ColorDbl lightIntensity = scene.getLightIntensity(hitPoint, normal, lightDir);
		float c = scene.findIntersection(shadow_ray);
		const int shadowSurfaceType = shadow_ray.getColor()._surfType;
		clr = (shadowSurfaceType == LIGHTSOURCE) ? clr*lightIntensity : ColorDbl(0.0, 0.0, 0.0);
		//clr = clr*lightIntensity;

		if (depth < MAXDEPTH)//|| russian roulette 
		{
			int nextDepth = (intersectedSurfaceType == SPECULAR) ? depth : depth + 1;
			clr = clr + castRay(scene, out, lightSource, nextDepth) * 0.8;
		}
	}
	return clr;
 }

 Direction Camera::reflectRay(Direction &I, const Direction &N)
 {
	 return I - 2 * glm::dot(I, N) * N;
 }

Ray Camera::sampleHemisphere(Vertex hitPos, glm::vec3 hitNormal){

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(0.0, 1.0);

	double rand1 = dis(gen);
	double rand2 = dis(gen);

	glm::vec3 helper = hitNormal + glm::vec3(1, 1, 1);
	glm::vec3 tangent = glm::normalize(glm::cross(hitNormal, helper));
	float inclination = acos(sqrt(rand1));
	float azimuth = 2 * M_PI * rand2;

	glm::vec3 random_direction = hitNormal;

	random_direction = glm::normalize(glm::rotate(
		random_direction,
		inclination,
		tangent));
	random_direction = glm::normalize(glm::rotate(
		random_direction,
		azimuth,
		hitNormal));

	return Ray(hitPos, random_direction);

}

void Camera::imageToFile()
{
	std::ofstream img("picture.ppm", std::ios::out | std::ios::binary); //Second argument is so that colors are correct on Windows.
	img << "P6\n" << WIDTH << " " << HEIGHT << "\n255\n";
	for (uint32_t i = 0; i < WIDTH* HEIGHT; ++i, ++_pixelBuffer) {
		ColorDbl clr = _pixelBuffer->_color;
		//char r = (char)(255 * Scene::clamp(clr._r, 0, 1));
		//char g = (char)(255 * Scene::clamp(clr._g, 0, 1));
		//char b = (char)(255 * Scene::clamp(clr._b, 0, 1));
		char r = (char)(255 * (clr._r / _maxClr));
		char g = (char)(255 * (clr._g / _maxClr));
		char b = (char)(255 * (clr._b / _maxClr));

		img << r << g << b;
	}
	img.close();
}

