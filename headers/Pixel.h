#include "ColorDbl.h"
#include "Ray.h"

class Pixel {
public:

	Pixel();
	Pixel(ColorDbl &color);
	~Pixel() = default;
	void addRay(Ray &ray) { _rays.push_back(ray); }
	std::vector<Ray> getRays() { return _rays; }

	ColorDbl _color;
private:
	
	std::vector<Ray> _rays;
};