#ifndef TRIANGLE_H
#define TRIANGLE_H
#include <vector>
#include "Vertex.h"
#include "ColorDbl.h"
#include "Direction.h"
class Triangle {

public:
	Triangle(const std::vector<Vertex> &pos, const ColorDbl &color, const Direction &normal);
private:
	std::vector<Vertex> _pos;
	ColorDbl _color;
	Direction _normal;
};

#endif //TRIANGLE_H