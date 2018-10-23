#include "ColorDbl.h"


ColorDbl::ColorDbl() //Default white
{
	_r = 1.0;
	_g = 1.0;
	_b = 1.0;
	//_surfType = LAMBERTIAN;
}
ColorDbl::ColorDbl(double r, double g, double b)
	:_r{ r }, _g{ g }, _b{ b } 
{
	//_surfType = LAMBERTIAN;
}

ColorDbl::ColorDbl(double r, double g, double b,  int surfType)
	: _r{ r }, _g{ g }, _b{ b }, _surfType{surfType} {}