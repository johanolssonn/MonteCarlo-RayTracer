#include "Definitions.h"
#include "Pixel.h"
#include "ColorDbl.h"
#include "Scene.h"
#include <array>
#include <fstream>
#include <random>

const int WIDTH = 400;
const int HEIGHT = 400;
const int MAXDEPTH = 2;

class Camera {
public:
	Camera(bool useEyePoint1 = true);
	~Camera() {
		delete [] _pixelArray;
	}
	bool trace(Ray &ray, std::vector<Triangle> &triangles);//,const int &depth);
	void render(Scene&);
	void createImage(Scene&);
	void imageToFile();
	ColorDbl castRay(Scene &scene, Ray &ray, Light &lightSource, int depth);
	Direction reflect(Direction &I, const Direction &N);
    Ray sampleHemisphere(Vertex hitPos, glm::vec3 hitNormal);

	Pixel *_pixelArray = new Pixel[WIDTH * HEIGHT];
	Pixel *_pixelBuffer = _pixelArray;

private: 
	
	bool _useEyePoint1;
	Vertex _eyePoint;
};