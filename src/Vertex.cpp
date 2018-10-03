#include "Vertex.h"


Vertex::Vertex(float x, float y, float z, float w)
	: _x{ x }, _y{ y }, _z{ z }, _w{ w } {};

Vertex Vertex::operator - (const Vertex &v) const
{
	Vertex temp{0.0, 0.0, 0.0};
	temp._x = _x - v._x;
	temp._y = _y - v._y;
	temp._z = _z - v._z;
	return temp;
};