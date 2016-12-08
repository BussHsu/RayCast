#include "Ray.h"

//Ray::Ray():
//	origin({0,0,0}),
//	direction({0,0,0})
//{
//}

Ray::Ray(const Vec3f& ori, const Vec3f& dir) :
	origin(ori),
	direction(dir)
{
	direction.normalize();
}

Ray::~Ray()
{
}
