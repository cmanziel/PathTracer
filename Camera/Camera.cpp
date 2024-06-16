#include "Camera.h"

float aspect_ratio = 16.0 / 9;

// make viewport grid

Camera::Camera(int image_width)
{
	m_Position = vec3(3, 3, -8.5);
	//m_Direction = -m_Position;
	m_Direction = vec3(-1.0, -0.5, 0.0);
	m_fov = 45.0;
	m_FocalLength = 1.0;
	m_NearToFarDistance = 99.0;

	m_ImageWidth = image_width;
	m_ImageHeight = static_cast<int>((double)image_width / aspect_ratio);

	// calculate the grid dimensions here and instantiate the m_Grid bidimensional array (double pointer)
	m_Grid = (vec3**)malloc(sizeof(vec3*) * m_ImageHeight);

	if (m_Grid == NULL)
	{
		printf("error allocating pixel grid");
		return;
	}

	for (int y = 0; y < m_ImageHeight; y++)
	{
		m_Grid[y] = (vec3*)malloc(sizeof(vec3) * image_width);
	}
}

/* viewport grid and orientation according to camera position and direction
	* find camera_front: the point that's distant focal_length from the camera position on the line that has the direction of camera_direction
	* this line is the viewport plane normal, move on this plane the correct distances to find the grid's upper left corner
*/

void Camera::CreateViewportGrid()
{
	float viewport_height = 2.0;
	float viewport_width = viewport_width = viewport_height * (static_cast<double>(m_ImageWidth) / m_ImageHeight);

	vec3 world_up = vec3(0, 1, 0);

	m_Direction = unit_vector(m_Direction);

	// Ray camera_normal = Ray(m_Position, m_Direction)
	// point near_plane_origin = camera_normal.at(focal_length) = m_CameraFront
	m_CameraFront = m_Position + m_Direction * m_FocalLength;

	vec3 camera_left = unit_vector(cross(world_up, m_Direction));

	vec3 camera_up = unit_vector(cross(m_Direction, camera_left));

	// dir : (camera_left + camera_up) * (viewport_width / 2 + viewport_height / 2) + camera_front;

	// camera_front_translate is the grid upper left point on the plane generated by the camera_left and camera_up vector that passes from the origin, these point is then trnslated in front of the camera by adding m_CameraFront
	vec3 camera_front_translate = (viewport_width / 2) * camera_left + (viewport_height / 2) * camera_up;
	vec3 grid_upper_left_corner = m_CameraFront + camera_front_translate;

	double delta_u = viewport_width / m_ImageWidth;
	double delta_v = viewport_height / m_ImageHeight;

	vec3 grid_00 = grid_upper_left_corner + ((delta_u / 2) * -camera_left + (delta_v / 2) * -camera_up);

	for (int v = 0; v < m_ImageHeight; v++)
	{
		for (int u = 0; u < m_ImageWidth; u++)
		{
			vec3 pixel_center_pos = grid_00 + ((delta_u * u) * -camera_left + (delta_v * v) * -camera_up);

			m_Grid[v][u] = pixel_center_pos;
		}
	}
}

int Camera::GetImageHeight()
{
	return m_ImageHeight;
}

vec3 Camera::GetPosition() const
{
	return m_Position;
}

vec3 Camera::GetDirection() const
{
	return m_Direction;
}

vec3** Camera::GetGrid() const
{
	return m_Grid;
}

double Camera::GetFocalLength() const
{
	return m_FocalLength;
}

double Camera::GetFarPlaneDistance() const
{
	return m_FocalLength + m_NearToFarDistance;
}

Camera::~Camera()
{
	// iterate through grid and free the rows of coordinates
	for (int v = 0; v < m_ImageHeight; v++)
	{
		free(m_Grid[v]);
	}

	free(m_Grid);
}