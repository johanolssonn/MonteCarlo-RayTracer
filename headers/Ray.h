#ifndef RAY_H
#define RAY_H


#include "Definitions.h"
#include "ColorDbl.h"
#include <vector>

struct Triangle;

class Ray {
public:
	Ray(Vertex &start, Direction &dir, ColorDbl color);
	~Ray() = default;

	Vertex _start;
	Direction _dir;
	ColorDbl _color;
	Vertex*_end;
	std::vector<Vertex> VERTS;
	Triangle* _triangle;
};

#endif //RAY_H