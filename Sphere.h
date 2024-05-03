#include "Hittable.h"

class Sphere : public Hittable
{
public:

	bool hit(const Ray& ray, const Camera& camera, float ray_tmin, float ray_tmax, hit_data hit_point_data) override;
private:
	float radius;
	vec3 center;
};