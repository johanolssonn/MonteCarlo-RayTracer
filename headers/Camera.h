#include "Definitions.h"
#include "Pixel.h"
#include "ColorDbl.h"
#include "Scene.h"
#include <array>
#include <fstream>

const int WIDTH = 50;
const int HEIGHT = 50;

class Camera {
public:
	Camera(bool useEyePoint1 = true);
	~Camera() = default;

	
	std::array<std::array <Pixel, WIDTH>, HEIGHT> _pixelArray;
    //Pixel pixelArray[800][800];
	
	ColorDbl trace(const Direction &rayorig, const Direction &raydir,const std::vector<Triangle> &triangles,const int &depth);
	void render(Scene&);
	void createImage(Scene&);
private: 

	double clamp(double v, double lo, double hi);

	bool _useEyePoint1;
	Vertex _eyePoint;
	//std::vector
	

};