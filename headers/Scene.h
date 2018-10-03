#include "Vertex.h"
#include "ColorDbl.h"
#include "Triangle.h"
#include "Direction.h"

#include <vector>
#include <iostream>
#include <ostream>
class Scene {
public:
	Scene();
	~Scene() = default;

	void createScene();

	Direction CalculateSurfaceNormal(const Vertex &p1, const Vertex &p2, const Vertex &p3) const;
private:

	std::vector<Triangle> triangle_list;

};