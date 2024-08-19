#include <stdio.h>

#include "Hittable/Block/Block.h"
#include "Hittable/Sphere/Sphere.h"

#include "Camera/Camera.h"

/* TODO: 
	* calculate the correct viewport dimension based on focal_length and fov (degrees)
	* use the ray.at() function when calculating a point on a line, like is done to calculate the viewport orientation
	* problem when discriminant is = 0, so when the sphere center is onto the near plane
	* distinguish between inward and outward normal vectors when hitting objects with rays
*/

/* TODO:
	* problem when m_CameraFront stands in (0, 0, 0): the length of the vector is 0
*/

int main()
{
	const char* path = "D:\\39331\\Code\\C++\\PathTracer\\images\\path_10.png";

	try 
	{
		Camera camera(path);
		camera.CreateViewportGrid();

		//Sphere* sphere = new Sphere(vec3(0, 1, -10.0), 1.0);
		//Plane* plane = new Plane(vec3(0.0, 0.0, 0.0), vec3(0.0, 1.0, 0.0));
		//Block* block = new Block(vec3(0, 2, -8.0));
		//Sphere* sphere1 = new Sphere(vec3(0, 1, -5.0), 1.0);

		Block* block = new Block(vec3(0, 0, 1));

		//Sphere* sphere = new Sphere(vec3(0, 1, 6.0), 1.0);

		std::vector<Hittable*> objects;

		//objects.push_back(sphere);
		//objects.push_back(plane);
		objects.push_back(block);
		//objects.push_back(sphere1);

		camera.Render(objects);

		for (Hittable* obj : objects)
		{
			delete obj;
		}

		objects.clear();

	}
	catch (std::exception& e)
	{
		printf("%s\n", e.what());
		return -1;
	}

	return 0;
}