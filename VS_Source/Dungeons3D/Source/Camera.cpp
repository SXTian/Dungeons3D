/*****************************************************************************************
Project      : 3D Game Engine
Author       : Sam Tian
Contributors :
******************************************************************************************/
#pragma once

#include "Camera.h"
#include "Math.h"

namespace Dungeons3D
{
	Camera::Camera() : _pos(67.5f, -46.0f, 150.0f), _target(0.0f, 0.4f, 0.0f), _up(0.0f, 1.0f, 0.0f), _update(true)
	{
	}

	Mtx44 Camera::Matrix()
	{
		if (_update)
			calculate();

		return _wcMatrix;
	}

	void Camera::calculate()
	{
		//	Get camera position in world coordinates
		float phi = _pos.x;
		float theta = _pos.y + 90.0f;
		Vec3 dirToCamera(SinLookup(theta) * CosLookup(phi), CosLookup(theta), SinLookup(theta) * SinLookup(phi));
		Vec3 cameraPos = (dirToCamera * _pos.z) + _target;

		//	Construct matrix
		Vec3 lookDir = (_target - cameraPos).Normalize();
		Vec3 upDir = _up.Normalize();

		Vec3 rightDir = lookDir.Cross(upDir);
		Vec3 perpUpDir = rightDir.Cross(lookDir);

		_wcMatrix.IdentityThis();

		_wcMatrix.RowCol(0, 0) = rightDir.x;
		_wcMatrix.RowCol(0, 1) = rightDir.y;
		_wcMatrix.RowCol(0, 2) = rightDir.z;

		_wcMatrix.RowCol(1, 0) = perpUpDir.x;
		_wcMatrix.RowCol(1, 1) = perpUpDir.y;
		_wcMatrix.RowCol(1, 2) = perpUpDir.z;

		_wcMatrix.RowCol(2, 0) = -lookDir.x;
		_wcMatrix.RowCol(2, 1) = -lookDir.y;
		_wcMatrix.RowCol(2, 2) = -lookDir.z;

		_wcMatrix.TranslateThis(-cameraPos.x, -cameraPos.y, - cameraPos.z);

		_update = false;
	}
}