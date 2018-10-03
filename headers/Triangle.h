#ifndef TRIANGLE_H
#define TRIANGLE_H
#include <vector>
#include "Vertex.h"
#include "ColorDbl.h"
#include "Direction.h"
struct Triangle {

	Triangle(const Vertex &p1, const Vertex &p2, const Vertex &p3, const ColorDbl &color, const Direction &normal);

	const Vertex _p1;
	const Vertex _p2; 
	const Vertex _p3;
	const ColorDbl _color;
	const Direction _normal;
};

#endif //TRIANGLE_H