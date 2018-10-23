//#include <vld.h> used to check memory leaks
#include <vector>
#include <iostream>
#include "Scene.h"
#include "Sphere.h"
#include "Camera.h"
#include "Light.h"

int main () {

	Scene sc;
	Sphere sphere1 = Sphere(glm::vec3(4.0f, -2.0f, 0.0f), 1.0f, ColorDbl(0,1,0));

	sc.createScene();
	sc.addTetra(7.0, 3.0, 2.0, 2.0);

    Light light;
    sc.importTriangles(light.getLightTriangles());

	sc.addSphere(sphere1);

	//sc.logTrianglesTypes();
	//std::cout << "light direction : " << light.getDirection().x << ", " << light.getDirection().y << ", " << light.getDirection().z << "\n";

	Camera cam(false); // true => uses eyepoint1 (-2, 0, 0);
	cam.createImage(sc);


    return 0;
}
