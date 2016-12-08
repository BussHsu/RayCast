#pragma once
#include "Vector.h"
class Matrix33
{
	Vec3f r0, r1, r2;
	Vec3f c0, c1, c2;
public:
	Matrix33();
	Matrix33(Vec3f v0, Vec3f v1, Vec3f v2);
	~Matrix33();

	Matrix33 operator *(const Matrix33& m);
	Vec3f operator *(const Vec3f& v);
};

