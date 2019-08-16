#pragma once

#include "SceneObject.h"

class Sphere : public SceneObject
{
private:
	double m_Radius;
public:
	Sphere() : SceneObject(), m_Radius(1) {}
	Sphere(Vector3d pos, double radius, const Material& m) : SceneObject(pos, m), m_Radius(radius) {}
	~Sphere() {}

	double getRadius() const
	{
		return m_Radius;
	}

	void setRadius(double radius)
	{
		m_Radius = radius;
	}

	Vector3d getNormal(Vector3d point) override
	{
		return (point - getPosition()).normalized();
	}

	double Intersect(const Ray& ray) override
	{
		Vector3d oc = ray.getOrigin() - getPosition();
		double b = ray.getDirection().dot(oc);
		double dis = b * b - oc.dot(oc) + m_Radius * m_Radius; // term inside of the square root
		if (dis < 0) return 0; // ray misses the sphere
		double t = -b - sqrt(dis);
		return t > 0 ? t : ((t = -b + sqrt(dis)) > 0 ? t : 0);
	}

};