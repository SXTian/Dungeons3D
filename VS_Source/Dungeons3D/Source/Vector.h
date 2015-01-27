/*****************************************************************************************
Project      : 3D Game Engine
Author       : Sam Tian
Contributors :
******************************************************************************************/
#pragma once

#include "Math.h"

struct Vec4
{
	float x, y, z, w;

	Vec4() : x(0.0f), y(0.0f), z(0.0f), w(1.0f) {}
	Vec4(const Vec4& rhs) : x(rhs.x), y(rhs.y), z(rhs.z), w(rhs.w) {}
	Vec4(float xx, float yy, float zz, float ww = 1.0f) : x(xx), y(yy), z(zz), w(ww) {}
	explicit Vec4(float xx) : x(xx), y(xx), z(xx) , w(1.0f){}

	// add or substract
	Vec4 operator+(const Vec4& rhs) const { return Vec4(x + rhs.x, y + rhs.y, z + rhs.z, w); }
	Vec4 operator-(const Vec4& rhs) const { return Vec4(x - rhs.x, y - rhs.y, z - rhs.z, w); }

	// multiply or divide by a scalar
	Vec4 operator*(float s) const {	return Vec4(x * s, y * s, z * s, w); }
	Vec4 operator/(float s) const {	return Vec4(x / s, y / s, z / s, w); }

	// get vector length
	float Length() const { return sqrtf((*this) * (*this)); }

	// dot product
	float operator*(const Vec4& rhs) const { return x * rhs.x + y * rhs.y + z * rhs.z; }

	// cross product
	Vec4 Cross(const Vec4& rhs) const {	return Vec4(y * rhs.z - z * rhs.y, z * rhs.x - x * rhs.z, x * rhs.y - y * rhs.x, w); }

	// calculate normalized vector
	Vec4 Normalize() const { return (*this) / Length(); }
	const Vec4&	NormalizeThis() { return (*this) = (*this) / Length(); }

	//	Construct a quaternion with (x component, y component, z component, degrees) as (x, y, z, w)
	Vec4 Quaternize() const { return Vec4(x * SinLookup(w / 2.0f), y * SinLookup(w / 2.0f), z * SinLookup(w / 2.0f), CosLookup(w / 2.0f)); }

	const Vec4& QuaternizeThis() { return (*this) = (*this).Quaternize(); }

	//	Multiply with another quaternion, both must be Quaternized!! (or you get garbage result)
	Vec4 MultQuat(const Vec4& rhs) const { return Vec4(w * rhs.x + x * rhs.w + y * rhs.z - z * rhs.y,
														w * rhs.y + y * rhs.w + z * rhs.x - x * rhs.z,
														w * rhs.z + z * rhs.w + x * rhs.y - y * rhs.x,
														w * rhs.w - x * rhs.x - y * rhs.y - z * rhs.z);}

	const Vec4& MultQuatThis(const Vec4& rhs) { return (*this) = (*this).MultQuat(rhs); }

};

template <typename T>
Vec4 operator*(T s, const Vec4& rhs)
{
	return (rhs * s);
}