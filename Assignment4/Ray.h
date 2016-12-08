#pragma once
#include "Vector.h"
class Ray
{
	Vec3f origin;
	Vec3f direction;
	
public:
	//Ray();
	Ray(const Vec3f& ori, const Vec3f& dir);
	~Ray();

	Vec3f GetDir() const { return direction; }
	Vec3f GetOri() const { return origin; }
};

