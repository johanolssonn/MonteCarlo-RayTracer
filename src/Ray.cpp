#include "Ray.h"

class Ray {

    public:
    Ray(Vertex start, Vertex end, ColorDbl color)
        :_start{start}, _end{end}, _color{color}
    {
        VERTS.push_back(start);
        VERTS.push_back(end);
        _triangle = end->triangle;
    }
    ~Ray() = default;
    
    Vertex _start, _end;
    std::vector<Vertex> VERTS;
    ColorDbl _color;
    Triangle &_triangle;

};