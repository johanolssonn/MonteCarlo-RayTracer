#include "Vertex.h"

struct Vertex {

    Vertex(float x, float y, float z, float w = 1.0)
            :_x{x},_y{y},_z{z},_w{w}{}
    ~Vertex() = default;
    
    float _x, _y, _z, _w;
    Triangle *triangle;

    
};