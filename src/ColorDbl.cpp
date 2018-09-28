#include "ColorDbl.h"

class ColorDbl {

    public: 

    ColorDbl(double r = 1.0, double g = 0.0, double b = 0.0)
            :_r{r},_g{g},_b{b}{}

    ~ColorDbl() = default;

    private: 

    double _r, _g, _b;

};