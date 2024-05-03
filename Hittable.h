#pragma once

#include "Camera.h"

// parent class for hittable objects
// every different hittable object (spheres, prisms, or other forms) implements is own hit method

typedef struct
{
	point point;
	vec3 normal;
	float t;
} hit_data;

class Hittable
{
public:
	virtual bool hit(const Ray& ray, const Camera& camera, float ray_tmin, float ray_tmax, hit_data hit_point_data) = 0;

	virtual ~Hittable() = default;
};

