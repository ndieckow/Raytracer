#pragma once

#include "Vector3d.h"

class Ray
{
private:
	Vector3d m_Origin, m_Dir;
public:
	Ray(Vector3d o, Vector3d d) : m_Origin(o), m_Dir(d.normalized()) {}
	Vector3d getOrigin() const { return m_Origin; }
	Vector3d getDirection() const { return m_Dir; }
};