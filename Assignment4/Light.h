#pragma once
#include "MyColor.h"
class Light
{
	MyColor color;
	float intensity;

public:
	Light();
	Light(const MyColor& c, const float intensity);
	~Light();
	MyColor GetColor() const;
};

