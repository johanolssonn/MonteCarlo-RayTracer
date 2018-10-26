#include "Scene.h"

Scene::Scene() {}

//(TOP VIEW)
//	        b(0,6)__________c(10,6)
//	      a(-3,0)/ 0     10  \ d(13,0)
//		  f(0,-6)\___________/e(10,-6)
//
//		Y	
//		|__ X
//   
//(SIDE VIEW)               <LEFT>
//	    g(-3,5) _____h(0,5)______i(10,5)______j(13,5)
//              |       |            |        |
//	 <BACK>     |       |            |        |		  <FRONT>
//	    n(-3,-5)|_______|____________|________|k(13,-5)
//                   m(0,-5)     l(10,-5)
//		Z					<RIGHT>
//		|__ X
//  
void Scene::createScene()
{
	const Vertex a_floor{ -3.0, 0.0, -5.0, 1.0 };
	const Vertex b_floor{ -0.0, 6.0, -5.0, 1.0 };
	const Vertex c_floor{ 10.0, 6.0, -5.0, 1.0 };
	const Vertex d_floor{ 13.0, 0.0, -5.0, 1.0 };
	const Vertex e_floor{ 10.0, -6.0, -5.0, 1.0 };
	const Vertex f_floor{ 0.0, -6.0, -5.0, 1.0 };
	const Vertex origo_floor{ 0.0, 0.0, -5.0, 1.0 };
	const Vertex origo10_floor{ 10.0, 0.0, -5.0, 1.0 };

	const Vertex a_ceiling{ -3.0, 0.0, 5.0, 1.0 };
	const Vertex b_ceiling{ -0.0, 6.0, 5.0, 1.0 };
	const Vertex c_ceiling{ 10.0, 6.0, 5.0, 1.0 };
	const Vertex d_ceiling{ 13.0, 0.0, 5.0, 1.0 };
	const Vertex e_ceiling{ 10.0, -6.0, 5.0, 1.0 };
	const Vertex f_ceiling{ 0.0, -6.0, 5.0, 1.0 };
	const Vertex origo_ceiling{ 0.0, 0.0, 5.0, 1.0 };
	const Vertex origo10_ceiling{ 10.0, 0.0, 5.0, 1.0 };


	const ColorDbl white(1.0, 1.0, 1.0); //Default constructor gives white color
	const ColorDbl red(1.0, 0.0, 0.0); 	//RIGHT WALL
	const ColorDbl green(0.0, 1.0, 0.0); //LEFT WALL
	const ColorDbl blue(0.0, 0.0, 1.0);	 //RIGHT BACK WALL
	const ColorDbl yellow(1.0, 1.0, 0.0); //LEFT BACK WALL
	const ColorDbl mirror(0.0, 0.0, 0.0, SPECULAR); //RIGHT FRONT WALL
	const ColorDbl orange(1.0, 0.65, 0.0); //LEFT FRONT WALL

	//FLOOR
	const Direction floor_norm( 0.0, 0.0, 1.0 );
	_triangleList.push_back(Triangle(a_floor, f_floor, b_floor, white, floor_norm));
	_triangleList.push_back(Triangle(b_floor, origo_floor, origo10_floor, white, floor_norm));
	_triangleList.push_back(Triangle(origo10_floor, c_floor, b_floor, white, floor_norm));
	_triangleList.push_back(Triangle(e_floor, d_floor, c_floor, white, floor_norm));
	_triangleList.push_back(Triangle(e_floor, origo10_floor, f_floor, white, floor_norm));
	_triangleList.push_back(Triangle(origo10_floor, origo_floor, f_floor, white, floor_norm));

	//CEILING
	const Direction ceiling_norm(0.0 ,0.0, -1.0);
	_triangleList.push_back(Triangle(a_ceiling, b_ceiling, f_ceiling, white, ceiling_norm));
	_triangleList.push_back(Triangle(b_ceiling, origo10_ceiling, origo_ceiling, white, ceiling_norm));
	_triangleList.push_back(Triangle(origo10_ceiling, b_ceiling, c_ceiling, white, ceiling_norm));
	_triangleList.push_back(Triangle(c_ceiling, d_ceiling, e_ceiling, white, ceiling_norm));
	_triangleList.push_back(Triangle(e_ceiling, f_ceiling, origo10_ceiling, white, ceiling_norm));
	_triangleList.push_back(Triangle(origo_ceiling, origo10_ceiling, f_ceiling, white, ceiling_norm));
	
	//RIGHT WALL
	const Direction rWall_norm(0.0,1.0, 0.0);
	_triangleList.push_back(Triangle(f_floor, f_ceiling, e_floor, red, rWall_norm));
	_triangleList.push_back(Triangle(f_ceiling, e_ceiling, e_floor, red, rWall_norm));

	//LEFT WALL
	const Direction lWall_norm(0.0, -1.0, 0.0);
	_triangleList.push_back(Triangle(b_ceiling, b_floor, c_floor, green, lWall_norm));
	_triangleList.push_back(Triangle(b_ceiling, c_floor, c_ceiling, green, lWall_norm));

	//RIGHT BACK WALL
	const Direction rbWall_norm = CalculateSurfaceNormal(a_floor, a_ceiling, f_floor);
	_triangleList.push_back(Triangle(a_floor, a_ceiling, f_floor, blue, rbWall_norm));
	_triangleList.push_back(Triangle(a_ceiling, f_ceiling, f_floor, blue, rbWall_norm));
	

	//LEFT BACK WALL
	const Direction lbWall_norm = CalculateSurfaceNormal(b_ceiling, a_ceiling, b_floor);
	_triangleList.push_back(Triangle(b_ceiling, a_ceiling, b_floor, yellow, lbWall_norm));
	_triangleList.push_back(Triangle(a_ceiling, a_floor, b_floor, yellow, lbWall_norm));

	//RIGHT FRONT WALL
	const Direction rfWall_norm = CalculateSurfaceNormal(e_floor, e_ceiling, d_floor);
	_triangleList.push_back(Triangle(e_floor, e_ceiling, d_floor, mirror, rfWall_norm));
	_triangleList.push_back(Triangle(e_ceiling, d_ceiling, d_floor, mirror, rfWall_norm));

	//LEFT FRONT WALL
	const Direction lfWall_norm = CalculateSurfaceNormal(c_floor, d_floor, c_ceiling);
	_triangleList.push_back(Triangle(c_floor, d_floor, c_ceiling, orange, lfWall_norm));
	_triangleList.push_back(Triangle(d_floor, d_ceiling, c_ceiling, orange, lfWall_norm));

};

std::vector<Triangle> Scene::getTriangles() {
	return _triangleList;
}

void Scene::importTriangles(std::vector<Triangle> inTriangles) {

	for( Triangle &t : inTriangles)
	_triangleList.push_back(t);
}

void Scene::addSphere(Sphere &s) {
    _sphereList.push_back(s);
}

Direction Scene::CalculateSurfaceNormal(const Vertex &p1, const Vertex &p2, const Vertex &p3 ) const
{
	Direction Normal(0.0, 0.0, 0.0);
	Vertex U(p2 - p1);
	Vertex V(p3 - p1);

	Normal.x = (U.y * V.z) - (U.z * V.y);
	Normal.y = (U.z * V.x) - (U.x * V.z);
	Normal.z = (U.x * V.y) - (U.y * V.x);

	Normal = glm::normalize(Normal);
	return Normal;
};

float Scene::findIntersection(Ray &ray)
{

	float tClosest = INFINITY;
	float t = INFINITY;
	Ray tempRay = ray;

	// intersection for triangles (room, tetras)
	for (Triangle &triangle : _triangleList)
	{
		t = triangle.rayIntersection(ray);
		if (t < INFINITY && t > 0.0 && t < tClosest)
		{

			tempRay._triangle = &triangle;
			tempRay._color = triangle._color;
			tempRay._hitNormal = triangle.getNormal();
			tClosest = t;
		}
	}

	for(Sphere &s : _sphereList) {
		t = s.sphereIntersection(ray);
		if(t<tClosest){
			tClosest = t;
			tempRay._color = s.getColor();
			tempRay._hitNormal = glm::normalize(glm::vec3(ray._start) + tClosest*glm::vec3(ray._dir) - s.getCenter());
		}
	}

	if (tClosest < INFINITY)
	{
		ray = tempRay;
		ray._end = ray._start + Vertex(ray._dir, 1.0)*tClosest;
		return tClosest;
	}
	else
		return INFINITY;


}

void Scene::addTetra(const float xPos, const float width, const float height, const float depth)
{
	Vertex ov(xPos, 2.0, -4.99, 1.0); //origin vertex
	Vertex lv(xPos+depth+1.0, 2.0 + width/2, -4.99, 1.0); //left vertex
	Vertex rv(xPos+depth, 2.0 -width/2, -4.99, 1.0); //right vertex
	Vertex tv(xPos+depth, 3.0, -4.99 + height, 1.0); //top vertex


	const ColorDbl purple(0.73, 0.33, 0.83, LAMBERTIAN);
	const Direction lWall = CalculateSurfaceNormal(ov, tv, lv); //LEFT WALL
	_triangleList.push_back(Triangle(ov, tv, lv, purple, lWall));

	const Direction rWall = CalculateSurfaceNormal(ov, rv, tv); //RIGHT WALL
	_triangleList.push_back(Triangle(ov, rv, tv, purple, rWall));

	const Direction bWall = CalculateSurfaceNormal(lv, tv, rv); //BACK WALL
	_triangleList.push_back(Triangle(lv, tv, rv, purple, bWall));

	const Direction floor = CalculateSurfaceNormal(ov, lv, rv); //FLOOR
	_triangleList.push_back(Triangle(ov, lv, rv, purple, floor));
}

ColorDbl Scene::getLightIntensity(Vertex &hitpoint, const Direction &hitnormal, Direction &shadowRay)
{

	double lightDistance = glm::distance(glm::vec3(hitpoint), _light.getCenter());
	// calc geometric term
	double alpha = glm::dot(-hitnormal, shadowRay);
	double beta = clamp((double)glm::dot(_light.getDirection(), -shadowRay), 0.0, 1.0);
	double geometric = abs(alpha * beta / pow(clamp(lightDistance,1.0 ,40), 2.0));
	ColorDbl clr = _light.getColor() * _light.getEmission() * geometric;

	return clr * _light.getLightArea();
}

double Scene::clamp(double v, double lo, double hi)
{
	if (v < lo)
		return lo;

	else if (v > hi)
		return hi;

	else
		return v;
}