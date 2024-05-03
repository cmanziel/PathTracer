#include "Sphere.h"

bool Sphere::hit(const Ray& ray, const Camera& camera, float ray_tmin, float ray_tmax, hit_data hit_point_data)
{
	vec3 oc = ray.origin() - center;

	// -oc is the line from the viewport grid pixel's coordinates to the sphere's center
	// if dot product is < 0 then the angle between the camera direction and the direction of the ray from the grid to the sphere is 90 < angle < 270	
	// if the ray from grid to sphere has 90+ angle then the sphere is behind the viewport grid
	if (dot(-oc, camera.GetDirection()) < 0)
		return -1.0;

	auto a = dot(ray.direction(), ray.direction());
	auto b = 2.0 * dot(oc, ray.direction());
	auto c = dot(oc, oc) - radius * radius;
	auto discriminant = b * b - 4 * a * c;

	if (discriminant < 0)
		return false;

	auto sqrtd = sqrt(discriminant);

	// find if the root of the equation lies within the [ray_tmin, ray_tmax] interval
}