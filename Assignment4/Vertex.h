#pragma once
#include<GL\glew.h>

struct Position
{
	float x;
	float y;
};

struct Color
{
	GLubyte r, g, b, a;
};

struct UV
{
	float U;
	float V;
};

struct Vertex
{
	Position position;
	Color color;
	UV uv;

	void SetColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a)
	{
		color.r = r;
		color.g = g;
		color.b = b;
		color.a = a;
	}

	void SetUV(float u, float v)
	{
		uv.U = u;
		uv.V = v;
	}

	void SetPosition(float x, float y)
	{
		position.x = x;
		position.y = y;
	}
};