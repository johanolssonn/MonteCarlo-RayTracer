#include "ColorDbl.h"


ColorDbl::ColorDbl() //Default white
{
	_r = 1.0;
	_g = 1.0;
	_b = 1.0;

}
ColorDbl::ColorDbl(double r, double g, double b)
	:_r{ r }, _g{ g }, _b{ b } 
{

}

ColorDbl::ColorDbl(double r, double g, double b,  int surfType)
	: _r{ r }, _g{ g }, _b{ b }, _surfType{surfType} {}

ColorDbl ColorDbl::reflect() {
    
    if(_surfType == LAMBERTIAN){
        return diffuse();
    }
    else if(_surfType == SPECULAR) {
        return specular();
    }
    
}

ColorDbl ColorDbl::specular() {
    
    return *this;
}

ColorDbl ColorDbl::diffuse() {
    return *this * reflectionCoefficient / M_PI; //divided by PI to ensure the surface doesnt reflect more light than it receives
}

std::ostream& operator<<(std::ostream& os, const ColorDbl &c)
{
    os << "Color = { " << c._r << ", " << c._g << ", " << c._b << " } " << std::endl;
    return os;
};

