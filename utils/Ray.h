#pragma once

#include "vec3.h"

class Ray
{
public:
	Ray(vec3 origin, vec3 dir);

	point origin() const;
	vec3 direction() const;

	static double point_plane_distance(point plane_origin, vec3 plane_normal, point hit_point);
	
	point at (double t) const;

private:
	point m_Origin;
	vec3 m_Direction;
};