//#include <vld.h> used to check memory leaks
#include <vector>
#include <iostream>
#include "Scene.h"
#include "Sphere.h"
#include "Camera.h"

int main () {

	Scene sc;
	Sphere sphere1 = Sphere(glm::vec3(-2.0f, 0.0f, 9.0f), 2.0f);

	sc.createScene();
	sc.addTetra(4.0, 2.0, 2.0, 2.0);
	sc.addSphere(sphere1);

	Camera cam(false); // true => uses eyepoint1 (-2, 0, 0);
	cam.createImage(sc);



    return 0;
}
