#include "Plane.h"

// default plane: zx plane
Plane::Plane()
	: m_Origin(vec3(0.0, 0.0, 0.0)), m_Normal(vec3(0.0, 1.0, 0.0))
{

}

Plane::Plane(vec3 origin, vec3 normal)
	: m_Origin(origin), m_Normal(normal)
{
	// normal.x = a, normal.y = b, normal.z = c

	m_PlaneD = -(m_Normal.x * m_Origin.x + m_Normal.y * m_Origin.y + m_Normal.z * m_Origin.z);
}

bool Plane::Hit(const Ray& ray, const Camera& camera, double ray_tmin, double ray_tmax, hit_record& hit_data)
{
	vec3 oc = m_Origin - ray.origin();

	//if (dot(oc, camera.GetDirection()) < 0)
	//	return false;

	// intersection between line and plane: see quad.
	double a = m_Normal.x;
	double b = m_Normal.y;
	double c = m_Normal.z;
	double d = m_PlaneD;

	double t = -(a * ray.origin().x + b * ray.origin().y + c * ray.origin().z + m_PlaneD) / (a * ray.direction().x + b * ray.direction().y + c * ray.direction().z);

	if (t < ray_tmin || t > ray_tmax)
		return false;

	hit_data.normal = m_Normal;
	hit_data.point = ray.at(t);
	hit_data.t = t;

	return true;
}