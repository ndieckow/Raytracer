#pragma once

#include "Vector3d.h"

struct Material {
	Vector3d color;
	double softness;
	double specular_exponent;
	double reflect;
	double refraction_index;
	double transparency;

	Material(Vector3d c, double s, double se, double r, double ri, double t) : color(c), softness(s),
	                                                                           specular_exponent(se), reflect(r),
	                                                                           refraction_index(ri), transparency(t) {
	}
};

extern Material mirror, stone, redgloss, bluegloss, whiteWall, redWall, greenWall;
