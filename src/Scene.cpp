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
	const Vertex a_floor{ -3.0f, 0.0f, -5.0f };
	const Vertex b_floor{ -0.0f, 6.0f, -5.0f };
	const Vertex c_floor{ 10.0f, 6.0f, -5.0f };
	const Vertex d_floor{ 13.0f, 0.0f, -5.0f };
	const Vertex e_floor{ 10.0f, -6.0f, -5.0f };
	const Vertex f_floor{ 0.0f, -6.0f, -5.0f };
	const Vertex origo_floor{ 0.0f, 0.0f, -5.0f };
	const Vertex origo10_floor{ 10.0f, 0.0f, -5.0f};

	const Vertex a_ceiling{ -3.0f, 0.0f, 5.0f };
	const Vertex b_ceiling{ -0.0f, 6.0f, 5.0f };
	const Vertex c_ceiling{ 10.0f, 6.0f, 5.0f };
	const Vertex d_ceiling{ 13.0f, 0.0f, 5.0f };
	const Vertex e_ceiling{ 10.0f, -6.0f, 5.0f };
	const Vertex f_ceiling{ 0.0f, -6.0f, 5.0f };
	const Vertex origo_ceiling{ 0.0f, 0.0f, 5.0f };
	const Vertex origo10_ceiling{ 10.0f, 0.0f, 5.0f};

	const Vertex g{ -3.0f, .0f, 5.0f };
	const Vertex h{ .0f, .0f, 5.0f };
	const Vertex i{ 10.0f, .0f, 5.0f };
	const Vertex j{ 13.0f, .0f, 5.0f };
	const Vertex k{ 13.0f, .0f, -5.0f };
	const Vertex l{ 10.0f, .0f, -5.0f };
	const Vertex m{ .0f, .0f, -5.0f };
	const Vertex n{ -3.0f, .0f, -5.0f };



	const ColorDbl white(1.0, 1.0, 1.0); //Default constructor gives white color
	const ColorDbl red(1.0, 0.0, 0.0);
	const ColorDbl green(0.0, 1.0, 0.0);
	const ColorDbl blue(0.0, 0.0, 1.0);
	const ColorDbl yellow(1.0, 1.0, 0.0);
	const ColorDbl gray(0.0, 0.0, 0.0);
	const ColorDbl orange(1.0, 0.5, 0.2);

	//FLOOR
	const Direction floor_norm( 0.0, 0.0, 1.0 );
	triangle_list.push_back(Triangle(a_floor, f_floor, b_floor, white, floor_norm));
	triangle_list.push_back(Triangle(b_floor, origo_floor, origo10_floor, white, floor_norm));
	triangle_list.push_back(Triangle(origo10_floor, c_floor, b_floor, white, floor_norm));
	triangle_list.push_back(Triangle(e_floor, d_floor, c_floor, white, floor_norm));
	triangle_list.push_back(Triangle(e_floor, origo10_floor, f_floor, white, floor_norm));
	triangle_list.push_back(Triangle(origo10_floor, origo_floor, f_floor, white, floor_norm));

	//CEILING
	const Direction ceiling_norm(0.0 ,0.0, -1.0);
	triangle_list.push_back(Triangle(a_ceiling, b_ceiling, f_ceiling, white, ceiling_norm));
	triangle_list.push_back(Triangle(b_ceiling, origo10_ceiling, origo_ceiling, white, ceiling_norm));
	triangle_list.push_back(Triangle(origo10_ceiling, b_ceiling, c_ceiling, white, ceiling_norm));
	triangle_list.push_back(Triangle(c_ceiling, d_ceiling, e_ceiling, white, ceiling_norm));
	triangle_list.push_back(Triangle(e_ceiling, f_ceiling, origo10_ceiling, white, ceiling_norm));
	triangle_list.push_back(Triangle(origo_ceiling, origo10_ceiling, f_ceiling, white, ceiling_norm));
	
	//RIGHT WALL
	const Direction rWall_norm(0.0 ,1.0, 0.0);
	triangle_list.push_back(Triangle(f_floor, f_ceiling, e_floor, red, rWall_norm));
	triangle_list.push_back(Triangle(f_ceiling, e_ceiling, e_floor, red, rWall_norm));

	//LEFT WALL
	const Direction lWall_norm(0.0, -1.0, 0.0);
	triangle_list.push_back(Triangle(b_ceiling, b_floor, c_floor, green, lWall_norm));
	triangle_list.push_back(Triangle(b_ceiling, c_ceiling, c_ceiling, green, lWall_norm));

	//RIGHT BACK WALL
	const Direction rbWall_norm = CalculateSurfaceNormal(a_floor, a_ceiling, f_floor);
	triangle_list.push_back(Triangle(a_floor, a_ceiling, f_floor, blue, rbWall_norm));
	triangle_list.push_back(Triangle(a_ceiling, f_ceiling, f_floor, blue, rbWall_norm));

	std::cout << "RIGHT BACK WALL NORMAL: " << rbWall_norm << std::endl;
	

	//LEFT BACK WALL
	const Direction lbWall_norm = CalculateSurfaceNormal(b_ceiling, a_ceiling, b_floor);
	triangle_list.push_back(Triangle(b_ceiling, a_ceiling, b_floor, yellow, lbWall_norm));
	triangle_list.push_back(Triangle(a_ceiling, a_floor, b_floor, yellow, lbWall_norm));

	//RIGHT FRONT WALL
	const Direction rfWall_norm = CalculateSurfaceNormal(e_floor, e_ceiling, d_floor);
	triangle_list.push_back(Triangle(e_floor, e_ceiling, d_floor, gray, rfWall_norm));
	triangle_list.push_back(Triangle(e_ceiling, d_ceiling, d_floor, gray, rfWall_norm));

	//LEFT FRONT WALL
	const Direction lfWall_norm = CalculateSurfaceNormal(c_floor, d_floor, c_ceiling);
	triangle_list.push_back(Triangle(c_floor, d_floor, c_ceiling, orange, lfWall_norm));
	triangle_list.push_back(Triangle(d_floor, d_ceiling, c_ceiling, orange, lfWall_norm));


};

Direction Scene::CalculateSurfaceNormal(const Vertex &p1, const Vertex &p2, const Vertex &p3 ) const
{
	Direction Normal(0.0, 0.0, 0.0);
	Vertex U(p2 - p1);
	Vertex V(p3 - p1);

	Normal._x = (U._y * V._z) - (U._z * V._y);
	Normal._y = (U._z * V._x) - (U._x * V._z);
	Normal._z = (U._x * V._y) - (U._y * V._x);

	Normal.normalize();
	return Normal;
};
