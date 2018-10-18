#ifndef COLORDBL_H
#define COLORDBL_H

class ColorDbl {

public:
	ColorDbl(); //DEfault white
	ColorDbl(double r, double g, double b); 
	~ColorDbl() = default;
	double _r, _g, _b;
private:
	
};

#endif //COLORDBL_H