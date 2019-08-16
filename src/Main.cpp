#include "Vector3d.h"
#include "Scene.h"
#include "Sphere.h"
#include "Light.h"
#include "Plane.h"

#include <cmath>
#include <cstdlib>
#include <ctime>
#include <algorithm>

#define PI 3.1415926536
#define RND (2.0*((rand() % 100) / (double)100) - 1.0)

const double W = 900;
const double H = 900;

const double inf = 1e9;
const double eps = 1e-6;

/*
namespace Mat
{
	Material mirror(Vector3d(1, 1, 1), 0, 20, 0.8);
	Material stone(Vector3d(0.5, 0.5, 0.5), 0.8, 2, 0);
	Material redgloss(Vector3d(1.0, 0.3, 0.3), 0.2, 100, 0.3);
	Material bluegloss(Vector3d(0.3, 0.3, 1.0), 0.2, 100, 0.3);
};
*/

Vector3d camcr(double x, double y)
{
	float fovx = PI / 4;
	float fovy = (H / W) * fovx;
	return Vector3d(((2 * x - W) / W) * tan(fovx), -((2 * y - H) / H) * tan(fovy), -1.0);
}

// Casts a ray in a given scene and returns the color that the pixel should take on.
Vector3d CastRay(const Ray& ray, const Scene& s, int depth)
{
	auto iter = s.iter_begin();
	double intersection = inf;
	SceneObject* io = nullptr;
	while (iter != s.iter_end())
	{
		double is = (*iter)->Intersect(ray);
		if (is != 0 && is < intersection)
		{
			intersection = is;
			io = *iter;
		}
		iter++;
	}

	Vector3d color(0.8, 0.8, 1.0); // background color
	if (io && depth < 4)
	{
		const Material& mat = io->getMaterial();
		color = mat.color;

		auto light = s.getLights().begin();
		double diffuse_intensity = 0;
		double specular_intensity = 0;
		
		Vector3d ip = ray.getOrigin() + ray.getDirection() * intersection; // point of intersection
		Vector3d normal = io->getNormal(ip);

		// reflections
		Vector3d dmo = (ray.getDirection() - ray.getOrigin()).normalized();

		double r0 = pow((mat.refraction_index - 1) / (mat.refraction_index + 1), 2);
		double refl_prob = r0 + (1 - r0) * pow((1 + dmo.dot(normal)), 5); // Schlick's approximation of the Fresnel equation

		Vector3d reflectDir = (-dmo).reflect(normal);
		Ray reflectRay(ip + reflectDir * 1e-3, reflectDir);
		Vector3d reflectColor = CastRay(reflectRay, s, depth + 1);

		// refractions
		Vector3d refractDir = 

		while (light != s.getLights().end())
		{
			Vector3d lightHit = ((*light)->getPosition() - ip).normalized();
			double dot = MAX(0.0, normal.dot(lightHit)); // cos of angle between normal and lightHit

			// specular
			double spec = pow(MAX(0.0, -dmo.dot(lightHit.reflect(normal))), mat.specular_exponent);

			diffuse_intensity += dot * (*light)->getIntensity(); // diffuse lighting
			specular_intensity += (*light)->getIntensity() * spec; // specular lighting

			light++;
		}

		color *= diffuse_intensity;
		color += Vector3d(1, 1, 1) * specular_intensity * (1 - mat.softness);
		color += reflectColor /* * mat.reflect*/ * refl_prob;
	}
	return color;
}

RGBImage Render(const Scene& s)
{
	RGBImage img(W, H);
	img.Fill(RGBPixel(255, 255, 255));

	Vector3d view = s.getViewpoint();
	for (int y = 0; y < H; y++)
	{
		for (int x = 0; x < W; x++)
		{
			Vector3d color = CastRay(Ray(Vector3d(0, 0, 0), camcr(x, y)), s, 0);
			
			RGBPixel px;
			px.setColor(color);
			img.at(x, y) = px;
		}
	}

	return img;
}

int main(int argc, char* argv[])
{
	srand(time(NULL)); // initialize randomizer

	// Construct a scene
	Scene scene;

	SceneObject* s1 = new Sphere(Vector3d(0.5, 0.6, -1), 0.2, redgloss);
	SceneObject* s2 = new Sphere(Vector3d(-0.1, -0.4, -0.7), 0.2, mirror);
	SceneObject* s3 = new Sphere(Vector3d(0.4, -0.2, -0.9), 0.2, mirror);
	SceneObject* p1 = new Plane(Vector3d(0, -1, -3), Vector3d(0, 1, 0), 2.0, stone);

	scene.AddObject(s1).AddObject(s2).AddObject(s3).AddObject(p1);
	Light* l1 = new Light(Vector3d(0, 2, 3), 0.6);
	Light* l2 = new Light(Vector3d(-2, 2, -2), 0.3);
	Light* l3 = new Light(Vector3d(2, 1, 0), 0.3);
	scene.AddLight(l1).AddLight(l2).AddLight(l3);

	RGBImage res = Render(scene);
	res.WriteToFile("output.png");

	delete s1, s2, s3, l1, l2, p1;

	return 0;
}