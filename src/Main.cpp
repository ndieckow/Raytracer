#include "Vector3d.h"
#include "Scene.h"
#include "Sphere.h"
#include "Light.h"
#include "Plane.h"
#include "RGBImage.h"

#include <cmath>
#include <cstdlib>
#include <ctime>

#define PI 3.1415926536
#define RND (2.0*((rand() % 100) / (double)100) - 1.0)

const double W = 900;
const double H = 900;

const double inf = 1e9;
const double eps = 1e-6;

Vector3d camcr(double x, double y) {
	float fovx = PI / 5;
	float fovy = (H / W) * fovx;
	return Vector3d(((2 * x - W) / W) * tan(fovx), -((2 * y - H) / H) * tan(fovy), -1.0);
}

std::pair<SceneObject*, double> Intersect(const Ray &ray, const Scene &s) {
	// Loop through all objects in the scene and check for intersection with ray.
	// The object closest to the camera is saved.
	auto iter = s.iter_begin();
	double intersection = inf;
	SceneObject *io = nullptr;
	while (iter != s.iter_end()) {
		double is = (*iter)->Intersect(ray);
		if (is != 0 && is < intersection) {
			intersection = is;
			io = *iter;
		}
		iter++;
	}
	return std::make_pair(io, intersection);
}

// Casts a ray in a given scene and returns the color that the pixel should take on.
Vector3d CastRay(const Ray &ray, const Scene &s, int depth) {
	// Loop through all objects in the scene and check for intersection with ray.
	// The object closest to the camera is saved.
	auto [io, intersection] = Intersect(ray, s);

	// Initialize with the scene's background color. If no object is hit, this is returned.
	Vector3d color{s.getBackgroundColor()};
	if (io && depth < 4) {
		const Material &mat = io->getMaterial();
		color = mat.color;

		auto light = s.getLights().begin();
		double diffuse_intensity = 0;
		double specular_intensity = 0;

		Vector3d ip = ray.at(intersection); // point of intersection
		Vector3d normal = io->getNormal(ip);

		// Get the vector that starts at the origin and points toward the intersection point, normalized.
		Vector3d dmo = (ip - ray.getOrigin()).normalized();

		double r0 = pow((mat.refraction_index - 1) / (mat.refraction_index + 1), 2);
		double refl_prob = r0 + (1 - r0) * pow((1 + dmo.dot(normal)), 5);
		// Schlick's approximation of the Fresnel equation

		// Compute the direction of the reflected ray.
		Vector3d reflectDir = (-dmo).reflect(normal);
		// Start the ray a little later in order to avoid unwanted intersections.
		Ray reflectRay(ip + reflectDir * 1e-3, reflectDir);
		Vector3d reflectColor = CastRay(reflectRay, s, depth + 1);

		while (light != s.getLights().end()) {
			// Vector from intersection point to light.
			Vector3d lightHitUnnorm = (*light)->getPosition() - ip;
			Vector3d lightHit = lightHitUnnorm.normalized();
			Ray lightRay{(*light)->getPosition(), -lightHit};

			// Check for intersection
			auto [io, intersection] = Intersect(lightRay, s);
			if (intersection < lightHitUnnorm.norm() - 1e-3) { light++; continue; }

			// cos of angle between normal and lightHit
			double lightNormalCos = MAX(0.0, normal.dot(lightHit));

			// Reflect the light hit vector wrt the surface normal.
			Vector3d lightHitReflect = lightHit.reflect(normal);
			// Compute cosine of angle between lightHitReflect and ray pointing toward ray origin.
			double lightRayOriginCos = -dmo.dot(lightHitReflect);
			// Specular exponent determines how smooth the specular light will be.
			// High exponent: Pointy and smaller
			// Low exponent: Smooth and larger
			double spec = pow(MAX(0.0, lightRayOriginCos), mat.specular_exponent);

			diffuse_intensity += lightNormalCos * (*light)->getIntensity(); // diffuse lighting
			specular_intensity += (*light)->getIntensity() * spec; // specular lighting

			light++;
		}

		color *= diffuse_intensity;
		color += Vector3d(1, 1, 1) * specular_intensity * (1 - mat.softness);
		color += reflectColor * mat.reflect * refl_prob;
	}
	return color;
}

RGBImage Render(const Scene &s) {
	RGBImage img(W, H);
	img.Fill(RGBPixel(255, 255, 255));

	for (int y = 0; y < H; y++) {
		for (int x = 0; x < W; x++) {
			Ray ray{Vector3d{0, 0, 0}, camcr(x, y)};
			Vector3d color = CastRay(ray, s, 0);
			RGBPixel px{color};
			img.at(x, y) = px;
		}
	}

	return img;
}

int main(int argc, char *argv[]) {
	srand(time(nullptr)); // initialize randomizer

	// Construct a scene
	Scene scene{0.8, 0.8, 0.8};

	// Add some spheres
	SceneObject *s1 = new Sphere(Vector3d(0, -2 + 0.5, -3), 0.5, redgloss);
	SceneObject *s2 = new Sphere(Vector3d(-1.0, -2 + 1, -4), 1, mirror);
	SceneObject *s3 = new Sphere(Vector3d(1.0, -2 + 0.5, -4), 0.5, mirror);

	// Add a room without ceiling
	SceneObject *floor = new Plane(Vector3d(0, -2, -3), Vector3d(0, 1, 0), 2.0, whiteWall); // Floor
	SceneObject *leftWall = new Plane(Vector3d(-2, 0, -3), Vector3d(1, 0, 0), 2.0, redWall); // Left wall
	SceneObject *rightWall = new Plane(Vector3d(2, 0, -3), Vector3d(-1, 0, 0), 2.0, greenWall); // Right wall
	SceneObject *backWall = new Plane(Vector3d(0, 0, -5), Vector3d(0, 0, 1), 2.0, whiteWall); // Back wall
	SceneObject *ceiling = new Plane(Vector3d(0, 2, -3), Vector3d(0, -1, 0), 2.0, whiteWall); // Ceiling

	scene.AddObject(s1).AddObject(s2).AddObject(s3).AddObject(floor).AddObject(leftWall).AddObject(rightWall).
			AddObject(backWall).AddObject(ceiling);
	Light *l1 = new Light(Vector3d(0, 1.8, -3), 1.0);
	//Light* l2 = new Light(Vector3d(-2, 2, -2), 0.3);
	//Light* l3 = new Light(Vector3d(2, 1, 0), 0.3);
	scene.AddLight(l1);

	RGBImage res = Render(scene);
	res.WriteToFile("output.png");

	return 0;
}
