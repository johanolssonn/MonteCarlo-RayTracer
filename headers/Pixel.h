#include "ColorDbl.h"
#include "Ray.h"
class Pixel {
public:

	Pixel();
	~Pixel() = default;

private:
	ColorDbl _color;
	//std::vector<Ray> _rays;
};