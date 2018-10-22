#ifndef LIGHT_H
#define LIGHT_H

#include "Definitions.h"
#include "ColorDbl.h"
#include "Triangle.h"

#include <vector>


class Light {

public:

    Light();
    std::vector<Triangle> getLightTriangles();
	Direction getDirection() { return _dir; }

private:

    std::vector<Triangle> _lightTriangles;
	Direction _dir;


};


#endif LIGHT_H
