#include "Ray.h"

Ray::Ray(vec3 origin, vec3 direction)
{
	m_Origin = origin;

	m_Direction = unit_vector(direction);
}

point Ray::origin() const
{
	return m_Origin;
}

vec3 Ray::direction() const
{
	return m_Direction;
}

// find the point that's distant t from the origin in the ray's direction
point Ray::at (double t) const
{
	return m_Origin + t * m_Direction;
}

// origin(X0): a plane can determined by a normal vector and a point: origin
double Ray::point_plane_distance(point origin, vec3 plane_normal, point hit_point)
{
	double a = plane_normal.x;
	double b = plane_normal.y;
	double c = plane_normal.z;

	double d = -(a * origin.x + b * origin.y + c * origin.z);
	double dist = abs((long)(a * hit_point.x + b * hit_point.y + c * hit_point.z + d)) / sqrt(a * a + b * b + c * c);

	return dist;
}