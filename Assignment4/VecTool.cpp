#include "VecTool.h"      
#include "define.h"

template<typename T>
Vec3<T> VecTool<T>::RotatePointAlongAxis(const Vec3<T>& p, const Vec3<T>& axisPoint, const Vec3<T>& axisDir, float deg)
{

	T rad = fmod(deg, 360) / 360.0f * 2 * PI;
	T c = cos(rad);
	T s = sin(rad);
	Vec3<T> ret = p;
	Vec3<T> A = axisDir;
	A.normalize();
	//1. use axisPoint as origin
	ret -= axisPoint;
	//2. rotate along arbitrary axis
	Vec3<T> r0 = Vec3<T>(c + (1 - c)*A.x*A.x, (1 - c)*A.x*A.y - s*A.z, (1 - c)*A.x*A.z + s*A.y);
	Vec3<T> r1 = Vec3<T>((1 - c)*A.x*A.y + s*A.z, c + (1 - c)*A.y*A.y, (1 - c)*A.y*A.z - s*A.x);
	Vec3<T> r2 = Vec3<T>((1 - c)*A.x*A.z - A.y*s, (1 - c)*A.y*A.z + s*A.x, c + (1 - c)*A.z*A.z);
	float retX = r0.dot(ret);
	float retY = r1.dot(ret);
	float retZ = r2.dot(ret);
	ret.x = retX;
	ret.y = retY;
	ret.z = retZ;
	// translate back
	ret += axisPoint;
	return ret;
}

template class VecTool<float>;