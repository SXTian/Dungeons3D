/*****************************************************************************************
  Project      : 3D Game Engine
  Author       : Sam Tian
  Contributors :
******************************************************************************************/
#pragma once
#include <stdlib.h>
#include <time.h>
#include <cmath>

// -----------------------------------------------------------------------------

const float PI = 3.1415926535897932f;
const float TWO_PI = PI * 2.0f;
const float HALF_PI = PI * 0.5f;

// ------------------------------------------------------------------------------
template <typename T>
inline T SinD(T degree)
{
	return sin(DegToRad(degree));
}

// -------------------------------------------------------------------------------

template <typename T>
inline T CosD(T degree)
{
  return cos(DegToRad(degree));
}

template <typename T>
inline T TanD(T degree)
{
  return tan(DegToRad(degree));
}

// --------------------------------------------------------------------------------
template <typename T>
inline T RandomRange(T x, T y)
{
	T result = (T)rand() / (T)RAND_MAX;
	return x * (1.0 - result) + y * result;
}
// ---------------------------------------------------------------------------------

template<typename T>
inline bool IsPowOf2(T x)
{
	return ((x > 0) && ((x & (x - 1)) == 0));
}

// ---------------------------------------------------------------------------------

template <typename T>
inline T DegToRad(const T x)
{
	return x * (PI / (T)180.0);
}

// -----------------------------------------------------------------------------------

template <typename T>
inline T RadToDeg(const T x)
{
	return x * (180.0 / PI);
}

// ------------------------------------------------------------------------------------

template <typename T>
inline T Min(const T x, const T y)
{
	return (x < y) ? x : y;
}

// -------------------------------------------------------------------------------------

template <typename T>
inline T Max(const T x, const T y)
{
	return (x < y) ? y : x;
}

// --------------------------------------------------------------------------------------

template <typename T>
inline T Clamp(const T x, const T xMin, const T xMax)
{
	return Max(xMin, Min(x, xMax));
}

// ---------------------------------------------------------------------------------------

template <typename T>
inline T Wrap(const T x, const T xMin, const T xMax)
{
	return (x < xMin) ? (x + (xMax - xMin)) : ((x > xMax) ? (x - (xMax - xMin)) : x);
}

// ---------------------------------------------------------------------------------------

template <typename T0, typename T1>
inline T0 Lerp(const T0 xMin, const T0 xMax, const T1 t)
{
	return xMin + (xMax - xMin) * t;
}

// ---------------------------------------------------------------------------------------

template <typename T0, typename T1>
inline T0 Mix(const T0 x, const T0 y, const T1 t)
{
	return x * (1.0f - t) + y * t;
}

// ----------------------------------------------------------------------------------------

template <typename T>
inline bool InRange(const T x, const T xMin, const T xMax)
{
	return ((xMin <= x) && (x <= xMax));
}

// ----------------------------------------------------------------------------------------
// And just for a lil somethin' extra...
// ----------------------------------------------------------------------------------------
inline float QSqrt(float number)
{
    long i;
    float x, y;
    const float f = 1.5F;

    x = number * 0.5F;
    y  = number;
    i  = * ( long * ) &y;
    i  = 0x5f3759df - ( i >> 1 );
    y  = * ( float * ) &i;
    y  = y * ( f - ( x * y * y ) );
    y  = y * ( f - ( x * y * y ) );
    return number * y;
}
