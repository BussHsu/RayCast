#include "ImagePlane.h"
#include "define.h"


ImagePlane::ImagePlane(int ResolutionX, int ResolutionY, float ppi)
{
	SetupResolution(ResolutionX, ResolutionY, ppi);
}

ImagePlane::~ImagePlane()
{
	ClearColorBuffer();
}

void ImagePlane::SetupImgPlane(const Vec3f & focus, float fDist, const Vec3f & lookDir, const Vec3f & up)
{
	if (lookDir.z == 1 && up.y ==1)
		zAlgin = true;
	SetCenter(focus, fDist, lookDir);
	this->up = Vec3f(up).normalize();
	this->lookDir = Vec3f(lookDir).normalize();
}


void ImagePlane::SetupResolution(const int resX, const int resY,const float ppi)
{
	//clear previous buffer
	ClearColorBuffer();
	//setup parameters
	xRes = resX;
	yRes = resY;
	this->ppi = ppi;
	//the measurement unit is cm
	width = resX / ppi*INCHTOCM;	//8.67cm = 120deg => focaldist = 2.5
	height = resY / ppi*INCHTOCM;	//6.5cm

	//create xRes*yRes*3 buffer
	colorBuffer = new unsigned char[resX*resY*3];
}

Vec3f ImagePlane::GetPixelLocation(int x, int y) const
{
	Vec3f ret;
	if (zAlgin)
	{
		ret.z = center.z;
		float gridWidth = width / xRes;
		if (xRes % 2 == 0)
			ret.x = center.x + (x-xRes/2+0.5f)*gridWidth;
		else
			ret.x = center.x + (x - xRes / 2)*gridWidth;
		if (yRes % 2 == 0)
			ret.y = center.y + (y - yRes / 2 + 0.5f)*gridWidth;
		else
			ret.y = center.y + (y - yRes / 2)*gridWidth;
		return ret;
	}
	else 
	{
		Vec3f l = lookDir.cross(up);
		Vec3f n = up;
		float gridWidth = width / xRes;
		l *= gridWidth;
		n *= gridWidth;
		ret = center;
		if (xRes % 2 == 0)
			ret += l*(x - xRes / 2 + 0.5f);
		else
			ret+= l*(x - xRes / 2);
		if (yRes % 2 == 0)
			ret+= n*(y - yRes / 2 + 0.5f);
		else
			ret+= n*(y - yRes / 2);
		return ret;
	}
}

void ImagePlane::ClearColorBuffer()
{
	if (colorBuffer)
	{
		delete[] colorBuffer;
	}
}

void ImagePlane::SetCenter(const Vec3f& focus, float fDist, const Vec3f& lookDir)
{
	center = focus + (Vec3f(lookDir).normalize())*fDist;
}