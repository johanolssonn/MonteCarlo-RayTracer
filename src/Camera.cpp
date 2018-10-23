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

void Camera::render(Scene &scene) {

	std::vector<Triangle> triangles = scene.getTriangles();
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
				//primary_ray._end = primary_ray._start + Vertex(primary_ray._dir, 0.0)*primary_ray.tMax;

				ColorDbl color;
				float a = scene.findIntersectedTriangle(primary_ray); //DIST TO TRIANGLE
				//std::cout << "a = " << a << std::endl;
				float b = scene.findIntersectedSphere(primary_ray, color); //DIST TO SPHERE
				if (a < b && a < INFINITY && primary_ray._triangle->getSurfaceType() != LIGHTSOURCE) // If a triangle is closer than any sphere.
				{
					Light lightSource = scene.getLight();
					//Direction L = -lightSource.getDirection();
					const Direction normal = primary_ray._triangle->getNormal(); //Triangle normal at intersection point

					Vertex hitPoint = primary_ray._end;
					Direction lightDir = glm::normalize(lightSource.getCenter() - glm::vec3(hitPoint));
					//std::cout << "lightDir: " << lightDir.x <<", "<< lightDir.y << ", " << lightDir.z << std::endl;
					//std::cout << "normal: " << normal.x << ", " << normal.y << ", " << normal.z << std::endl;
					//std::cout << "preHitpoint: " << hitPoint.x << ", " << hitPoint.y << ", " << hitPoint.z << std::endl;
					hitPoint += Vertex((float)0.01 * normal, 1.0);
					//std::cout << "postHitpoint: " << hitPoint.x << ", " << hitPoint.y << ", " << hitPoint.z << std::endl;
					Ray shadow_ray(hitPoint, lightDir); // Create a shadow ray with intersectionpoint as start and direction towards light as direction.
					//shadow_ray._end = hitPoint + Vertex(shadow_ray._dir, 1.0) *(float)10;
					//std::cout << "shadow_ray._end: " << shadow_ray._end.x << ", " << shadow_ray._end.y << ", " << shadow_ray._end.z << std::endl;
					float c = scene.findIntersectedTriangle(shadow_ray);
					const int intersectedTriangleType = shadow_ray.getColor()._surfType;
					if (intersectedTriangleType == LIGHTSOURCE)
					{
						color = primary_ray.getColor();
					}
					else color = ColorDbl(0.0, 0.0, 0.0);
					//color = primary_ray.getColor() / M_PI * lightIntensity*lightColor * std::max(0.f, glm::dot(N, L))/*;*/
					//color = primary_ray.getColor();

				}
				else if (b < a && b < INFINITY) //IF THE RAY HITS A SPHERE
				{
					primary_ray._triangle = nullptr;
				}
				else //IF THE RAY HITS A LIGHTSOURCE
				{
					color = primary_ray.getColor();
				}
			
				*_pixelBuffer = Pixel(color);
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