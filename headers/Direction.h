#ifndef DIRECTION_H
#define DIRECTION_H
class Direction {
public:

	Direction(float x, float y, float z);
	~Direction() = default;

private:
	float _x, _y, _z;
};

#endif //DIRECTION_H