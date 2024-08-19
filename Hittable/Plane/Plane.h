#pragma once

#include "../Hittable.h"

class Plane : public Hittable
{
public:
	Plane();
	Plane(vec3 origin, vec3 normal);
	Plane(vec3 origin, vec3 normal, vec3 genA, vec3 genB);


	~Plane() = default;

	bool Hit(const Ray& ray, Interval tInterval, hit_record& hit_point_data) override;

	vec3 m_Origin;
	vec3 m_Normal;
	vec3 m_Generators[2];
	double m_PlaneD;

private:
};

