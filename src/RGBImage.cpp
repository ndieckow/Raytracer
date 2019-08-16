#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"

#include "RGBImage.h"
#include <algorithm>

RGBImage::RGBImage(int w, int h) : m_Width(w), m_Height(h), m_Pixels(new RGBPixel[w * h])
{
}

RGBImage::RGBImage(const RGBImage& o) : m_Width(o.getWidth()), m_Height(o.getHeight()), m_Pixels(new RGBPixel[m_Width * m_Height]())
{
	std::copy(o.m_Pixels, m_Pixels + m_Width * m_Height, m_Pixels);
}

RGBImage::RGBImage(RGBImage&& o) : m_Width(o.getWidth()), m_Height(o.getHeight()), m_Pixels(o.m_Pixels)
{
	o.m_Pixels = nullptr;
}

RGBImage::~RGBImage()
{
	delete m_Pixels;
}

int RGBImage::getWidth() const
{
	return m_Width;
}

int RGBImage::getHeight() const
{
	return m_Height;
}

void RGBImage::Fill(RGBPixel color)
{
	for (int i = 0; i < m_Width * m_Height; i++) m_Pixels[i] = color;
}

void RGBImage::WriteToFile(std::string fname) const
{
	stbi_write_png(fname.c_str(), m_Width, m_Height, 3, m_Pixels, m_Width * 3);
}

RGBPixel& RGBImage::operator[](int idx)
{
	if (idx < 0 || idx >= m_Width * m_Height) exit(0);
	return m_Pixels[idx];
}

RGBPixel& RGBImage::at(int x, int y)
{
	if (x < 0 || x >= m_Width || y < 0 || y >= m_Height) exit(0);
	return m_Pixels[y * m_Width + x];
}