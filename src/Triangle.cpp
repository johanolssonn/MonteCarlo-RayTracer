#include "Triangle.h"

Triangle::Triangle(
	const Vertex &p1, const Vertex &p2, const Vertex &p3,
	const ColorDbl &color,
	const Direction &normal)
	:_p1{ p1 }, _p2{ p2 }, _p3{ p3 }, _color{ color }, _normal{ normal } {};



float Triangle::rayIntersection(Ray &ray)
{
	glm::vec3 T = ray._start - _p1;
	glm::vec3 E1 = _p2 - _p1;
	glm::vec3 E2 = _p3 - _p1;
	glm::vec3 D = ray._end - ray._start;
	glm::vec3 P = glm::cross(D, E2);
	glm::vec3 Q = glm::cross(T, E1);

	float u = glm::dot(P, T) / glm::dot(P, E1);
	if (u < 0.0f || u > 1.0f)
	{ 
		return INFINITY;
	}

	float v = glm::dot(Q, D) / glm::dot(P, E1);
	if (v < 0.0f || u+v > 1.0f)
	{
		return INFINITY;
	}

	float t	 = glm::dot(Q, E2) / glm::dot(P, E1);
	if (t > EPSILON && t < 10000000.0f)
	{
		ray._end = ray._start + (ray._end - ray._start)*t;
		return t;
	}
	return false;
}