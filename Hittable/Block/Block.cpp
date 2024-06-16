#include "Block.h"

void setFacePlane(Block* block, uint8_t side);

Block::Block()
	: m_WorldPosition(vec3(0, 0, 0))
{
	for (int i = 0; i < FACES_PER_BLOCK; i++)
	{
		setFacePlane(this, i);
	}
}

Block::Block(vec3 pos)
	: m_WorldPosition(pos)
{
	for (int i = 0; i < FACES_PER_BLOCK; i++)
	{
		setFacePlane(this, i);
	}
}

Block::~Block()
{
	for (int i = 0; i < FACES_PER_BLOCK; i++)
	{
		delete m_Faces[i].plane;
	}
}

vec3 Block::GetWorldPosition() const
{
	return m_WorldPosition;
}

bool Block::Hit(const Ray& ray, const Camera& camera, double ray_tmin, double ray_tmax, hit_record& hit_data)
{
	// loop through faces and call their Hit method

	// keep track of the closest face hit by a ray
	double smallest_t = 0.0;
	hit_record closest;
	bool is_hit = false;

	for (int i = 0; i < FACES_PER_BLOCK; i++)
	{
		face f = m_Faces[i];

		if (f.plane->Hit(ray, camera, ray_tmin, ray_tmax, hit_data))
		{
			// a face plane might be hit by the ray but it should be checked if it was inside the face edges
			vec3 edgeOffsets(1.0, 1.0, 1.0);

			if (hit_data.point[f.edges[0]] < f.plane->m_Origin[f.edges[0]] || hit_data.point[f.edges[0]] > f.plane->m_Origin[f.edges[0]] + edgeOffsets[f.edges[0]]
				|| hit_data.point[f.edges[1]] < f.plane->m_Origin[f.edges[1]] || hit_data.point[f.edges[1]] > f.plane->m_Origin[f.edges[1]] + edgeOffsets[f.edges[1]])
				continue;

			is_hit = true;

			if (hit_data.t < smallest_t || smallest_t == 0.0)
			{
				closest = hit_data;
				smallest_t = hit_data.t;
			}
		}
	}

	if (!is_hit)
		return false;

	// set the ray hit data to the one of the closest point, otherwise it would be the one of the last point hit
	hit_data = closest;

	return true;
}

//bool Block::Hit(const Ray& ray, const Camera& camera, double ray_tmin, double ray_tmax, hit_record& hit_data)
//{
//	// check if ray intersects the block
//	// 6 planes, see if ray intersects plane at a point which is inside the face edges
//	// the sides are unit length
//	// a block spans downwards on the y axis, frontwards on the z axis and rightwards on the x axis from it world position point
//
//	vec3 oc = m_WorldPosition - ray.origin();
//
//	if (dot(oc, camera.GetDirection()) < 0)
//		return false;
//
//	hit_record closest;
//	double smallest_t = 0.0; // initialized to 0.0 because it is less than the focal length
//
//	for (int i = 0; i < FACES_PER_BLOCK; i++)
//	{
//		face f = m_Faces[i];
//
//		double t = (f.origin[f.plane] - ray.origin()[f.plane]) / ray.direction()[f.plane];
//
//		if (t < ray_tmin || t > ray_tmax)
//			return false;
//
//		point intersection = ray.at(t);
//
//		vec3 edgesOffsets = vec3(0.0, 0.0, 0.0);
//		double edge1 = f.edges[0];
//		double edge2 = f.edges[1];
//
//		edgesOffsets[edge1] = 1.0;
//		edgesOffsets[edge2] = 1.0;
//
//		if (intersection[edge1] < f.origin[edge1] || intersection[edge1] > f.origin[edge1] + edgesOffsets[edge1]
//			|| intersection[edge2] < f.origin[edge2] || intersection[edge2] > f.origin[edge2] + edgesOffsets[edge2])
//			continue;
//
//		if (t < smallest_t || smallest_t == 0.0)
//		{
//			smallest_t = t;
//			
//		}
//	}
//
//	hit_data = closest;
//
//	return true;
//}

/*
* top
 	gen1 = vec3(0.0, 0.0, 1.0);
	gen2 = vec3(1.0, 0.0, 0.0);
	origin = m_WorldPosition;

* left
	gen1 = vec3(0.0, -1.0, 0.0);
	gen2 = vec3(0.0, 0.0, 1.0);
	origin = m_WorldPosition

*/

//double t = (origin.z - ray.origin().z) / ray.direction().z;

//if (t < ray_tmin || t > ray_tmax)
//	return false;

//point intersection = ray.at(t);

//if (intersection.x < m_WorldPosition.x || intersection.x > m_WorldPosition.x + 1.0)
//	return false;

//if (intersection.y < m_WorldPosition.y - 1.0 || intersection.y > m_WorldPosition.y)
//	return false;

//hit_data.t = t;
//hit_data.point = intersection;
//hit_data.normal = vec3(0.0, 0.0, 1.0); // normal to the front face of a block: vec3(0.0, 0.0, 1.0)

void setFacePlane(Block* block, uint8_t side)
{
	face f = block->m_Faces[side];
	//Plane* face = block->m_Faces[side];
	vec3 blockPos = block->GetWorldPosition();
	uint8_t edges[2];

	vec3 faceNormal;
	vec3 faceOrigin;

	switch (side)
	{
		case top:
		{
			faceOrigin = blockPos;
			faceNormal = vec3(0.0, 1.0, 0.0);
			edges[0] = x;
			edges[1] = z;
		} break;
		case bottom:
		{
			faceOrigin = blockPos + vec3(0.0, -1.0, 0.0);
			faceNormal = vec3(0.0, -1.0, 0.0);
			edges[0] = x;
			edges[1] = z;
		} break;
		case left:
		{
			faceOrigin = blockPos + vec3(0.0, -1.0, 0.0);
			faceNormal = vec3(-1.0, 0.0, 0.0);
			edges[0] = z;
			edges[1] = y;
		} break;
		case right:
		{
			faceOrigin = blockPos + vec3(1.0, -1.0, 0.0);
			faceNormal = vec3(1.0, 0.0, 0.0);
			edges[0] = z;
			edges[1] = y;
		} break;
		case front:
		{
			faceOrigin = blockPos + vec3(0.0, -1.0, 1.0);
			faceNormal = vec3(0.0, 0.0, 1.0);
			edges[0] = x;
			edges[1] = y;
		} break;
		case back:
		{
			faceOrigin = blockPos + vec3(0.0, -1.0, 0.0);
			faceNormal = vec3(0.0, 0.0, -1.0);
			edges[0] = x;
			edges[1] = y;
		} break;
	}

	block->m_Faces[side].plane = new Plane(faceOrigin, faceNormal);
	block->m_Faces[side].edges[0] = edges[0];
	block->m_Faces[side].edges[1] = edges[1];
}