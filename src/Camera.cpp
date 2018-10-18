#include "Camera.h"

 Camera::Camera(bool useEyePoint1)
	 :	_useEyePoint1{useEyePoint1} {
	 
	 if (useEyePoint1)
		 _eyePoint = Vertex{ -2.0, 0.0, 0.0, 0.0 }; //e1
	 else
	 	 _eyePoint = Vertex{ -0.2, 0.0, 0.0, 0.0 }; //e2
 }
 
 ColorDbl Camera::trace(const Direction &rayorig, const Direction &raydir,const std::vector<Triangle> &triangles,const int &depth)
 {/*
	 //if (raydir.length() != 1) std::cerr << "Error " << raydir << std::endl;
	 float tnear = INFINITY;
	 const Triangle* triangle = NULL;
	 // find intersection of this ray with the triangles in the scene
	 for (unsigned i = 0; i < triangles.size(); ++i) {
		 float t0 = INFINITY, t1 = INFINITY;
		 if (triangles[i].intersect(rayorig, raydir, t0, t1)) {
			 if (t0 < 0) t0 = t1;
			 if (t0 < tnear) {
				 tnear = t0;
				 triangle = &triangles[i];
			 }
		 }
	 }*/
	 return ColorDbl();
 }

void Camera::render(Scene &scene) {

	std::vector<Triangle> triangles = scene.getTriangles();
	float fov = atan(1 / glm::length(_eyePoint)); // this gives fov/2 in radians
	std::cout << "fov = " << fov << std::endl;
	float scale = tan(fov);
	{
		for (int j = 0; j < HEIGHT; ++j) {
			for (int i = 0; i < WIDTH; ++i) {

				// generate primary ray
				float y = (1 - 2 * (i + 0.5) / (float)WIDTH)*scale;
				float z = (1 - 2 * (j + 0.5) / (float)HEIGHT)*scale;
				Vertex ray_origin = _eyePoint;
				Direction ray_dir = Direction{ 1.0, y,z } -Direction{ ray_origin };
				ray_dir = glm::normalize(ray_dir);
				Ray primary_ray(ray_origin, ray_dir);
				primary_ray._end = primary_ray._start + Vertex(primary_ray._dir, 0.0)*primary_ray.tMax;
				scene.findIntersectedTriangle(primary_ray);
				_pixelArray[j][i] = primary_ray._color;
				//std::cout << "primary_ray._color._r : " << primary_ray._color._r << std::endl;
			}
		}


		std::ofstream img("picture.ppm", std::ios::out | std::ios::binary);
		img << "P6\n" << WIDTH << " " << HEIGHT << "\n255\n";
		for (uint32_t  j = 0; j < HEIGHT; ++j){
			for (uint32_t  i = 0; i < WIDTH; ++i) {
				char r = (char)(255 * clamp(_pixelArray[j][i]._r, 0, 1));
				char g = (char)(255 * clamp(_pixelArray[j][i]._g, 0, 1));
				char b = (char)(255 * clamp(_pixelArray[j][i]._b, 0, 1));
				img << r<< g<< b;
			}
		}
		img.close();
		//delete[] _image;
	}
}

void Camera::createImage(Scene &scene)
{
	render(scene);
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