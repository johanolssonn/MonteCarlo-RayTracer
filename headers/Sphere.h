#ifndef SPHERE_H
#define SPHERE_H

#include "Definitions.h"
#include "Ray.h"


class Sphere {

public:

    Sphere(glm::vec3 center, float radius, ColorDbl color);
    float sphereIntersection(Ray &r);
    float getRadius();
    glm::vec3 getCenter();
    ColorDbl getColor();

private:

    glm::vec3 _center;
    float _radius;
    ColorDbl _color;

};


#endif //SPHERE_H
