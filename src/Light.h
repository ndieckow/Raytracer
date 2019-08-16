#pragma once

#include "SceneObject.h"

// A light source

class Light
{
private:
	Vector3d m_Pos;
	double m_Intensity;
public:
	Light(Vector3d pos, double intensity) : m_Pos(pos), m_Intensity(intensity) {}
	double getIntensity() const { return m_Intensity; }
	double setIntensity(double i) { m_Intensity = i; }
	Vector3d getPosition() const { return m_Pos; }
};