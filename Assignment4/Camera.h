#pragma once
#include "Vector.h"
#include "ImagePlane.h"
#include "Scene.h"
#include "GLTexture.h"
#include <stdio.h>

class Camera
{
	Vec3f focus;
	ImagePlane plane;
	//FOV and Fdist are actually mutually dependent
	float focalDistance;
	float FOV;
	static Camera* activeInstance;
public:
	Camera(const Vec3f& fPos,float fDist,const Vec3f& lookDir = Vec3f(0.0f,0.0f,1.0f),const Vec3f& up = Vec3f(0.0f, 1.0f, 0.0f));
	~Camera();

	void LookAt(const Vec3f& p);
	void Tilt(float deg);
	//Setup parameters
	void SetPosition(const Vec3f& pos);
	void SetFOV(float deg);
	void SetResolution(int ResX, int ResY, float ppi);
	
	//GetResolution
	int GetXRes() const { return plane.xRes; }
	int GetYRes() const { return plane.yRes; }

	//Render
	GLTexture Render(const Scene& scene);
};

