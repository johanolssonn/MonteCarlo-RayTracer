#ifndef COLORDBL_H
#define COLORDBL_H

class ColorDbl {

public:
	ColorDbl(); //DEfault white
	ColorDbl(double r, double g, double b); 
	~ColorDbl() = default;

private:
	double _r, _g, _b;
};

#endif //COLORDBL_H