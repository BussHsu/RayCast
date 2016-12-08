#pragma once
#include <vector>
#include "I_RayTraceable.h"
#include "Light.h"
#include "PointLight.h"
class Scene
{
	std::vector<IRayTraceable*> objects;
	//std::vector<Light> lights;
	PointLight light;
	MyColor bgColor;
public:
	Scene();
	Scene(const MyColor& bg);
	~Scene();

	void SetLight(PointLight& l) { light = l; }
	//void AddLight(Light& l) { lights.push_back(l); }
	void AddObj(IRayTraceable* obj) { objects.push_back(obj); }
	void RayTracing(unsigned char* dest, const Ray& ray) const;
};

