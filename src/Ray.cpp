#include "Ray.h"


    Ray::Ray(Vertex &start, Direction &dir, ColorDbl color)
		:_start{ start }, _dir{ dir }, _color{ color }
    {
        //VERTS.push_back(start);
        //VERTS.push_back(end);
		//_triangle = end->triangle;
	}