#include "Direction.h"

class Direction {

    public: 

    Direction(float x, float y, float z)
            :_x{x},_y{y},_z{z}{}

    ~Direction() = default;

    private: 

    float _x, _y, _z;

};