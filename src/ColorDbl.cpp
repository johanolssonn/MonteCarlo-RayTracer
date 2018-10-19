#include "ColorDbl.h"


ColorDbl::ColorDbl() //Default white
{
	_r = 1.0;
	_g = 1.0;
	_b = 1.0;
}
ColorDbl::ColorDbl(double r, double g, double b)
	:_r{ r }, _g{ g }, _b{ b } {}

ColorDbl::ColorDbl(double r, double g, double b, const std::string surfType)
	: _r{ r }, _g{ g }, _b{ b }, _surfType{surfType} {}