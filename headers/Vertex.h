#ifndef VERTEX_H
#define VERTEX_H

class Vertex {
public:
	//Vertex(float x, float y, float z);
	Vertex(float x, float y, float z, float w = 1.0f);
	~Vertex() = default;
private:
	float _x, _y, _z, _w;


};

#endif //VERTEX_H