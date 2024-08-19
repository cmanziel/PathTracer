#pragma once

#include <vector>
#include "../utils/Ray.h"
#include "../utils/rgb.h"
#include "../utils/Interval/Interval.h"

// parent class for hittable objects
// every different hittable object (spheres, prisms, or other forms) implements is own hit method

typedef struct
{
	point point;
	vec3 normal;
	double t;
} hit_record;

class Hittable
{
public:
	virtual bool Hit(const Ray& ray, Interval tInterval, hit_record& hit_point_data) = 0;

	virtual ~Hittable() = default;

private:
};

