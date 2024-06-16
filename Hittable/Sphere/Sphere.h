#pragma once

#include "../Hittable.h"

class Sphere : public Hittable
{
public:
	Sphere();
	Sphere(const point center, double radius);

	bool Hit(const Ray& ray, const Camera& camera, double ray_tmin, double ray_tmax, hit_record& hit_point_data) override;
private:
	double m_Radius;
	vec3 m_Center;
};