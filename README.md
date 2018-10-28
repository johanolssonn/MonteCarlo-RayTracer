# MonteCarlo-RayTracer
A project for the course Advanced Global Illumination (TNCG15) at Linköping University.

## Languages
This MonteCarlo-RayTracer is built solely on C++ and the OpenGL Mathematics (GLM) library. 

## The room
The rendered image is of a closed room with 6 walls, 1 tetrahedron and 2 spheres. One of the walls as well as one of the spheres
uses specular reflections. The floor, ceiling and the remaining walls and objects uses a Lambertian based BRDF. 
Total amount of triangles in the scene is 28. The boundaries of the room makes up 24, and the tetrahedron is the remaining 4.
Both spheres are implicitly defined and therefore uses no triangles.

## Intersections and Light
Triangle intersections are calculated using the Möller Trumbore algorithm. The scene is lit up by one lightsource which is a rectangle
of two triangles located slightly below the ceiling. We treat it as an area light and randomize the shadowray
directions in order to achieve soft shadows.

## Rendered Image
The final image rendered is 2000x2000 pixels. We randomize ray directions with 35 samples per pixel. Each ray has a max depth 
of 4 bounces, provided it's not eliminated early by the roussian roulette scheme. 

![MonteCarlo-RayTracer](raytracer.png?raw=true "Title")
