#include "Camera.h"

 Camera::Camera(bool useEyePoint1)
	 :	_useEyePoint1{useEyePoint1} {
	 
	 if (useEyePoint1)
		 _eyePoint = Vertex{ -2.0, 0.0, 0.0, 0.0 }; //e1
	 else
	 	 _eyePoint = Vertex{ -0.5, 0.0, 0.0, 0.0 }; //e2
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

 ColorDbl Camera::castRay(Scene &scene, Ray &ray, Light &lightSource, ColorDbl &clr,  int depth) {

	 if (depth > MAXDEPTH) { return clr; }
	 else
	 {
		 float a = scene.findIntersectedTriangle(ray); //DIST TO TRIANGLE
		 //float b = scene.findIntersectedSphere(ray); //DIST TO SPHERE
		 //if (a < b && a < INFINITY && ray._triangle->getSurfaceType() == LAMBERTIAN) // If a triangle is closer than any sphere.
		 if (a < INFINITY && ray._triangle->getSurfaceType() == LAMBERTIAN) // If a triangle is closer than any sphere.
		 {
			 const Direction normal = ray._triangle->getNormal(); //Triangle normal at intersection point
			 Vertex hitPoint = ray._end;
			 Direction lightDir = glm::normalize(lightSource.getCenter() - glm::vec3(hitPoint));
			 hitPoint += Vertex((float)0.01 * normal, 1.0);
			 Ray shadow_ray(hitPoint, lightDir); // Create a shadow ray with intersectionpoint as start and direction towards light as direction.
							
			 
			 float c = scene.findIntersectedTriangle(shadow_ray);
			 const int intersectedTriangleType = shadow_ray.getColor()._surfType;
			 if (intersectedTriangleType == LIGHTSOURCE)
			 {
				 return ray.getColor() * std::max(0.f, glm::dot(normal, lightDir));
			 }
			 else { return ColorDbl(0.0, 0.0, 0.0); }
			 //color = primary_ray.getColor() / M_PI * lightIntensity*lightColor * std::max(0.f, glm::dot(N, L))/*;*/
			 //color = primary_ray.getColor();

		 }
		 else if (a < INFINITY && ray._triangle->getSurfaceType() == SPECULAR)
		 {
			 //recursive
			 const Direction normal = ray._triangle->getNormal(); //Triangle normal at intersection point
			 Direction R = reflect(ray._dir, normal);
			 Vertex hitPoint = ray._end;
			 hitPoint += Vertex((float)0.01 * normal, 1.0);
			 Ray reflection_ray(hitPoint, R);
			 return clr + castRay(scene, reflection_ray, lightSource, clr, depth + 1)*(float)0.8;
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
				Direction ray_dir = Direction{ 1.0, y,z } -Direction{ ray_origin };
				ray_dir = glm::normalize(ray_dir);
				Ray primary_ray(ray_origin, ray_dir);

				Light lightSource = scene.getLight();
				ColorDbl color(0.0, 0.0, 0.0);
				*_pixelBuffer = Pixel(castRay(scene, primary_ray, lightSource, color, 0));
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
		char r = (char)(255 * clamp(clr._r, 0, 1));
		char g = (char)(255 * clamp(clr._g, 0, 1));
		char b = (char)(255 * clamp(clr._b, 0, 1));

		img << r << g << b;
	}
	img.close();
}

double Camera::clamp(double v, double lo, double hi)
{
	if (v < lo)
		return lo;

	else if (v > hi)
		return hi;
	
	else
		return v;
}