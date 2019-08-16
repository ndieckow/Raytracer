#pragma once

#include "SceneObject.h"

#include <iostream>

class Plane : public SceneObject
{
private:
	Vector3d m_Normal;
	double m_Size; // negative size means inifinite
public:
	Plane() : SceneObject(), m_Normal(Vector3d(0, 1, 0)), m_Size(-1.0) {}
	Plane(Vector3d pos, Vector3d normal, double size, const Material& m) : SceneObject(pos, m), m_Normal(normal), m_Size(size) {}

	Vector3d getNormal() const { return m_Normal; }
	double getSize() const { return m_Size; }

	Vector3d getNormal(Vector3d point) override { return m_Normal; }

	double Intersect(const Ray& ray) override
	{
		if (m_Normal.dot(ray.getDirection()) == 0) return 0; // no intersection
		double dot1 = (getPosition() - ray.getOrigin()).dot(m_Normal);
		double dot2 = ray.getDirection().dot(m_Normal);
		double lambda = dot1 / dot2;

		if (m_Size > 0)
		{
			Vector3d v = ray.getDirection() * lambda + ray.getOrigin();
			if ((v - getPosition()).maxNorm() > m_Size) return 0;
		}

		return lambda < 0 ? 0 : lambda; // return lambda if bigger than zero (otherwise the plane is behind the camera)
	}
};