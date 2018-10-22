#ifndef LIGHT_H
#define LIGHT_H

#include "Definitions.h"
#include "ColorDbl.h"
#include "Triangle.h"
#include "Scene.h"

#include <vector>


class Light {

public:

    Light();
    std::vector<Triangle> getLightTriangles();

private:

    std::vector<Triangle> _lightTriangles;


};


#endif LIGHT_H
