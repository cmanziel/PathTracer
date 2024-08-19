#include "Block.h"

Block::Block()
	: m_WorldPosition(vec3(0, 0, 0)), m_SideLength(1.0)
{
	SetFaces();
}

Block::Block(vec3 pos)
	: m_WorldPosition(pos), m_SideLength(1.0)
{
	SetFaces();
}

Block::Block(vec3 pos, double sideLength)
	: m_WorldPosition(pos), m_SideLength(sideLength)
{
	SetFaces();
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

/* TODO: change Hit method
	* each face is a plane, so it has an origin and two generator vectors for every point in the face
	* to check if the ray intersection point is inside the face edges check if at least one of the generators' coefficients is greater than the length of the side of the block
*/

bool Block::Hit(const Ray& ray, Interval tInterval, hit_record& hit_data)
{
	// loop through faces and call their Hit method

	// keep track of the closest face hit by a ray
	double smallest_t = 0.0;
	hit_record closest;
	bool is_hit = false;

	for (int i = 0; i < FACES_PER_BLOCK; i++)
	{
		face f = m_Faces[i];
		vec3 genA = f.plane->m_Generators[0];
		vec3 genB = f.plane->m_Generators[1];
		vec3 fOrigin = f.plane->m_Origin;

		if (f.plane->Hit(ray, tInterval, hit_data))
		{
			vec3 hitPoint = ray.at(hit_data.t);

			double a, b;

			int genAc, genBc;
			// find which of the generators coordinates are suitable to compute the coefficients
			for (int i = 0; i < 3; i++)
			{
				if (genA[i] != 0)
					genAc = i;
				if (genB[i] != 0)
					genBc = i;
			}

			b = (hitPoint[genBc] * genA[genAc] - hitPoint[genAc] * genA[genBc] + fOrigin[genAc] * genA[genBc] - fOrigin[genBc] * genA[genAc]) / (genA[genAc] * genB[genBc] - genB[genAc]);
			a = (hitPoint[genAc] - b * genB[genAc] - fOrigin[genAc]) / genA[genAc];

			if (a < 0.0 || b < 0.0 || a > m_SideLength || b > m_SideLength)
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

	hit_data = closest;
	return true;
}

/* how to initialize a face plane:
	* for now just initialize a block whose top face is parllel to the xz plane
*/
void Block::SetFaces()
{
	// send origin and generators for each of the faces
	// top face
	vec3 origin = m_WorldPosition;
	vec3 normal = vec3(0.0, 1.0, 0.0);
	vec3 genA = vec3(1.0, 0.0, 0.0);
	vec3 genB = vec3(0.0, 0.0, 1.0);
	m_Faces[top].plane = new Plane(origin, normal, genA, genB);

	//bottom face
	normal = -normal;
	origin = origin + normal * m_SideLength;
	m_Faces[bottom].plane = new Plane(origin, normal, genA, genB);

	// left face
	normal = vec3(-1.0, 0.0, 0.0);
	origin = m_WorldPosition;
	genA = vec3(0.0, -1.0, 0.0);
	genB = vec3(0.0, 0.0, 1.0);
	m_Faces[left].plane = new Plane(origin, normal, genA, genB);

	// right face
	normal = -normal;
	origin = origin + normal * m_SideLength;
	m_Faces[right].plane = new Plane(origin, normal, genA, genB);

	// back face
	normal = vec3(0.0, 0.0, -1.0);
	origin = m_WorldPosition;
	genA = vec3(1.0, 0.0, 0.0);
	genB = vec3(0.0, -1.0, 0.0);
	m_Faces[back].plane = new Plane(origin, normal, genA, genB);

	// front face
	normal = -normal;
	origin = origin + normal * m_SideLength;
	m_Faces[front].plane = new Plane(origin, normal, genA, genB);
}