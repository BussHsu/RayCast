#pragma once
struct MyColor
{
	unsigned char r, g, b, a;
	MyColor(int ri, int gi, int bi, int ai =255):r(ri),g(gi),b(bi),a(ai) {}
	MyColor(float rf, float gf, float bf, float af = 1) 
	{
		r = (unsigned char) 255 * rf;
		g = (unsigned char) 255 * gf;
		b = (unsigned char) 255 * bf;
		a = (unsigned char) 255 * af;
	}
};