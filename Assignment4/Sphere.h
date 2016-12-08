#pragma once
#include "Vector.h"
#include "Vertex.h"
#include "I_RayTraceable.h"
class Sphere: public IRayTraceable
{
	Vec3f center;
	float r;


public:
	Sphere(const Vec3f& center, const float radius, const MyColor& c = { 255,255,255,255 });
	~Sphere();

	 bool RayIntersect(const Ray& ray, Vec3f& p, bool barycentricCoord = false) const override;
	 Vec3f GetNormal(const Vec3f& p) const override;
};

