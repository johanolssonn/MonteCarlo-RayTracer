#ifndef SPHERE_H
#define SPHERE_H

#include "Definitions.h"


class Sphere {

public:

    Sphere(glm::vec3 center, float radius); //, Surface surface);

private:

    glm::vec3 _center;
    float _radius;

};


#endif //SPHERE_H
