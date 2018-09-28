#include "Ray.h"


    Ray::Ray(Vertex start, Vertex end, ColorDbl color)
        :_start{start}, _end{end}, _color{color}
    {
        VERTS.push_back(start);
        VERTS.push_back(end);
		//_triangle = end->triangle;
	}