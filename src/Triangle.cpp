#include "Triangle.h"

Triangle::Triangle(
	const std::vector<Vertex> &pos, 
	const ColorDbl &color = ColorDbl(0.0, 0.0, 0.0),
	const Direction &normal = Direction(0.0, 0.0, 0.0))
	:_pos{ pos }, _color{ color }, _normal{ normal } {};