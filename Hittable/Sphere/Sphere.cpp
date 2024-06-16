#include "Sphere.h"

Sphere::Sphere()
	: m_Center(vec3(0.0, 0.0, 0.0)), m_Radius(1.0)
{

}

Sphere::Sphere(const point center, double radius)
	: m_Center(center), m_Radius(radius)
{

}

bool Sphere::Hit(const Ray& ray, const Camera& camera, double ray_tmin, double ray_tmax, hit_record& hit_data)
{
	// center: sphere's center

	//vec3 oc = ray.origin() - center;
	vec3 oc = m_Center - ray.origin();

	// -oc is the line from the viewport grid pixel's coordinates to the sphere's center
	// if dot product is < 0 then the angle between the camera direction and the direction of the ray from the grid to the sphere is 90 < angle < 270
	// if the ray from grid to sphere has 90+ angle then the sphere is behind the viewport grid
	if (dot(oc, camera.GetDirection()) < 0)
		return false;

	auto a = dot(ray.direction(), ray.direction());
	auto b = -2.0 * dot(oc, ray.direction());
	auto c = dot(oc, oc) - m_Radius * m_Radius;
	auto discriminant = b * b - (long)4 * a * c;

	if (discriminant < 0)
		return false;

	auto sqrtd = sqrt(discriminant);

	// find if the root of the equation lies within the [ray_tmin, ray_tmax] interval
	// starting from the smallest

	double root = (-b - sqrtd) / (2 * a);

	if (root <= ray_tmin || root >= ray_tmax)
		root = (-b + sqrtd) / (2 * a);
	if (root <= ray_tmin || root >= ray_tmax)
		return false;

	hit_data.t = root;
	hit_data.point = ray.at(root);
	hit_data.normal = (hit_data.point - m_Center) / m_Radius;

	return true;
}