/*****************************************************************************************
  Project      : 3D Game Engine
  Author       : Sam Tian
  Contributors :
******************************************************************************************/
#pragma once

#include <math.h>

struct Vec3
{
	float x, y, z;

	Vec3(){x = 0, y = 0, z = 0; }
	Vec3(const Vec3& rhs) { (*this) = rhs; }
	Vec3(float xx, float yy, float zz) { x = xx, y = yy, z = zz; }
	explicit Vec3(float xx) {x = y = z = xx;}

	// add or substract
	Vec3 operator+(const Vec3& rhs) const { return Vec3(x + rhs.x, y + rhs.y, z + rhs.z); }
	Vec3 operator-(const Vec3& rhs) const { return Vec3(x - rhs.x, y - rhs.y, z - rhs.z); }

	// multiply or divide by a scalar
	Vec3 operator*(float s) const {	return Vec3(x * s, y * s, z * s); }
	Vec3 operator/(float s) const {	return Vec3(x / s, y / s, z / s); }

	// get vector length
	float Length() const { return sqrtf((*this) * (*this)); }

	// calculate normalized vector
	Vec3 Normalize() const { return (*this) / Length(); }
	const Vec3&	NormalizeThis() { return (*this) = (*this) / Length(); }

	// dot product
	float operator*(const Vec3& rhs) const { return x * rhs.x + y * rhs.y + z * rhs.z; }

	// cross product
	Vec3 Cross(const Vec3& rhs) const {	return Vec3(y * rhs.z - z * rhs.y, z * rhs.x - x * rhs.z, x * rhs.y - y * rhs.x); }
};

template <typename T>
Vec3 operator*(T s, const Vec3& rhs)
{
	return (rhs * s);
}