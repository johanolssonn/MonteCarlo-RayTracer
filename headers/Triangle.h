#ifndef TRIANGLE_H
#define TRIANGLE_H

#define EPSILON 0.00000000000000001

#include <vector>
#include "Definitions.h"
#include "ColorDbl.h"
#include "Ray.h"
struct Triangle {

	Triangle(const Vertex &p1, const Vertex &p2, const Vertex &p3, const ColorDbl &color, const Direction &normal);

	float rayIntersection(Ray &ray);

	const Direction getNormal() { return _normal; }
	const ColorDbl getColor() {return _color;}
	int getSurfaceType() { return _color._surfType; }


	const Vertex _p1;
	const Vertex _p2; 
	const Vertex _p3;
	const ColorDbl _color;
	const Direction _normal;
};

#endif //TRIANGLE_H