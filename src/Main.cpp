//#include <vld.h> used to check memory leaks
#include <vector>
#include <iostream>
#include "Scene.h"
#include "Sphere.h"
#include "Camera.h"
#include "Light.h"

int main () {

	Scene sc;
	Sphere sphere1 = Sphere(glm::vec3(0.0f, 0.0f, 0.0f), 0.2f);

	sc.createScene();
	sc.addTetra(4.0, 2.0, 2.0, 2.0);

    Light light;
    sc.importTriangles(light.getLightTriangles());

	//sc.addSphere(sphere1);

	Camera cam(false); // true => uses eyepoint1 (-2, 0, 0);
	cam.createImage(sc);



    return 0;
}
