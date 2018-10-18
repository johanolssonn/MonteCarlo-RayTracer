#ifndef RAY_H
#define RAY_H


#include "Definitions.h"
#include "ColorDbl.h"
#include <vector>

struct Triangle;

class Ray {
public:
	Ray(Vertex &start, Direction &dir);
	~Ray() = default;

	Vertex _start;
	Direction _dir;
	ColorDbl _color{};
	Vertex _end;
	Triangle* _triangle;
	float tMax = 20;
};

#endif //RAY_H