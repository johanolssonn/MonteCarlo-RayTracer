#include "Ray.h"

Ray::Ray()
{
	_start = Vertex(0.0);
	_dir = Direction(0);
}
Ray::Ray(Vertex &start, Direction &dir)
	:_start{ start }, _dir{ dir }
{
}

