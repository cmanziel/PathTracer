#include "Plane.h"

// default plane: zx plane
Plane::Plane()
	: m_Origin(vec3(0.0, 0.0, 0.0)), m_Normal(vec3(0.0, 1.0, 0.0))
{
	m_PlaneD = 0.0;
}

Plane::Plane(vec3 origin, vec3 normal, vec3 genA, vec3 genB)
	: m_Origin(origin), m_Normal(normal)
{
	m_Generators[0] = genA;
	m_Generators[1] = genB;

	m_PlaneD = -(m_Normal.x * m_Origin.x + m_Normal.y * m_Origin.y + m_Normal.z * m_Origin.z);
}

Plane::Plane(vec3 origin, vec3 normal)
	: m_Origin(origin), m_Normal(normal)
{
	m_PlaneD = -(m_Normal.x * m_Origin.x + m_Normal.y * m_Origin.y + m_Normal.z * m_Origin.z);
}

bool Plane::Hit(const Ray& ray, Interval tInterval, hit_record& hit_data)
{
	// intersection between line and plane: see quad.
	double a = m_Normal.x;
	double b = m_Normal.y;
	double c = m_Normal.z;
	double d = m_PlaneD;

	double t = -(a * ray.origin().x + b * ray.origin().y + c * ray.origin().z + m_PlaneD) / (a * ray.direction().x + b * ray.direction().y + c * ray.direction().z);

	if (!tInterval.ContainsClosed(t))
		return false;

	hit_data.normal = m_Normal;
	hit_data.point = ray.at(t);
	hit_data.t = t;

	return true;
}