#pragma once
#include "Vector.h"

template<typename T>
class VecTool
{

public:
	//Rotate a point around an axis
	static Vec3<T> RotatePointAlongAxis(const Vec3<T>& p,const Vec3<T>& axisPoint,const Vec3<T>& axisDir, float deg);
};

