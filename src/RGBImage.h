#pragma once

#include <string>
#include "Vector3d.h"

#define MIN(x, y) x > y ? y : x
#define MAX(x, y) x < y ? y : x

static unsigned char dtouc(double x)
{
	if (x > 1.0) x = 1.0;
	if (x < 0.0) x = 0.0;
	return static_cast<unsigned char>(x * 255);
}

struct RGBPixel
{
	unsigned char r, g, b;

	RGBPixel() : r(0), g(0), b(0)
	{
	}

	RGBPixel(unsigned char rv, unsigned char gv, unsigned char bv) : r(rv), g(gv), b(bv)
	{
	}

	void setColor(unsigned char rv, unsigned char gv, unsigned char bv)
	{
		r = rv;
		g = gv;
		b = bv;
	}

	// the Vector3d must have values between 0 and 1.
	// values will be capped
	void setColor(Vector3d c)
	{
		r = dtouc(c.x);
		g = dtouc(c.y);
		b = dtouc(c.z);
	}

	void operator=(const RGBPixel& o)
	{
		r = o.r;
		g = o.g;
		b = o.b;
	}
};

class RGBImage
{
private:
	RGBPixel* m_Pixels;
	int m_Width, m_Height;
public:
	RGBImage(int w, int h);
	RGBImage(const RGBImage& o);
	RGBImage(RGBImage&& o);
	~RGBImage();
	int getWidth() const;
	int getHeight() const;
	void Fill(RGBPixel color);
	void WriteToFile(std::string fname) const;

	RGBPixel& operator[](int idx);
	RGBPixel& at(int x, int y);
};