#ifndef SCENE_H
#define SCENE_H

#include "Definitions.h"
#include "ColorDbl.h"
#include "Triangle.h"

#include <vector>
#include <list>
class Scene {
public:
	Scene();
	~Scene() = default;

	void createScene();

	Direction CalculateSurfaceNormal(const Vertex &p1, const Vertex &p2, const Vertex &p3) const;
	void findIntersectedTriangle(Ray &arg);
	std::vector<Triangle> getTriangles();
private:

	std::vector<Triangle> _triangleList;
	std::vector<Vertex> vertex_list;

};

#endif //SCENE_H