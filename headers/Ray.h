#ifndef RAY_H
#define RAY_H


#include "Definitions.h"
#include "ColorDbl.h"
#include <vector>

struct Triangle;

class Ray {
public:
	Ray();
	Ray(Vertex &start, Direction &dir);
	~Ray() = default;



	ColorDbl getColor() { return _color; }

	Vertex _start;
	Direction _dir;
	Vertex _end;
	ColorDbl _color;
	Triangle* _triangle;
	Direction _hitNormal;
	float tMax = 20;


private:
	
};

#endif //RAY_H