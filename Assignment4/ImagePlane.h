#pragma once
#include "Vector.h"
class ImagePlane
{
	friend class Camera;
	float width;
	float height;
	//square pixel only
	int xRes;
	int yRes;
	float ppi;

	//up vector,look direction, center pos
	Vec3f up;			//normalized
	Vec3f lookDir;		//normalized
	Vec3f center;

	bool zAlgin = false;
	//the buffer stores color
	unsigned char* colorBuffer;
	
public:
	//ImagePlane(int ResolutionX, int ResolutionY, float width = 0, float height = 0);
	ImagePlane(int ResolutionX, int ResolutionY, float ppi = 300);
	~ImagePlane();
	
	//Setup vectors
	void SetupImgPlane(const Vec3f& focus, float fDist, const Vec3f& lookDir, const Vec3f& up);
	void SetupUpVec(const Vec3f& up) { this->up = up; }
	//Setup resolution
	void SetupResolution(const int resX, const int resY, const float ppi);
	//Get the location in 3D space of pixel position 
	Vec3f GetPixelLocation(int x, int y) const;
	////set the color of location
	//void SetPixelColor(int* location, float* color);

	//GetResolutions
	int GetXRes() const{ return xRes; }
	int GetYRes() const { return yRes; }



private:
	void ClearColorBuffer();
	void SetCenter(const Vec3f& focus, float fDist, const Vec3f& lookDir);
};

