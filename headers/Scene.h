#include "Definitions.h"
#include "ColorDbl.h"
#include "Triangle.h"

#include <vector>
class Scene {
public:
	Scene();
	~Scene() = default;

	void createScene();

	Direction CalculateSurfaceNormal(const Vertex &p1, const Vertex &p2, const Vertex &p3) const;
private:

	std::vector<Triangle> triangle_list;

};