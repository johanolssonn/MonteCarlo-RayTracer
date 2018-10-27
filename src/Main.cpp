//#include <vld.h> used to check memory leaks
#include <vector>
#include <iostream>
#include "Scene.h"
#include "Sphere.h"
#include "Camera.h"
#include "Light.h"

int main () {

	Scene sc;
	sc.createScene();

	// tetra
	sc.addTetra(4.0, 3.0, 3.0, 2.0);

    // spheres
	Sphere sphere1 = Sphere(glm::vec3(5.0f, -2.0f, -3.49f), 1.5f, ColorDbl(0,1,0));
	Sphere sphere2 = Sphere(glm::vec3(4.0f, 2.0f, 0.0f), 1.0f, ColorDbl(0,0,0, SPECULAR));
	sc.addSphere(sphere1);
	sc.addSphere(sphere2);

	Light light;
	sc.importTriangles(light.getLightTriangles());

	Camera cam(false); // true => uses eyepoint1 (-2, 0, 0);
	cam.createImage(sc);


    return 0;
}
