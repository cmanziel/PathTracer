#pragma once

#include <math.h>

class vec3
{
public:
	vec3();
	vec3(float x, float y, float z);

	vec3& operator=(const vec3& other);
	vec3& operator*=(const int scalar);
	vec3& operator*=(const float scalar);
	vec3& operator/= (const int scalar);
	vec3& operator-();

	float length();

	float x;
	float y;
	float z;
};

vec3 operator+(const vec3 u, const vec3 v);
vec3 operator-(const vec3 u, const vec3 v);
vec3 operator*(const float s, const vec3 v);
vec3 operator*(const vec3 v, const float s);

vec3 unit_vector(vec3 v);

float dot(const vec3 u, const vec3 v);
vec3 cross(const vec3& u, const vec3& v);

typedef vec3 point;