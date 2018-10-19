#ifndef COLORDBL_H
#define COLORDBL_H

#include <iostream>
using namespace std;
class ColorDbl {

public:
	ColorDbl(); //DEfault white
	ColorDbl(double r, double g, double b); 
	ColorDbl(double r, double g, double b, const std::string surfType);
	~ColorDbl() = default;
	double _r, _g, _b;
	string _surfType;
private:
	
};

#endif //COLORDBL_H