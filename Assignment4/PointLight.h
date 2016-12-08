#pragma once
#include "Light.h"
#include "Vector.h"
class PointLight :	public Light
{
	Vec3f position;

public:
	PointLight() {}
	PointLight(const Vec3f& p, const MyColor& c, const float i);
	virtual ~PointLight();

	Vec3f GetPosition() const { return position; }
	void SetPosition(const Vec3f& p) { position = p; }
};

