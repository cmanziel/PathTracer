#ifndef CAMERA_H
#define CAMERA_H

#define CHANNELS_PER_PIXEL 3

#include <stdio.h>
#include <stdlib.h>
#include <exception>

#include "pnglib.h"
#include "../Hittable/Hittable.h"

class Camera
{
public:
	Camera(const char* path);
	~Camera();

	int GetImageHeight();

	vec3 GetPosition() const;
	vec3 GetDirection() const;
	vec3** GetGrid() const;
	double GetFocalLength() const;
	double GetFarPlaneDistance() const;

	// reset viewportgrid on camera movement because the pixels' center coordinates will change
	void CreateViewportGrid();
	unsigned char* AllocPNGDatastream();

	void Render(std::vector<Hittable*> world);

private:
	double m_fov;
	double m_FocalLength; // near plane is distant m_FocalLength from m_Position
	double m_NearToFarDistance; // distance between near and far plane
	int m_ImageWidth;
	int m_ImageHeight;

	FILE* m_Image;
	const char* m_ImagePath;
	unsigned char* m_ImageData;

	Interval m_tInterval;

	vec3 m_Position;
	vec3 m_Direction;
	vec3 m_CameraFront;

	// grid with the pixels' center coordinates to send the ray through from the camera position (also called camera center)
	vec3** m_Grid;
};

#endif