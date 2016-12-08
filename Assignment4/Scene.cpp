#include "Scene.h"
#include "Vector.h"
#include "Sphere.h"
#include <algorithm>


Scene::Scene() :
	bgColor(MyColor(0,0,0,255))
{
}

Scene::Scene(const MyColor& bg):
	bgColor(bg)
{

}


Scene::~Scene()
{
	//lights.clear();
	objects.clear();
}

void Scene::RayTracing(unsigned char * dest, const Ray & ray) const
{
	Vec3f pos, temp;
	IRayTraceable* hitTarget = nullptr;
	bool hitflag = false;
	float sqrDistToCamera = INFINITY;
	//look through every objests
	/*std::vector<IRayTraceable>::const_iterator it , object;*/
	for (auto obj:objects)
	{
		//if there's intersection
		if (obj->RayIntersect(ray, temp, false)) 
		{
			hitflag = true;
			//TO FIX:use z coordinate to determine distance
			if (temp.z < sqrDistToCamera)
			{
				sqrDistToCamera = temp.z;
				pos = temp;
				hitTarget = obj;
			}

			//float dist = (ray.GetOri() - temp).length2();
			//if (dist < sqrDistToCamera)
			//{
			//	sqrDistToCamera = dist;
			//	pos = temp;
			//	hitTarget = obj;
			//}
		}
	}
	if (hitTarget)
	{
		MyColor objColor = hitTarget->GetColor();
		//calculate light
		Ray shadowRay = Ray(pos,  light.GetPosition()-pos);
		//if obscured => color = bgcolor
		bool obscureFlag = false;
		for (auto obscureObj : objects)
		{
			if (obscureObj->RayIntersect(shadowRay, temp) && ((temp - pos).length2()>0.001f))
			{
				obscureFlag = true;
				break;
			}
		}
		if (obscureFlag)
		{
			//debug shadow color = black
			dest[0] = 0;
			dest[1] = 0;
			dest[2] = 0;
		}
		else
		{
			//diffuse color = cos = N dot L
			float cos = abs(hitTarget->GetNormal(pos).dot(shadowRay.GetDir()));
			dest[0] = (unsigned char)((float)objColor.r) / 255 * light.GetColor().r*cos;
			dest[1] = (unsigned char)((float)objColor.g) / 255 * light.GetColor().g*cos;
			dest[2] = (unsigned char)((float)objColor.b) / 255 * light.GetColor().b*cos;
		}
	}
	else 
	{
		dest[0] = bgColor.r;
		dest[1] = bgColor.g;
		dest[2] = bgColor.b;
	}
}
