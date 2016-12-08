#pragma once
#include<GL\glew.h>

class Sprite
{
public:
	Sprite();
	~Sprite();

	void draw();
	void init(float x, float y, float w, float h);

private:
	float _x, _y, _w, _h;
	GLuint _vboID;

};
