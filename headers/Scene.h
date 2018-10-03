#include "Vertex.h"
#include "ColorDbl.h"
#include "Triangle.h"
#include "Direction.h"

#include <vector>
class Scene {
public:
	Scene();
	~Scene() = default;

	void createScene();
private:

	std::vector<Triangle> triangle_list;

};