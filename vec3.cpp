#include "vec3.h"

vec3::vec3()
	: x(0.0), y(0.0), z(0.0)
{

}

vec3::vec3(float x, float y, float z)
	: x(x), y(y), z(z)
{

}

vec3& vec3::operator=(const vec3& other)
{
	if (this == &other)
		return *this;

	this->x = other.x;
	this->y = other.y;
	this->z = other.z;
	
	return *this;
}

vec3& vec3::operator*=(const int scalar)
{
	this->x *= scalar;
	this->y *= scalar;
	this->z *= scalar;

	return *this;
}

vec3& vec3::operator*=(const float scalar)
{
	this->x *= scalar;
	this->y *= scalar;
	this->z *= scalar;

	return *this;
}

vec3& vec3::operator/=(const int scalar)
{
	this->x /= scalar;
	this->y /= scalar;
	this->z /= scalar;

	return *this;
}

vec3& vec3::operator-()
{
	vec3 result = vec3(-this->x, -this->y, -this->z);

	return result;
}

float vec3::length()
{
	return sqrt(x * x + y * y + z * z);
}

// arguments are set as const so they are not modyfied but a new vec3 is instantiated and returned
// its more useful to use this type of function definition instead of making it a member of the vec3 class
// because then the order of the vector operands in the operation doesn't matter
vec3 operator+(const vec3 u, const vec3 v)
{
	vec3 result = vec3();

	result.x = u.x + v.x;
	result.y = u.y + v.y;
	result.z = u.z + v.z;

	return result;
}

vec3 operator-(const vec3 u, const vec3 v)
{
	vec3 result = vec3();

	result.x = u.x - v.x;
	result.y = u.y - v.y;
	result.z = u.z - v.z;

	return result;
}

vec3 operator*(const float s, const vec3 v)
{
	vec3 result = vec3();

	result.x = s * v.x;
	result.y = s * v.y;
	result.z = s * v.z;

	return result;
}

vec3 operator*(const vec3 v, const float s)
{
	vec3 result;

	result.x = s * v.x;
	result.y = s * v.y;
	result.z = s * v.z;

	return result;
}

vec3 unit_vector(vec3 v)
{
	return v * (1 / v.length());
}

float dot(const vec3 u, const vec3 v)
{
	return u.x * v.x + u.y * v.y + u.z * v.z;
}

/*
u = u.x * i + u.y * j + u.z * k
v = v.x * i + v.y * j + v.z * k

u x v = (u.x * i + u.y * j + u.z * k) x (v.x * i + v.y * j + v.z * k) =
= u.x * v.x * (i x i) + u.x * v.y * (i x j) ecc.
*/

vec3 cross(const vec3& u, const vec3& v)
{
	vec3 result;

	result.x = u.y * v.z - u.z * v.y;
	result.y = u.z * v.x - u.x * v.z;
	result.z = u.x * v.y - u.y * v.x;

	return result;
}