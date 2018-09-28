#include "Scene.h"

Scene::Scene() {}

//(TOP VIEW)
//	        b(0,6)________c(10,6)
//	      a(-3,0)/        \ d(13,0)
//		  f(0,-6)\________/e(10,-6)
//
//		Y	
//		|__ X
//   
//(SIDE VIEW)
//	    g(-3,5) _____h(0,5)______i(10,5)______j(13,5)
//              |       |            |        |
//	            |       |            |        |
//	    n(-3,-5)|_______|____________|________|k(13,-5)
//                   m(0,-5)     l(10,-5)
//		Z	
//		|__ X
//  
void Scene::createScene()
{
	Vertex a{ -3.0f, 0.0f, 0.0f };
	Vertex b{ -0.0f, 6.0f, 0.0f };
	Vertex c{ 10.0f, 6.0f, 0.0f };
	Vertex d{ 13.0f, 0.0f, 0.0f };
	Vertex e{ 10.0f, -6.0f, 0.0f };
	Vertex f{ 0.0f, -6.0f, 0.0f };

	Vertex g{ -3.0f, .0f, 5.0f };
	Vertex h{ .0f, .0f, 5.0f };
	Vertex i{ 10.0f, .0f, 5.0f };
	Vertex j{ 13.0f, .0f, 5.0f };
	Vertex k{ 13.0f, .0f, -5.0f };
	Vertex l{ 10.0f, .0f, -5.0f };
	Vertex m{ .0f, .0f, -5.0f };
	Vertex n{ -3.0f, .0f, -5.0f };
};
