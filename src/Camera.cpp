#include "Camera.h"

double randZero_One()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(0.0, 1.0);

	return dis(gen);
}

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
	 Light lightSource = scene.getLight();
	 float fov = atan(1 / glm::length(_eyePoint)); // this gives fov/2 in radians
	 float scale = tan(fov);
	 float imageAspectRatio = WIDTH / (float)HEIGHT; // assuming width > height
	 
	 for (int j = 0; j < HEIGHT; ++j) {
		 for (int i = 0; i < WIDTH; ++i, ++_pixelBuffer) {

			 Pixel p;
			 for (int rr = 0; rr < _randomRays; rr++)
			 {
				 // generate primary ray
				 float rand1 = randZero_One();
				 float rand2 = randZero_One();
				 float y = (1 - 2 * (i + rand1) / (float)WIDTH)*scale * imageAspectRatio;
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
		 finalColor = finalColor / (double)_randomRays;
		 _pixelBuffer->_color = finalColor;

		 _maxClr = (finalColor.getTotal() > _maxClr.getTotal()) ? finalColor : _maxClr;
	 }
	 _pixelBuffer = _pixelArray; //Reset buffer

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
		ColorDbl emittance = ray.getColor().reflect() *cos(angle);
		clr = clr + emittance;

		//SHADOW RAY
		glm::vec3 lightPoint(lightSource.getRandomPoint());
		Direction lightDir = glm::normalize(lightPoint - glm::vec3(hitPoint));
		hitPoint += Vertex((float)0.01 * normal, 1.0);
		Ray shadow_ray(hitPoint, lightDir); // Create a shadow ray with intersectionpoint as start and direction towards light as direction.
		ColorDbl lightIntensity = scene.getLightIntensity(hitPoint, normal, lightPoint, lightDir);
		float c = scene.findIntersection(shadow_ray);
		const int shadowSurfaceType = shadow_ray.getColor()._surfType;
		clr = (shadowSurfaceType == LIGHTSOURCE) ? clr*lightIntensity : ColorDbl(0.0, 0.0, 0.0);

		double rusRoulette = glm::max(glm::max(emittance._r, emittance._g), emittance._b);
		if (depth < MAXDEPTH || randZero_One() < rusRoulette)
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

	double rand1 = randZero_One();
	double rand2 = randZero_One();

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

		char r = (char)(255 * (clr._r / _maxClr._r));
		char g = (char)(255 * (clr._g / _maxClr._g));
		char b = (char)(255 * (clr._b / _maxClr._b));
		
		img << r << g << b;
	}
	img.close();
}
