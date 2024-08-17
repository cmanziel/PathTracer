#pragma once

#include "../Plane/Plane.h"

#define FACES_PER_BLOCK 6

enum sides
{
	top, bottom, left, right, front, back
};

enum axis
{
	x, y, z
};

typedef struct
{
	Plane* plane;
	uint8_t edges[2]; // two of the "axis" enum's values
} face;

class Block : public Hittable
{
public:
	Block();
	Block(vec3 pos);
	~Block();

	vec3 GetWorldPosition() const;

	bool Hit(const Ray& ray, Interval tInterval, hit_record& hit_data) override;

	face m_Faces[FACES_PER_BLOCK];
private:
	vec3 m_WorldPosition;
	

	//face m_Faces[FACES_PER_BLOCK];
};

