#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "Ray.h"
#include "rgb.h"

class Camera
{
public:
	Camera(int image_width);
	~Camera();

	int GetImageHeight();

	vec3 GetPosition() const;
	vec3 GetDirection() const;
	vec3** GetGrid();

	rgb SendRay(point origin, vec3 Ray);

	// reset viewportgrid on camera movement because the pixels' center coordinates will change
	void CreateViewportGrid();

private:
	float m_fov;
	float m_FocalLength; // near plane is distant m_FocalLength from m_Position
	float m_NearToFarDistance; // far plane distance from camera
	int m_ImageWidth;
	int m_ImageHeight;

	vec3 m_Position;
	vec3 m_Direction;
	vec3 m_CameraFront;

	// grid with the pixels' center coordinates to send the ray through from the camera position (also called camera center)
	vec3** m_Grid;
};

// check if ray intersects a sphere centered in center
float is_hit(Ray ray, vec3 center, float radius, Camera* camera);