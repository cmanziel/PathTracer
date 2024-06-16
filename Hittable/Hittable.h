#pragma once

#include "../Camera/Camera.h"

// parent class for hittable objects
// every different hittable object (spheres, prisms, or other forms) implements is own hit method

typedef struct
{
	point point;
	vec3 normal;
	float t;
} hit_record;

class Hittable
{
public:
	virtual bool Hit(const Ray& ray, const Camera& camera, double ray_tmin, double ray_tmax, hit_record& hit_point_data) = 0;

	virtual ~Hittable() = default;

private:

};

