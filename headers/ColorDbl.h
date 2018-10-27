#ifndef COLORDBL_H
#define COLORDBL_H
#include "Definitions.h"

const int LAMBERTIAN = 0, SPECULAR = 1, LIGHTSOURCE = 2;

class ColorDbl {

public:
	ColorDbl(); //DEfault white
	ColorDbl(double r, double g, double b); 
	ColorDbl(double r, double g, double b, int surfType);
	~ColorDbl() = default;

	ColorDbl operator+(ColorDbl rhs) { return ColorDbl(_r + rhs._r, _g + rhs._g, _b + rhs._b); }
    ColorDbl operator-(ColorDbl rhs) { return ColorDbl(_r - rhs._r, _g - rhs._g, _b - rhs._b); }
	ColorDbl operator/(float x) { return ColorDbl(_r / x, _g / x, _b / x); }
	ColorDbl operator/=(double x) { return ColorDbl(_r / x, _g / x, _b / x); }
	ColorDbl operator*(float x) { return ColorDbl(_r * x, _g * x, _b * x); }
	ColorDbl operator*(ColorDbl rhs) { return ColorDbl(_r * rhs._r, _g * rhs._g, _b * rhs._b); }
    friend std::ostream& operator<<(std::ostream& os, const ColorDbl &c);

	double getTotal() {
		return _r + _g + _b;
	}
    
    ColorDbl reflect();
    ColorDbl specular();
    ColorDbl diffuse();


	

	double _r, _g, _b;
	int _surfType = LAMBERTIAN;
private:
    
    double reflectionCoefficient = 0.8;
	
};

#endif //COLORDBL_H
