#include "PointLight.h"

PointLight::PointLight(const Vec3f& p, const MyColor& c, const float i):
	Light(c,i),
	position(p)
{
}


PointLight::~PointLight()
{
}
