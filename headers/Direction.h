#ifndef DIRECTION_H
#define DIRECTION_H

#include <math.h>
#include <iostream>
struct Direction {

	Direction(float x, float y, float z);
	~Direction() = default;

	friend std::ostream& operator<<(std::ostream& os, const Direction &d);
	float _x, _y, _z;
};

#endif //DIRECTION_H