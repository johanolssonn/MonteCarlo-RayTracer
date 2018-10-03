#ifndef RAY_H
#define RAY_H


#include "Definitions.h"
#include "ColorDbl.h"
#include <vector>
class Ray {
public:
	Ray(Vertex start, Vertex end, ColorDbl color);
	~Ray() = default;

	Vertex _start, _end;
	std::vector<Vertex> VERTS;
	ColorDbl _color;
	//Triangle *_triangle;

};

#endif //RAY_H