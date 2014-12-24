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

// -----------------------------------------------------------------------------
static float sin_table[3600], cos_table[3600]; // Look up tables

static inline void GenerateLookupTable(void)
{
   for(int i=0; i < 3600; i++)
   {
      sin_table[i]=(float)sin(i * PI / 1800);
      cos_table[i]=(float)cos(i * PI / 1800); 
   }    
}
// ------------------------------------------------------------------------------
template <typename T>
inline T SinLookup(T degree)
{
	int index = (int)(degree * 10.0);
	return sin_table[index];
}

// -------------------------------------------------------------------------------

template <typename T>
inline T CosLookup(T degree)
{
	int index = (int)(degree * 10.0);
	return cos_table[index];
}

template <typename T>
inline T TanLookup(T degree)
{
	int index = (int)(degree * 10.0);
	return sin_table[index] / cos_table[index];
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
	return x * (PI / 180.0);
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

// ----------------------------------------------------------------------------------------

template <typename T>
inline bool InRange(const T x, const T xMin, const T xMax)
{
	return ((xMin <= x) && (x <= xMax));
}