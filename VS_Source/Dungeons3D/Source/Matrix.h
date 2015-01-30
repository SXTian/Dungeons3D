/*****************************************************************************************
  Project      : 3D Game Engine
  Author       : Sam Tian
  Contributors :
******************************************************************************************/
#pragma once

#include "Vector.h"

struct Mtx44
{
	float m[16];

	// constructor
	Mtx44();
	Mtx44(const float* mm);
	Mtx44(float m00, float m01, float m02, float m03, 
		float m10, float m11, float m12, float m13, 
		float m20, float m21, float m22, float m23, 
		float m30, float m31, float m32, float m33);

	// ---------------------------------------------------------------------------
	// accessors

	float& RowCol(unsigned row, unsigned col) {	return m[row * 4 + col]; }
	float RowCol(unsigned row, unsigned col) const { return m[row * 4 + col]; }


	// ---------------------------------------------------------------------------
	// operator overload

	// accessors
	float& operator()(unsigned row, unsigned col) { return RowCol(row, col); }
	float operator()(unsigned row, unsigned col) const { return RowCol(row, col); }

	Mtx44 operator+(const Mtx44& rhs) const;

	Mtx44 operator-(const Mtx44& rhs) const;

	Mtx44 operator*(float s) const;
	Mtx44 operator*(const Mtx44& rhs) const;

	Mtx44 operator/(float s) const;

	Vec4 operator*(const Vec4& v) const;

	// ---------------------------------------------------------------------------
	// member functions

	Mtx44 Mult(float s) const;

	const Mtx44& MultThis(float s);

	Mtx44 Mult(const Mtx44& rhs) const;
	const Mtx44& MultThis (const Mtx44& rhs);

	Vec4 MultVec(const Vec4& v) const;

	Mtx44 MultQuat(const Vec4& v) const;
	const Mtx44& MultQuatThis(const Vec4& v);

	Vec4 Quaternize() const;

	Mtx44 Transpose() const;
	const Mtx44& TransposeThis();

	Mtx44 Inverse() const;

	// the following functions will be applied to 'this' matrix
	const Mtx44& ZeroThis();
	const Mtx44& IdentityThis();
	const Mtx44& ScaleThis(float x, float y, float z);
	const Mtx44& RotateThis(float x, float y, float z, float angle);
	const Mtx44& TranslateThis(float x, float y, float z);

	// the following functions construct a matrix
	static Mtx44 Zero();
	static Mtx44 Identity();
	static Mtx44 Scale(float x, float y, float z);
	static Mtx44 Rotate(float x, float y, float z, float angle);
	static Mtx44 Translate(float x, float y, float z);
};

template <typename T>
Mtx44 operator*(T s, const Mtx44& rhs)
{
	return (rhs * s);
}