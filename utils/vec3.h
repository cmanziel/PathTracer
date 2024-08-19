#pragma once

#include <math.h>
#include <assert.h>

class vec3
{
public:
	vec3();
	vec3(double x, double y, double z);

	vec3& operator=(const vec3& other);
	vec3& operator*=(const int scalar);
	vec3& operator*=(const double scalar);
	vec3& operator/= (const int scalar);
	vec3& operator-();
	double& operator[](const int i);

	double length();
	vec3 normalize(); // return a new normalized vector

	double x;
	double y;
	double z;

private:
};

vec3 operator+(const vec3 u, const vec3 v);
vec3 operator-(const vec3 u, const vec3 v);
vec3 operator*(const double s, const vec3 v);
vec3 operator*(const vec3 v, const double s);
vec3 operator/(const vec3 v, const double s);


vec3 unit_vector(vec3 v);

double dot(const vec3 u, const vec3 v);
vec3 cross(const vec3& u, const vec3& v);

typedef vec3 point;