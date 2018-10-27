#include "Sphere.h"
#define EPSILON 0.00000000000000001

Sphere::Sphere(glm::vec3 center, float radius, ColorDbl color)
:_center{ center }, _radius{ radius }, _color{color}{};

float Sphere::getRadius() {
    return _radius;
}

glm::vec3 Sphere::getCenter() {
    return _center;
}

ColorDbl Sphere::getColor() {
    return _color;
}

float Sphere::sphereIntersection(Ray &r) {

    //GEOMETRIC SOLUTION

    float t0, t1; //solutions for t if the ray intersects

    // because _start is a vec4 :(
    glm::vec3 rayOrigin = r._start;

    // vector L from center point to start of ray
    glm::vec3 L = _center - rayOrigin;

    float t_ca = glm::dot(L, r._dir);

    //if t_ca is negative, it means that L and the rays direction points in opposite direction => no intersection
    if(t_ca < EPSILON) return INFINITY;

    float d = glm::sqrt(glm::dot(L,L) - glm::pow(t_ca,2));

    if(d < EPSILON) return INFINITY;


    // if d is greater than the sphere radius the ray misses the sphere => no intersection
    if(d > _radius) return INFINITY;


    float t_hc = sqrt(pow(_radius,2) - pow(d,2));
    t0 = t_ca - t_hc;
    t1 = t_ca + t_hc;


    if(t0 > t1) std::swap(t0,t1);

    if(t0 < EPSILON) {
        t0 = t1; //use t1 if t0 is negative
        if(t0 < EPSILON) return INFINITY; //both are negative, no intersection
    }

    return t0;

}