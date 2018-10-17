#include "Definitions.h"
#include "Pixel.h"
#include "ColorDbl.h"
#include "Scene.h"
#include <array>
#include <fstream>

const int WIDTH = 800;
const int HEIGHT = 800;

class Camera {
public:
	Camera(bool useEyePoint1 = true);
	~Camera() = default;


	Pixel *_image = new Pixel[WIDTH * HEIGHT];
	Pixel *_pixel = _image;
	//std::array<std::array <Pixel, WIDTH>, HEIGHT> _pixelArray;
    //Pixel pixelArray[800][800];
	
	ColorDbl trace(const Direction &rayorig, const Direction &raydir,const std::vector<Triangle> &triangles,const int &depth);
	void render(Scene&);
	void createImage(Scene&);
private: 
	bool _useEyePoint1;
	Direction _eyePoint;
	

};