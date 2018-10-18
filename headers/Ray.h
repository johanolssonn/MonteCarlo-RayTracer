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
	Vertex _end;
	ColorDbl _color;
	Triangle* _triangle;
	float tMax = 20;

	ColorDbl getColor() { return _color ;}
private:
	
};

#endif //RAY_H