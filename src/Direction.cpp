#include "Direction.h"

Direction::Direction(float x, float y, float z)
	:_x{x},_y{y},_z{z}{}

void Direction::normalize()
{
	float norm_length = sqrt(_x*_x + _y*_y + _z*_z);
	_x = _x / norm_length;
	_y = _y / norm_length;
	_z = _z / norm_length;

};

std::ostream& operator<<(std::ostream& os, const Direction &d)
{
	os << "[ "<<d._x << ", " << d._y << ", " << d._z << " ] " << std::endl;
	return os;
};