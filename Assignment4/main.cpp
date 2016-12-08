#include <GL/glew.h>
#include <SDL\SDL.h>
#include <iostream>
#include "Vector.h"
#include "Scene.h"
#include "Sphere.h"
#include "Camera.h"
#include "Vertex.h"
#include "PointLight.h"
#include "Sprite.h"
#include "GLSLProgram.h"

SDL_Window* _window;
int _screeWidth = 1024;
int _screenHeight = 768;
Sprite _sprite;
GLTexture _playerTexture;
GLSLProgram _colorProgram;
bool exitFlag = false;

void initShaders()
{
	_colorProgram.compileShaders("Shader\\colorShading.vert", "Shader\\colorShading.frag");
	_colorProgram.addAttribute("vertexPosition");
	_colorProgram.addAttribute("vertexColor");
	_colorProgram.addAttribute("vertexUV");
	_colorProgram.linkShaders();
}

void initSystems()
{
	//SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Init(SDL_INIT_VIDEO);
	//SDL_Init(SDL_INIT_AUDIO);
	SDL_Init(SDL_INIT_TIMER);

	_window = SDL_CreateWindow("Graphics", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _screeWidth, _screenHeight, SDL_WINDOW_OPENGL);
	if (_window == nullptr)
	{
		fatalerror("Cannot create sdl window.");
	}

	SDL_GLContext glContext = SDL_GL_CreateContext(_window);
	if (glContext == nullptr)
	{
		fatalerror("Cannot create sdl gl context");
	}

	GLenum err = glewInit();	  //initialize Glew
	if (err != GLEW_OK)
		fatalerror("Cannot init glew");

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);					//clear color is blue
	initShaders();
}

void drawGame()
{
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_colorProgram.use();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _playerTexture.id);

	//draw sprite
	_sprite.draw();

	_colorProgram.unuse();
	glBindTexture(GL_TEXTURE_2D, 0);

	SDL_GL_SwapWindow(_window);
}

void processInput()
{
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt))
	{
		switch (evnt.type)
		{
		case SDL_QUIT:
		{
			exitFlag = true;
		}
		break;
		case SDL_MOUSEMOTION:
		{
			
		}
		break;
		}
	}
}

int main(int argc, char **argv)
{

	//create a default camera located at origin, look at z
	Camera cam = Camera(Vec3f(0,0,-2.5f),2.5f);

	//create scene
	Scene scene = Scene(MyColor(0,255,255));
	Sphere* sphere1 = new Sphere(Vec3f(0, 0, 15), 7.0f, MyColor(255,255,255));
	scene.AddObj(sphere1);

	Sphere* sphere2 = new Sphere(Vec3f(0, 6, 10), 3.0f, MyColor(255, 255, 0));
	scene.AddObj(sphere2);

	Sphere* sphere3 = new Sphere(Vec3f(4, 6, 10), 1.0f, MyColor(255, 0, 0));
	scene.AddObj(sphere3);

	Sphere* sphere4 = new Sphere(Vec3f(0, 6, 2), 1.0f, MyColor(0, 128, 200));
	scene.AddObj(sphere4);
	PointLight light = PointLight(Vec3f(0, 10, -2.5f), MyColor(255,255,255), 1);
	scene.SetLight(light);

	//rendering 
	initSystems();
	_sprite.init(-1.0f, -1.0f, 2.0f, 2.0f);
	_playerTexture = cam.Render(scene);

	//update loop
	while (!exitFlag)
	{
		processInput();
		drawGame();
	}
		

	return 0;
}
