#include "ColorDbl.h"
#include "Ray.h"

class Pixel {
public:

	Pixel();
	Pixel(ColorDbl &color);
	~Pixel() = default;

	ColorDbl _color;
private:
	
	//std::vector<Ray> _rays;
};