#include "Definitions.h"
#include "Pixel.h"
#include "ColorDbl.h"
#include "Scene.h"
#include <array>
#include <fstream>
#include <random>

const int WIDTH = 500;
const int HEIGHT = 500;
const int MAXDEPTH = 3;

class Camera {
public:
	Camera(bool useEyePoint1 = true);
	~Camera() {
		delete [] _pixelArray;
	}
	void createImage(Scene&);
	void render(Scene&);
	void generatePrimaryRays(Scene &scene);
	void castRays(Scene &scene);
	ColorDbl castRay(Scene &scene, Ray &ray, Light &lightSource, int depth);
	Direction reflectRay(Direction &I, const Direction &N);
    Ray sampleHemisphere(Vertex hitPos, glm::vec3 hitNormal);
	void imageToFile();


private:
	
	bool _useEyePoint1;
	Vertex _eyePoint;
	Pixel *_pixelArray = new Pixel[WIDTH * HEIGHT];
	Pixel *_pixelBuffer = _pixelArray;
	double _maxClr;
	int _randomRays = 7;
};
