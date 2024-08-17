#include "Sphere.h"

Sphere::Sphere()
	: m_Center(vec3(0.0, 0.0, 0.0)), m_Radius(1.0)
{

}

Sphere::Sphere(const point center, double radius)
	: m_Center(center), m_Radius(radius)
{

}

bool Sphere::Hit(const Ray& ray, Interval tInterval, hit_record& hit_data)
{
	//vec3 oc = ray.origin() - center;
	vec3 oc = m_Center - ray.origin();

	auto a = dot(ray.direction(), ray.direction());
	//auto b = -2.0 * dot(oc, ray.direction());
	auto b = -2.0 * dot(ray.direction(), oc);
	auto c = dot(oc, oc) - m_Radius * m_Radius;
	auto discriminant = b * b - (long)4 * a * c;

	if (discriminant < 0)
		return false;

	auto sqrtd = sqrt(discriminant);

	// find if the root of the equation lies within the [ray_tmin, ray_tmax] interval
	// starting from the smallest

	double root = (-b - sqrtd) / (2 * a);

	if (!tInterval.ContainsOpened(root))
		root = (-b + sqrtd) / (2 * a);
	if (!tInterval.ContainsOpened(root))
		return false;

	hit_data.t = root;
	hit_data.point = ray.at(root);
	hit_data.normal = (hit_data.point - m_Center) / m_Radius;

	return true;
}