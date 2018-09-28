#include "Triangle.h"

class Triangle {

   public:
   Triangle(const std::vector<Vertex> &pos,
            const ColorDbl &color = ColorDbl(),
            const Direction &normal = Direction(0.0, 0.0, 0.0) )
        :_pos{pos}, _color{color}, _normal{normal} {}

    std::vector<Vertex> _pos;
    ColorDbl _color;
    Direction _normal; 
};