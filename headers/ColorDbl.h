#ifndef COLORDBL_H
#define COLORDBL_H
#include "Definitions.h"

const int LAMBERTIAN = 0, SPECULAR = 1, LIGHTSOURCE = 2;

class ColorDbl {

public:
	ColorDbl(); //DEfault white
	ColorDbl(double r, double g, double b); 
	ColorDbl(double r, double g, double b, const int surfType);
	~ColorDbl() = default;
	double _r, _g, _b;
	int _surfType;
private:
	
};

#endif //COLORDBL_H