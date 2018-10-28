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
	_color = white;

    _lightTriangles.push_back(Triangle(a, d, c, white, normal));
    _lightTriangles.push_back(Triangle(a, b, d, white, normal));

	_center = glm::vec3(5.0, 0.0, 4.99);

	_emission = ColorDbl(35.0, 35.0, 35.0);

	_area = glm::distance(a, b) * glm::distance(a, c);

}

std::vector<Triangle> Light::getLightTriangles() {
    return _lightTriangles;
}

glm::vec3 Light::getRandomPoint()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(0.0, 2.0);

	glm::vec3 randP(4.0 + dis(gen), 1.0 - dis(gen), 4.99);
	return randP;
}