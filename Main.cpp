#include <vector>
#include <iostream>


//VERTEX

struct Vertex {

    Vertex(float x, float y, float z, float w = 1.0)
            :_x{x},_y{y},_z{z},_w{w}{}
    ~Vertex() = default;
    
    float _x, _y, _z, _w;
    Triangle *triangle;

    
};

//DIRECTION

class Direction {

    public: 

    Direction(float x, float y, float z)
            :_x{x},_y{y},_z{z}{}

    ~Direction() = default;

    private: 

    float _x, _y, _z;

};

//ColorDbl

class ColorDbl {

    public: 

    ColorDbl(double r = 1.0, double g = 0.0, double b = 0.0)
            :_r{r},_g{g},_b{b}{}

    ~ColorDbl() = default;

    private: 

    double _r, _g, _b;

};

//Ray

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

int main () {

    std::cout << "Oh lord";
    std::vector<int> ints;
    ints.push_back(5);
    return 0;
}
