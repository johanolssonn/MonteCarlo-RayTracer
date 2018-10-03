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
	const Vertex a{ -3.0f, 0.0f, -5.0f };
	const Vertex b{ -0.0f, 6.0f, -5.0f };
	const Vertex c{ 10.0f, 6.0f, -5.0f };
	const Vertex d{ 13.0f, 0.0f, -5.0f };
	const Vertex e{ 10.0f, -6.0f, -5.0f };
	const Vertex f{ 0.0f, -6.0f, -5.0f };

	const Vertex g{ -3.0f, .0f, 5.0f };
	const Vertex h{ .0f, .0f, 5.0f };
	const Vertex i{ 10.0f, .0f, 5.0f };
	const Vertex j{ 13.0f, .0f, 5.0f };
	const Vertex k{ 13.0f, .0f, -5.0f };
	const Vertex l{ 10.0f, .0f, -5.0f };
	const Vertex m{ .0f, .0f, -5.0f };
	const Vertex n{ -3.0f, .0f, -5.0f };

	const Vertex origo{ 0.0f, 0.0f, 0.0f };
	const Vertex origo10{ 10.0f, 0.0f, 0.0f};

	const ColorDbl white(1.0, 1.0, 1.0); //Default constructor gives white color
	const ColorDbl black(0.0, 0.0, 0.0);
	const ColorDbl red(1.0, 0.0, 0.0);
	const ColorDbl green(0.0, 1.0, 0.0);
	const ColorDbl blue(0.0, 0.0, 1.0);
	const ColorDbl yellow(1.0, 1.0, 0.0);
	//const ColorDbl black(0.0, 0.0, 0.0);
	//const ColorDbl black(0.0, 0.0, 0.0);

	//FLOOR
	const Direction floor_norm( 0.0, 0.0, 1.0 );
	triangle_list.push_back(Triangle(a, f, b, white, floor_norm));
	triangle_list.push_back(Triangle(b, origo, origo10, white, floor_norm));
	triangle_list.push_back(Triangle(origo10, c, b, white, floor_norm));
	triangle_list.push_back(Triangle(e, d, c, white, floor_norm));
	triangle_list.push_back(Triangle(e, origo10, f, white, floor_norm));
	triangle_list.push_back(Triangle(origo10, origo, f, white, floor_norm));

	//WALLS

};
