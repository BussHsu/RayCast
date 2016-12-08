#include "Sprite.h"
#include "Vertex.h"
#include <cstddef>


Sprite::Sprite()
{
	_vboID = 0;
}


Sprite::~Sprite()
{
	if (_vboID)
		glDeleteBuffers(1, &_vboID);
}

void Sprite::init(float x, float y, float w, float h)
{
	_x = x;
	_y = y;
	_w = w;
	_h = h;

	if (_vboID == 0)
	{
		glGenBuffers(1, &_vboID);
	}

	Vertex vertexData[6];
	vertexData[0].SetPosition(x + w, y + h);
	vertexData[0].SetUV(1.0f, 1.0f);

	vertexData[1].SetPosition(x, y + h);
	vertexData[1].SetUV(0.0f, 1.0f);

	vertexData[2].SetPosition(x, y);
	vertexData[2].SetUV(0.0f, 0.0f);

	vertexData[3].SetPosition(x + w, y + h);
	vertexData[3].SetUV(1.0f, 1.0f);

	vertexData[4].SetPosition(x + w, y);
	vertexData[4].SetUV(1.0f, 0.0f);

	vertexData[5].SetPosition(x, y);
	vertexData[5].SetUV(0.0f, 0.0f);

	//for (int i = 0; i < 6; i++)
	//{
	//	vertexData[i].color.r = 255;
	//	vertexData[i].color.g = 0;
	//	vertexData[i].color.b = 255;
	//	vertexData[i].color.a = 255;
	//}

	vertexData[1].SetColor(0, 255, 255, 255);

	vertexData[4].SetColor(255, 0, 255, 255);
	glBindBuffer(GL_ARRAY_BUFFER, _vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sprite::draw()
{
	glBindBuffer(GL_ARRAY_BUFFER, _vboID);

	//tell opengl that we want to use the first attrib array
	glEnableVertexAttribArray(0);
	//the position attrib pointer
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	//the color attrib pointer
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
	//uv attrib pointer
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

	//draw 6 vertices to the screen
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}