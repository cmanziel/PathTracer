#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "../utils/Ray.h"
#include "../utils/rgb.h"

class Camera
{
public:
	Camera(int image_width);
	~Camera();

	int GetImageHeight();

	vec3 GetPosition() const;
	vec3 GetDirection() const;
	vec3** GetGrid() const;
	double GetFocalLength() const;
	double GetFarPlaneDistance() const;

	// reset viewportgrid on camera movement because the pixels' center coordinates will change
	void CreateViewportGrid();

private:
	double m_fov;
	double m_FocalLength; // near plane is distant m_FocalLength from m_Position
	double m_NearToFarDistance; // distance between near and far plane
	int m_ImageWidth;
	int m_ImageHeight;

	vec3 m_Position;
	vec3 m_Direction;
	vec3 m_CameraFront;

	// grid with the pixels' center coordinates to send the ray through from the camera position (also called camera center)
	vec3** m_Grid;
};