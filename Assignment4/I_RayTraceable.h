#pragma once
#include "Ray.h"
#include "MyColor.h"
#include "Vector.h"
class IRayTraceable 
{
protected:
	IRayTraceable(const MyColor& c= MyColor(255,255,255,255)) :color(c) {}
	MyColor color;

public:
	virtual bool RayIntersect(const Ray& ray, Vec3f& p, bool barycentricCoord = false) const { return false; }
	MyColor GetColor() const { return color; }
	virtual  Vec3f GetNormal(const Vec3f& p) const { return Vec3f(0,0,0); }
};