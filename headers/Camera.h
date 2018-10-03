#include "Definitions.h"
#include "Pixel.h"
#include "ColorDbl.h"
#include "Triangle.h"
#include <vector>

class Camera {
public:
	Camera(Vertex eyePoint1, Vertex eyePoint2, bool useEyePoint1);
	~Camera() = default;

	Vertex _eyePoint1, _eyePoint2;
    bool _useEyePoint1;

    Pixel pixelArray[800][800];

private: 

    void render();
	

};