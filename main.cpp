#include <stdio.h>
#include "pnglib.h"
#include "vec3.h"
#include "rgb.h"
#include "Camera.h"
#include "Ray.h"

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

	Camera* camera = new Camera(width);

	camera->CreateViewportGrid();

	int height = camera->GetImageHeight();

	int row_size = CHANNELS_PER_PIXEL * width + 1; // 1 byte for filter method
	int pixel_data_size = row_size * height * sizeof(unsigned char);
	unsigned char* pixel_data = (unsigned char*)malloc(pixel_data_size);

	if (pixel_data == NULL) {
		printf("pixel data not allocated");
		return -1;
	}

	for (int y = 0; y < height; y++)
	{
		int row_start = y * row_size;

		unsigned char filter_method = 0x00;

		pixel_data[row_start] = filter_method;

		for (int x = 0; x < width; x++)
		{
			// the ray origin is the point in the viewport through which the ray passes
			point ray_origin = camera->GetGrid()[y][x];

			vec3 dir = ray_origin - camera->GetPosition();

			rgb color = camera->SendRay(ray_origin, dir);

			// +1 because the row starts with a one-byte filter method
			int index = y * row_size + CHANNELS_PER_PIXEL * x + 1;

			pixel_data[index] = color.r; index++;
			pixel_data[index] = color.g; index++;
			pixel_data[index] = color.b; index++;
		}
	}

	FILE* image;
	const char* path = "D:\\39331\\Code\\C++\\PathTracer\\images\\path_7.png";
	
	// create_image does fopen and fclose
	image = create_image(pixel_data, path, width, height);

	free(pixel_data);
	delete camera;

	return 0;
}