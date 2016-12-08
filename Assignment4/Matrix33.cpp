#include "Matrix33.h"

Matrix33::Matrix33()
{
}

Matrix33::Matrix33(Vec3f v0, Vec3f v1, Vec3f v2)
{
	r0 = v0;
	r1 = v1;
	r2 = v2;
	c0 = Vec3f(v0.x, v1.x, v2.x);
	c1 = Vec3f(v0.y, v1.y, v2.y);
	c2 = Vec3f(v0.z, v1.z, v2.z);
}


Matrix33::~Matrix33()
{
}

Matrix33 Matrix33::operator *(const Matrix33& m)
{
	Vec3f r0 = Vec3f(this->r0.dot(m.c0), this->r0.dot(m.c1), this->r0.dot(m.c2));
	Vec3f r1 = Vec3f(this->r1.dot(m.c0), this->r1.dot(m.c1), this->r1.dot(m.c2));
	Vec3f r2 = Vec3f(this->r2.dot(m.c0), this->r2.dot(m.c1), this->r2.dot(m.c2));

	return Matrix33(r0, r1, r2);
}

Vec3f Matrix33::operator *(const Vec3f& v)
{
	return Vec3f(this->r0.dot(v),this->r1.dot(v),this->r2.dot(v));
}