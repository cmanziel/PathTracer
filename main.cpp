#include <stdio.h>
#include "pnglib.h"
#include <vector>
#include "utils/vec3.h"
#include "utils/rgb.h"
#include "Camera/Camera.h"
#include "utils/Ray.h"
#include "Hittable/Block/Block.h"
#include "Hittable/Sphere/Sphere.h"

#define CHANNELS_PER_PIXEL 3

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
	int width = 256;

	// send rays through camera grid and see if they intersect a sphere

	Camera camera(width);

	camera.CreateViewportGrid();

	int height = camera.GetImageHeight();

	int row_size = CHANNELS_PER_PIXEL * width + 1; // 1 byte for filter method
	int pixel_data_size = row_size * height * sizeof(unsigned char);
	unsigned char* pixel_data = (unsigned char*)malloc(pixel_data_size);

	if (pixel_data == NULL) {
		printf("pixel data not allocated");
		return -1;
	}

	Sphere* sphere = new Sphere(vec3(0, 1, -10.0), 1.0);
	Block* block = new Block(vec3(0, 2, -8.0));
	Plane* plane = new Plane(vec3(0.0, 0.0, 0.0), vec3(0.0, 1.0, 0.0));

	std::vector<Hittable*> objects;

	objects.push_back(sphere);
	objects.push_back(block);
	objects.push_back(plane);

	for (int y = 0; y < height; y++)
	{
		int row_start = y * row_size;

		unsigned char filter_method = 0x00;

		pixel_data[row_start] = filter_method;

		for (int x = 0; x < width; x++)
		{
			point rayOrigin = camera.GetGrid()[y][x];
			vec3 dir = rayOrigin - camera.GetPosition();

			Ray ray(rayOrigin, dir);

			hit_record hitData;
			rgb color;

			// problem for all the objects it has to be checked if the ray interescted one of them, and which of them is closer

			hit_record closest; // hitData.t goes here, check it is still null after looping through the objects, if it is nothing was hit by that particular ray
			double smallest_t = 0.0;
			bool hit_anything = false;

			for (Hittable* obj : objects)
			{
				if (obj->Hit(ray, camera, camera.GetFocalLength(), camera.GetFarPlaneDistance(), hitData))
				{
					hit_anything = true;

					if (hitData.t < smallest_t || smallest_t == 0.0)
					{
						smallest_t = hitData.t;
						closest = hitData;
					}
				}

				// if nothing was hit set the bcakground color for this pixel's color
				if (!hit_anything)
					color = rgb(255, 255, 255);
				else
				{
					color.r = static_cast<uint8_t>(255 * (closest.normal.x + 1) / 2);
					color.g = static_cast<uint8_t>(255 * (closest.normal.y + 1) / 2);
					color.b = static_cast<uint8_t>(255 * (closest.normal.z + 1) / 2);
				}
			}

			unsigned int index = y * row_size + CHANNELS_PER_PIXEL * x + 1;

			pixel_data[index] = color.r; index++;
			pixel_data[index] = color.g; index++;
			pixel_data[index] = color.b; index++;
		}
	}

	for (Hittable* obj : objects)
	{
		delete obj;
	}

	objects.clear();

	FILE* image;
	const char* path = "D:\\39331\\Code\\C++\\PathTracer\\images\\path_8.png";
	
	// create_image does fopen and fclose
	image = create_image(pixel_data, path, width, height);

	free(pixel_data);

	return 0;
}