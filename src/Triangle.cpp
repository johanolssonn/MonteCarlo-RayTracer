#include "Triangle.h"

Triangle::Triangle(
	const Vertex &p1, const Vertex &p2, const Vertex &p3,
	const ColorDbl &color,
	const Direction &normal)
	:_p1{ p1 }, _p2{ p2 }, _p3{ p3 }, _color{ color }, _normal{ normal } {};
