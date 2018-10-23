#include "Light.h"


Light::Light() {

    // (TOP VIEW)

    // a --------- b
    // |           |
    // |           |
    // c --------- d



    const Vertex a{ 4.0, 1.0, 4.99, 1.0 };
    const Vertex b{ 6.0, 1.0, 4.99, 1.0 };
    const Vertex c{ 4.0, -1.0, 4.99, 1.0 };
    const Vertex d{ 6.0, -1.0, 4.99, 1.0 };

    const Direction normal( 0.0, 0.0, -1.0 );
	_dir = normal;
    const ColorDbl white(1.0, 1.0, 1.0, LIGHTSOURCE);

    _lightTriangles.push_back(Triangle(a, d, c, white, normal));
    _lightTriangles.push_back(Triangle(a, b, d, white, normal));

	_center = glm::vec3(5.0, 0.0, 4.99);

}

std::vector<Triangle> Light::getLightTriangles() {
    return _lightTriangles;
}
