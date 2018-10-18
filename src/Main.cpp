#include <vector>
#include <iostream>
#include "Scene.h"
#include "Camera.h"
int main () {

	Scene sc;
	sc.createScene();
	Camera cam(false); // true => uses eyepoint1 (-2, 0, 0);
	cam.createImage(sc);



    return 0;
}
