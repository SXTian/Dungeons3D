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
	Camera::Camera() : m_pos(67.5f, -46.0f, 100.0f), m_target(0.0f, 0.4f, 0.0f), m_up(0.0f, 1.0f, 0.0f), m_update(true)
	{
		//	For maths
		GenerateLookupTable();
	}

	Mtx44 Camera::CamMatrix()
	{
		if (m_update)
			calculate();

		return m_wcMatrix;
	}

	void Camera::MoveCamTarget(float x, float y, float z)
	{
		m_target = m_target + Vec4(x, y, z);
		m_update = true;
	}

	void Camera::MoveCamPosition(float x, float y, float z)
	{
		m_pos = m_pos + Vec4(x, y, z);
		m_update = true;
	}

	void Camera::calculate()
	{
		//	Get camera position in world coordinates
		float phi = m_pos.x;
		float theta = m_pos.y + 90.0f;
		Vec4 dirToCamera(SinLookup(theta) * CosLookup(phi), CosLookup(theta), SinLookup(theta) * SinLookup(phi));
		Vec4 cameraPos = (dirToCamera * m_pos.z) + m_target;

		//	Construct matrix
		Vec4 lookDir = (m_target - cameraPos).Normalize();
		Vec4 upDir = m_up.Normalize();

		Vec4 rightDir = lookDir.Cross(upDir);
		Vec4 perpUpDir = rightDir.Cross(lookDir);

		m_wcMatrix.IdentityThis();

		m_wcMatrix.RowCol(0, 0) = rightDir.x;
		m_wcMatrix.RowCol(0, 1) = rightDir.y;
		m_wcMatrix.RowCol(0, 2) = rightDir.z;

		m_wcMatrix.RowCol(1, 0) = perpUpDir.x;
		m_wcMatrix.RowCol(1, 1) = perpUpDir.y;
		m_wcMatrix.RowCol(1, 2) = perpUpDir.z;

		m_wcMatrix.RowCol(2, 0) = -lookDir.x;
		m_wcMatrix.RowCol(2, 1) = -lookDir.y;
		m_wcMatrix.RowCol(2, 2) = -lookDir.z;

		m_wcMatrix.TranslateThis(-cameraPos.x, -cameraPos.y, - cameraPos.z);

		m_update = false;
	}
}