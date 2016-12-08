#include "Light.h"



Light::Light() :
	color({255,255,255,255}),
	intensity(1.0f)
{
}

Light::Light(const MyColor& c, const float intensity) :
	color(c),
	intensity(intensity)
{
}


Light::~Light()
{
}

MyColor Light::GetColor() const
{
	return color;
}
