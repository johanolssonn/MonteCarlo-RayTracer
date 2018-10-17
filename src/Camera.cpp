#include "Camera.h"

 Camera::Camera(bool useEyePoint1)
	 :	_useEyePoint1{useEyePoint1} {
	 
	 if (useEyePoint1)
		 _eyePoint = Direction{ -2.0, 0.0, 0.0 }; //e1
	 else
	 	 _eyePoint = Direction{ -1.0, 0.0, 0.0 }; //e2
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

	std::vector<Triangle> objects = scene.getTriangles();
	for (int j = 0; j < HEIGHT; ++j) {
		for (int i = 0; i < WIDTH; ++i, ++_pixel) {
			// generate primary ray (this is what this lesson is about)
			//...
			/*
			float tnear = INFINITY; // closest intersection, set to INFINITY to start with 
			for (int k = 0; k < objects.size(); ++k) {
				float t = INFINITY; // intersection to the current object if any 
				if objects[k]->intersect(pimaryRay, tnear) && t < tnear) {
				tnear = t;
				framebuffer = objects[k].color;
			}
			}
			*_pixel = current_ray._color;
		*/
		}
	}
    
}

void Camera::createImage(Scene &scene)
{
	render(scene);
}