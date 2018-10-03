#ifndef COLORDBL_H
#define COLORDBL_H

class ColorDbl {

public:
	ColorDbl(double r = 1.0, double g = 1.0, double b = 1.0); //DEfault white
	~ColorDbl() = default;

private:
	double _r, _g, _b;
};

#endif //COLORDBL_H