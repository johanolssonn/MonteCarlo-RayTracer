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
	glm::vec3 getCenter() { return _center; }
	ColorDbl getColor() { return _color; }
	ColorDbl getEmission() { return _emission; }
	double getLightArea() { return _area; }

private:

    std::vector<Triangle> _lightTriangles;
	Direction _dir;
	glm::vec3 _center;
	ColorDbl _color;
	ColorDbl _emission;
	double _area;


};

#endif LIGHT_H