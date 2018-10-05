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
private:

	std::list<Triangle> triangle_list;
	std::list<Vertex> vertex_list;

};