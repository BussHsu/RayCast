#include <iostream>
#include <fstream> 
#include "Camera.h"
#include "VecTool.h"
#include "define.h"

Camera* Camera::activeInstance = nullptr;

Camera::Camera(const Vec3f& fPos, float fDist,const Vec3f& lookDir,const Vec3f& up):
	plane(ImagePlane(1024, 768)),
	focus(fPos),
	focalDistance(fDist)
{
	plane.SetupImgPlane(focus, focalDistance,lookDir,up);
}


Camera::~Camera()
{
}

void Camera::LookAt(const Vec3f & p)
{
	Vec3f lookDir = p - focus;
	plane.SetupImgPlane(focus, focalDistance, lookDir, plane.up);
}

void Camera::Tilt(float deg)
{
	Vec3f newUp =VecTool<float>::RotatePointAlongAxis(plane.up,Vec3f(0.0f,0.0f,0.0f),plane.lookDir,deg);
	plane.SetupUpVec(newUp);
}

void Camera::SetPosition(const Vec3f & pos)
{
	plane.SetupImgPlane(pos, focalDistance, plane.lookDir, plane.up);
}

void Camera::SetFOV(float deg)
{
	deg = fmod(deg, 180);
	if (deg == 0)
		return;
	focalDistance = plane.width / 2 / tan(deg  * PI / 180);
	plane.SetupImgPlane(focus, focalDistance, plane.lookDir, plane.up);
}

void Camera::SetResolution(int ResX, int ResY, float ppi)
{
	plane.SetupResolution(ResX, ResY, ppi);
}

GLTexture Camera::Render(const Scene& scene)
{
	int resX = plane.GetXRes();
	int resY = plane.GetYRes();
	for (int y = 0; y < resY; y++)
	{
		for (int x = 0; x < resX; x++)
		{
			Ray primaryRay = Ray(focus , plane.GetPixelLocation(x, y) - focus);
			scene.RayTracing(&(plane.colorBuffer[(x + (plane.yRes - y-1)*resX)*3]), primaryRay);
		}
	}

	//// Save result to a PPM image (keep these flags if you compile under Windows)
	//std::ofstream ofs("./untitled.ppm", std::ios::out | std::ios::binary);
	//ofs << "P6\n" << plane.xRes << " " << plane.yRes << "\n255\n";
	//for (unsigned j = 0; j<=plane.yRes; ++j)
	//{
	//	for (unsigned i = 0; i < plane.xRes; ++i) 
	//	{

	//		ofs << (unsigned char)plane.colorBuffer[(i + j*resX)*3] <<
	//			(unsigned char)plane.colorBuffer[(i + j*resX) * 3+1] <<
	//			(unsigned char)plane.colorBuffer[(i + j*resX) * 3+2];
	//	}
	//	
	//}
	//ofs.close();

	//create texture
	GLTexture texture = {};
	glGenTextures(1, &(texture.id));
	glBindTexture(GL_TEXTURE_2D, texture.id);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, resX, resY, 0, GL_RGB, GL_UNSIGNED_BYTE, plane.colorBuffer);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	glGenerateMipmap(GL_TEXTURE_2D);

	//unbind texture
	glBindTexture(GL_TEXTURE_2D, 0);

	texture.width = resX;
	texture.height = resY;
	return texture;

}


