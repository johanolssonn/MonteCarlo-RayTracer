#include "ColorDbl.h"
#include "Ray.h"
class Pixel {
public:

	Pixel();
	Pixel(ColorDbl &color);
	~Pixel() = default;

	double _r;
	double _g;
	double _b;
	ColorDbl _color;
private:
	
	//std::vector<Ray> _rays;
};