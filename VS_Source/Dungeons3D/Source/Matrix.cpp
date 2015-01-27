/*****************************************************************************************
  Project      : 3D Game Engine
  Author       : Sam Tian
  Contributors :
******************************************************************************************/
#include "Matrix.h"
#include "Math.h"

Mtx44::Mtx44()
{
}

// ---------------------------------------------------------------------------

Mtx44::Mtx44(const float* mm)
{	
	RowCol(0, 0) = mm[ 0]; RowCol(0, 1) = mm[ 1]; RowCol(0, 2) = mm[ 2]; RowCol(0, 3) = mm[ 3]; 
	RowCol(1, 0) = mm[ 4]; RowCol(1, 1) = mm[ 5]; RowCol(1, 2) = mm[ 6]; RowCol(1, 3) = mm[ 7]; 
	RowCol(2, 0) = mm[ 8]; RowCol(2, 1) = mm[ 9]; RowCol(2, 2) = mm[10]; RowCol(2, 3) = mm[11]; 
	RowCol(3, 0) = mm[12]; RowCol(3, 1) = mm[13]; RowCol(3, 2) = mm[14]; RowCol(3, 3) = mm[15]; 
}

// ---------------------------------------------------------------------------

Mtx44::Mtx44(float m00, float m01, float m02, float m03, 
			 float m10, float m11, float m12, float m13, 
			 float m20, float m21, float m22, float m23, 
			 float m30, float m31, float m32, float m33)
{
	RowCol(0, 0) = m00; RowCol(0, 1) = m01; RowCol(0, 2) = m02; RowCol(0, 3) = m03; 
	RowCol(1, 0) = m10; RowCol(1, 1) = m11; RowCol(1, 2) = m12; RowCol(1, 3) = m13; 
	RowCol(2, 0) = m20; RowCol(2, 1) = m21; RowCol(2, 2) = m22; RowCol(2, 3) = m23; 
	RowCol(3, 0) = m30; RowCol(3, 1) = m31; RowCol(3, 2) = m32; RowCol(3, 3) = m33;	
}

// ---------------------------------------------------------------------------
// operators overload

Mtx44 Mtx44::operator+(const Mtx44& rhs) const
{
	return Mtx44(RowCol(0, 0) + rhs.RowCol(0, 0), RowCol(0, 1) + rhs.RowCol(0, 1), RowCol(0, 2) + rhs.RowCol(0, 2), RowCol(0, 3) + rhs.RowCol(0, 3), 
				 RowCol(1, 0) + rhs.RowCol(1, 0), RowCol(1, 1) + rhs.RowCol(1, 1), RowCol(1, 2) + rhs.RowCol(1, 2), RowCol(1, 3) + rhs.RowCol(1, 3), 
				 RowCol(2, 0) + rhs.RowCol(2, 0), RowCol(2, 1) + rhs.RowCol(2, 1), RowCol(2, 2) + rhs.RowCol(2, 2), RowCol(2, 3) + rhs.RowCol(2, 3), 
				 RowCol(3, 0) + rhs.RowCol(3, 0), RowCol(3, 1) + rhs.RowCol(3, 1), RowCol(3, 2) + rhs.RowCol(3, 2), RowCol(3, 3) + rhs.RowCol(3, 3));
}

// ---------------------------------------------------------------------------

Mtx44 Mtx44::operator-(const Mtx44& rhs) const
{
	return Mtx44(RowCol(0, 0) - rhs.RowCol(0, 0), RowCol(0, 1) - rhs.RowCol(0, 1), RowCol(0, 2) - rhs.RowCol(0, 2), RowCol(0, 3) - rhs.RowCol(0, 3), 
				 RowCol(1, 0) - rhs.RowCol(1, 0), RowCol(1, 1) - rhs.RowCol(1, 1), RowCol(1, 2) - rhs.RowCol(1, 2), RowCol(1, 3) - rhs.RowCol(1, 3), 
				 RowCol(2, 0) - rhs.RowCol(2, 0), RowCol(2, 1) - rhs.RowCol(2, 1), RowCol(2, 2) - rhs.RowCol(2, 2), RowCol(2, 3) - rhs.RowCol(2, 3), 
				 RowCol(3, 0) - rhs.RowCol(3, 0), RowCol(3, 1) - rhs.RowCol(3, 1), RowCol(3, 2) - rhs.RowCol(3, 2), RowCol(3, 3) - rhs.RowCol(3, 3));
}

// ---------------------------------------------------------------------------

Vec4 Mtx44::operator*(const Vec4& v) const
{	
	return MultVec(v);
}

// ---------------------------------------------------------------------------

Mtx44 Mtx44::operator*(float s) const
{	
	return this->Mult(s);
}

// ---------------------------------------------------------------------------

Mtx44 Mtx44::operator*(const Mtx44& rhs) const
{	
	return (*this).Mult(rhs);
}

// ---------------------------------------------------------------------------

Mtx44 Mtx44::operator/(float s) const
{	
	return (*this).Mult(1.0f / s);
}

// ---------------------------------------------------------------------------

Mtx44 Mtx44::Mult(float s) const
{
	return Mtx44(s * RowCol(0, 0), s * RowCol(0, 1), s * RowCol(0, 2), s * RowCol(0, 3), 
				 s * RowCol(1, 0), s * RowCol(1, 1), s * RowCol(1, 2), s * RowCol(1, 3), 
				 s * RowCol(2, 0), s * RowCol(2, 1), s * RowCol(2, 2), s * RowCol(2, 3), 
				 s * RowCol(3, 0), s * RowCol(3, 1), s * RowCol(3, 2), s * RowCol(3, 3));
}

// ---------------------------------------------------------------------------

const Mtx44& Mtx44::MultThis(float s)
{
	RowCol(0, 0) *= s; RowCol(0, 1) *= s; RowCol(0, 2) *= s; RowCol(0, 3) *= s;
	RowCol(1, 0) *= s; RowCol(1, 1) *= s; RowCol(1, 2) *= s; RowCol(1, 3) *= s;
	RowCol(2, 0) *= s; RowCol(2, 1) *= s; RowCol(2, 2) *= s; RowCol(2, 3) *= s;
	RowCol(3, 0) *= s; RowCol(3, 1) *= s; RowCol(3, 2) *= s; RowCol(3, 3) *= s;
	
	return (*this);
}

// ---------------------------------------------------------------------------

Mtx44 Mtx44::Mult(const Mtx44& rhs) const
{
	return Mtx44(
		RowCol(0, 0) * rhs.RowCol(0, 0) + RowCol(0, 1) * rhs.RowCol(1, 0) + RowCol(0, 2) * rhs.RowCol(2, 0) + RowCol(0, 3) * rhs.RowCol(3, 0), 
		RowCol(0, 0) * rhs.RowCol(0, 1) + RowCol(0, 1) * rhs.RowCol(1, 1) + RowCol(0, 2) * rhs.RowCol(2, 1) + RowCol(0, 3) * rhs.RowCol(3, 1), 
		RowCol(0, 0) * rhs.RowCol(0, 2) + RowCol(0, 1) * rhs.RowCol(1, 2) + RowCol(0, 2) * rhs.RowCol(2, 2) + RowCol(0, 3) * rhs.RowCol(3, 2), 
		RowCol(0, 0) * rhs.RowCol(0, 3) + RowCol(0, 1) * rhs.RowCol(1, 3) + RowCol(0, 2) * rhs.RowCol(2, 3) + RowCol(0, 3) * rhs.RowCol(3, 3), 

		RowCol(1, 0) * rhs.RowCol(0, 0) + RowCol(1, 1) * rhs.RowCol(1, 0) + RowCol(1, 2) * rhs.RowCol(2, 0) + RowCol(1, 3) * rhs.RowCol(3, 0), 
		RowCol(1, 0) * rhs.RowCol(0, 1) + RowCol(1, 1) * rhs.RowCol(1, 1) + RowCol(1, 2) * rhs.RowCol(2, 1) + RowCol(1, 3) * rhs.RowCol(3, 1), 
		RowCol(1, 0) * rhs.RowCol(0, 2) + RowCol(1, 1) * rhs.RowCol(1, 2) + RowCol(1, 2) * rhs.RowCol(2, 2) + RowCol(1, 3) * rhs.RowCol(3, 2), 
		RowCol(1, 0) * rhs.RowCol(0, 3) + RowCol(1, 1) * rhs.RowCol(1, 3) + RowCol(1, 2) * rhs.RowCol(2, 3) + RowCol(1, 3) * rhs.RowCol(3, 3), 

		RowCol(2, 0) * rhs.RowCol(0, 0) + RowCol(2, 1) * rhs.RowCol(1, 0) + RowCol(2, 2) * rhs.RowCol(2, 0) + RowCol(2, 3) * rhs.RowCol(3, 0), 
		RowCol(2, 0) * rhs.RowCol(0, 1) + RowCol(2, 1) * rhs.RowCol(1, 1) + RowCol(2, 2) * rhs.RowCol(2, 1) + RowCol(2, 3) * rhs.RowCol(3, 1), 
		RowCol(2, 0) * rhs.RowCol(0, 2) + RowCol(2, 1) * rhs.RowCol(1, 2) + RowCol(2, 2) * rhs.RowCol(2, 2) + RowCol(2, 3) * rhs.RowCol(3, 2), 
		RowCol(2, 0) * rhs.RowCol(0, 3) + RowCol(2, 1) * rhs.RowCol(1, 3) + RowCol(2, 2) * rhs.RowCol(2, 3) + RowCol(2, 3) * rhs.RowCol(3, 3), 

		RowCol(3, 0) * rhs.RowCol(0, 0) + RowCol(3, 1) * rhs.RowCol(1, 0) + RowCol(3, 2) * rhs.RowCol(2, 0) + RowCol(3, 3) * rhs.RowCol(3, 0), 
		RowCol(3, 0) * rhs.RowCol(0, 1) + RowCol(3, 1) * rhs.RowCol(1, 1) + RowCol(3, 2) * rhs.RowCol(2, 1) + RowCol(3, 3) * rhs.RowCol(3, 1), 
		RowCol(3, 0) * rhs.RowCol(0, 2) + RowCol(3, 1) * rhs.RowCol(1, 2) + RowCol(3, 2) * rhs.RowCol(2, 2) + RowCol(3, 3) * rhs.RowCol(3, 2), 
		RowCol(3, 0) * rhs.RowCol(0, 3) + RowCol(3, 1) * rhs.RowCol(1, 3) + RowCol(3, 2) * rhs.RowCol(2, 3) + RowCol(3, 3) * rhs.RowCol(3, 3));
}

// ---------------------------------------------------------------------------

const Mtx44& Mtx44::MultThis(const Mtx44& rhs)
{
	return (*this) = this->Mult(rhs);
}

// ---------------------------------------------------------------------------

Vec4 Mtx44::MultVec(const Vec4& v) const
{
	return Vec4(
		RowCol(0, 0) * v.x + RowCol(0, 1) * v.y + RowCol(0, 2) * v.z + RowCol(0, 3) * v.w, 
		RowCol(1, 0) * v.x + RowCol(1, 1) * v.y + RowCol(1, 2) * v.z + RowCol(1, 3) * v.w, 
		RowCol(2, 0) * v.x + RowCol(2, 1) * v.y + RowCol(2, 2) * v.z + RowCol(2, 3) * v.w);
}

// ---------------------------------------------------------------------------

Mtx44 Mtx44::MultQuat(const Vec4& v) const
{
	Mtx44 quat(1.0f - 2.0f * v.y * v.y - 2.0f * v.z * v.z,
			   2.0f * v.x * v.y - 2.0f * v.w * v.z,
			   2.0f * v.x * v.z + 2.0f * v.w * v.y,
			   0.0f,

			   2.0f * v.x * v.y + 2.0f * v.w * v.z,
			   1.0f - 2.0f * v.x * v.x - 2.0f * v.z * v.z,
			   2.0f * v.y * v.z - 2.0f * v.w * v.x,
			   0.0f,

			   2.0f * v.x * v.z - 2.0f * v.w * v.y,
			   2.0f * v.y * v.z + 2.0f * v.w * v.x,
			   1.0f - 2.0f * v.x * v.x - 2.0f * v.y * v.y,
			   0.0f,

			   0.0f,
			   0.0f,
			   0.0f,
			   1.0f);

	return this->Mult(quat);
}

// ---------------------------------------------------------------------------

const Mtx44& Mtx44::MultQuatThis(const Vec4& v)
{
	return (*this) = this->MultQuat(v);
}

// ---------------------------------------------------------------------------

Mtx44 Mtx44::Transpose() const
{
	Mtx44 res;

	res.RowCol(0, 0) = RowCol(0, 0); res.RowCol(0, 1) = RowCol(1, 0); res.RowCol(0, 2) = RowCol(2, 0); res.RowCol(0, 3) = RowCol(3, 0);
	res.RowCol(1, 0) = RowCol(0, 1); res.RowCol(1, 1) = RowCol(1, 1); res.RowCol(1, 2) = RowCol(2, 1); res.RowCol(1, 3) = RowCol(3, 1);
	res.RowCol(2, 0) = RowCol(0, 2); res.RowCol(2, 1) = RowCol(1, 2); res.RowCol(2, 2) = RowCol(2, 2); res.RowCol(2, 3) = RowCol(3, 2);
	res.RowCol(3, 0) = RowCol(0, 3); res.RowCol(3, 1) = RowCol(1, 3); res.RowCol(3, 2) = RowCol(2, 3); res.RowCol(3, 3) = RowCol(3, 3);

	return res;
}

// ---------------------------------------------------------------------------

const Mtx44& Mtx44::TransposeThis()
{
	float f;

	// swap the 1st row
	f   = RowCol(0, 1); RowCol(0, 1) = RowCol(1, 0); RowCol(1, 0) = f;
	f   = RowCol(0, 2); RowCol(0, 2) = RowCol(2, 0); RowCol(2, 0) = f;
	f   = RowCol(0, 3); RowCol(0, 3) = RowCol(3, 0); RowCol(3, 0) = f;

	// swap the 2nd row
	f   = RowCol(1, 2); RowCol(1, 2) = RowCol(2, 1); RowCol(2, 1) = f;
	f   = RowCol(1, 3); RowCol(1, 3) = RowCol(3, 1); RowCol(3, 1) = f;

	// swap the 3rd row
	f   = RowCol(2, 3); RowCol(2, 3) = RowCol(3, 2); RowCol(3, 2) = f;
	
	return (*this);
}

// ---------------------------------------------------------------------------

Mtx44 Mtx44::Inverse() const
{
	Mtx44 res(*this);

	for (int i = 0; i < 16; ++i)
	{
		if (res.m[i] != 0)
		{
			res.m[i] = 1.0f / res.m[i];
		}
	}

	return res;
}
// ---------------------------------------------------------------------------

// the following functions will be applied to 'this' matrix
const Mtx44& Mtx44::ZeroThis()
{
	RowCol(0, 0) = RowCol(0, 1) = RowCol(0, 2) = RowCol(0, 3) = 
	RowCol(1, 0) = RowCol(1, 1) = RowCol(1, 2) = RowCol(1, 3) = 
	RowCol(2, 0) = RowCol(2, 1) = RowCol(2, 2) = RowCol(2, 3) = 
	RowCol(3, 0) = RowCol(3, 1) = RowCol(3, 2) = RowCol(3, 3) = 0.0f;

	return (*this);
}

// ---------------------------------------------------------------------------

const Mtx44& Mtx44::IdentityThis()
{
	RowCol(0, 1) = RowCol(0, 2) = RowCol(0, 3) = 
	RowCol(1, 0) = RowCol(1, 2) = RowCol(1, 3) = 
	RowCol(2, 0) = RowCol(2, 1) = RowCol(2, 3) = 
	RowCol(3, 0) = RowCol(3, 1) = RowCol(3, 2) = 0.0f;

	RowCol(0, 0) = RowCol(1, 1) = RowCol(2, 2) = RowCol(3, 3) = 1.0f;

	return (*this);
}

// ---------------------------------------------------------------------------

const Mtx44& Mtx44::ScaleThis(float x, float y, float z)
{
	return (*this) = (*this) * Mtx44::Scale(x, y, z);
}

// ---------------------------------------------------------------------------

const Mtx44& Mtx44::RotateThis(float x, float y, float z, float angle)
{
	return (*this) = (*this) * Mtx44::Rotate(x, y, z, angle);
}

// ---------------------------------------------------------------------------

const Mtx44& Mtx44::TranslateThis(float x, float y, float z)
{
	return (*this) = (*this) * Mtx44::Translate(x, y, z);
}

// ---------------------------------------------------------------------------
// the following functions construct a matrix

Mtx44 Mtx44::Zero()
{
	static Mtx44 res(
		0.0f, 0.0f, 0.0f, 0.0f, 
		0.0f, 0.0f, 0.0f, 0.0f, 
		0.0f, 0.0f, 0.0f, 0.0f, 
		0.0f, 0.0f, 0.0f, 0.0f);

	return res;
}

// ---------------------------------------------------------------------------

Mtx44 Mtx44::Identity()
{
	static Mtx44 res(
		1.0f, 0.0f, 0.0f, 0.0f, 
		0.0f, 1.0f, 0.0f, 0.0f, 
		0.0f, 0.0f, 1.0f, 0.0f, 
		0.0f, 0.0f, 0.0f, 1.0f);
	
	return res;
}

// ---------------------------------------------------------------------------

Mtx44 Mtx44::Scale(float x, float y, float z)
{
	return Mtx44(
		x,    0.0f, 0.0f, 0.0f, 
		0.0f, y,    0.0f, 0.0f, 
		0.0f, 0.0f, z,    0.0f, 
		0.0f, 0.0f, 0.0f, 1.0f);
}

// ---------------------------------------------------------------------------

Mtx44 Mtx44::Rotate(float x, float y, float z, float angle)
{
	float c   = CosLookup(angle);
	float omc = 1.0f - c;
	float s   = SinLookup(angle);

	float xx = x * x;
	float xy = x * y;
	float xz = x * z;
	float yy = y * y;
	float yz = y * z;
	float zz = z * z;

	Mtx44 A(
		c,    0.0f, 0.0f, 0.0f, 
		0.0f, c,    0.0f, 0.0f, 
		0.0f, 0.0f, c,    0.0f, 
		0.0f, 0.0f, 0.0f, 1.0f);
	Mtx44 B(
		xx,   xy,   xz,   0.0f, 
		xy,   yy,   yz,   0.0f, 
		xz,   yz,   zz,   0.0f, 
		0.0f, 0.0f, 0.0f, 0.0f);
	Mtx44 C(
		0.0f,   -z,    y, 0.0f, 
		   z, 0.0f,   -x, 0.0f, 
		  -y,    x, 0.0f, 0.0f, 
		0.0f, 0.0f, 0.0f, 0.0f);

	return A + omc * B + s * C;
}

// ---------------------------------------------------------------------------

Mtx44 Mtx44::Translate(float x, float y, float z)
{
	return Mtx44(
		1.0f, 0.0f, 0.0f, x, 
		0.0f, 1.0,  0.0f, y, 
		0.0f, 0.0f, 1.0,  z, 
		0.0f, 0.0f, 0.0f, 1.0f);
}

// ---------------------------------------------------------------------------
