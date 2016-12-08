#include "Sphere.h"



Sphere::Sphere(const Vec3f& center, const float radius, const MyColor& c):
	IRayTraceable(c),
	center(center), 
	r(radius)
{

}


Sphere::~Sphere()
{
}

bool Sphere::RayIntersect(const Ray& ray, Vec3f& p, bool barycentricCoord) const
{
	if(!barycentricCoord)
	{ 
		float a = 1.0f;
		float b = 2.0f * ((ray.GetOri() - this->center)).dot(ray.GetDir());
		float c = ((ray.GetOri() - this->center)).length2() - r*r;
		float D = b*b - 4.0f * a*c;
		if (D < 0.0f)
			return false;
		float t = ((-b)-sqrt(D)) / (2.0f * a);
		p = ray.GetOri() + ray.GetDir()*t;
		return t>0;
	}
	else 
	{
		return false;
	}
}

Vec3f Sphere::GetNormal(const Vec3f & p) const
{
	return Vec3f(p-center).normalize();
}
