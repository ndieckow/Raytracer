#pragma once

#include <cmath>
#include <ostream>

struct Vector3d
{
	double x, y, z;

	Vector3d() : x(0), y(0), z(0) {}
	Vector3d(double xv, double yv, double zv) : x(xv), y(yv), z(zv) {}

	Vector3d operator+(const Vector3d& o) const
	{
		return Vector3d(x + o.x, y + o.y, z + o.z);
	}

	Vector3d operator-(const Vector3d& o) const
	{
		return Vector3d(x - o.x, y - o.y, z - o.z);
	}

	Vector3d operator*(double f) const
	{
		return Vector3d(x * f, y * f, z * f);
	}

	Vector3d& operator+=(const Vector3d& o)
	{
		x += o.x;
		y += o.y;
		z += o.z;
		return *this;
	}

	Vector3d& operator-=(const Vector3d& o)
	{
		x -= o.x;
		y -= o.y;
		z -= o.z;
		return *this;
	}

	Vector3d& operator*=(double f)
	{
		x *= f;
		y *= f;
		z *= f;
		return *this;
	}

	Vector3d operator-() const
	{
		return Vector3d(-x, -y, -z);
	}

	void operator=(const Vector3d& o)
	{
		x = o.x;
		y = o.y;
		z = o.z;
	}

	double dot(const Vector3d& o) const
	{
		return x * o.x + y * o.y + z * o.z;
	}

	Vector3d cross(const Vector3d& o) const
	{
		return Vector3d(y * o.z - z * o.y, z * o.x - x * o.z, x * o.y - y * o.x);
	}

	double norm() const
	{
		return sqrt(x * x + y * y + z * z);
	}

	// returns the maximum norm of the vector
	// i.e. highest absolute component value
	double maxNorm() const
	{
		double norm = 0;
		if (abs(x) > norm) norm = abs(x);
		if (abs(y) > norm) norm = abs(y);
		if (abs(z) > norm) norm = abs(z);
		return norm;
	}

	Vector3d normalized() const
	{
		return (*this * (1 / norm()));
	}
	
	// assumes axis to be normalized
	Vector3d reflect(const Vector3d& axis) const
	{
		double lambda = axis.dot(*this);
		//Vector3d y = (axis * lambda - *this) * 2;
		return axis * (lambda * 2) - *this;
	}

};

static std::ostream& operator<<(std::ostream& o, const Vector3d& v)
{
	o << v.x << ", " << v.y << ", " << v.z;
	return o;
}