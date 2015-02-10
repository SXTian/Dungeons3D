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
	Camera::Camera(float distMin, float distMax) : m_position(0.0f, 0.0f, 50.0f), m_target(0.0f), m_up(0.0f, 1.0f, 0.0f, 0.0f), 
		m_rotateX(0.5f), m_rotateY(0.0f),
		m_min(distMin), m_max(distMax), m_update(true)
	{
		//	Need to look into this...
		GenerateLookupTable();

		m_distance = (m_min + m_max) * 0.5f;
	}

	Mtx44 Camera::CamMatrix()
	{
		if (m_update)
		{
			updatePosition();
			constructMatrix();
		}

		return m_wcMatrix;
	}

	void Camera::ZoomCam(float dist)
	{
		m_distance = Clamp(m_distance + dist, m_min, m_max);
		m_update = true;
	}

	void Camera::RotateCamX(float deg)
	{
		m_rotateX = Clamp(m_rotateX + deg, -90.0f, 90.0f);
		m_update = true;
	}

	void Camera::RotateCamY(float deg)
	{
		m_rotateY = Wrap(m_rotateY + deg, -180.0f, 180.0f);
		m_update = true;
	}

	void Camera::updatePosition()
	{
		float sinX = SinLookup(m_rotateX);
		float sinY = SinLookup(m_rotateY);
		float cosX = CosLookup(m_rotateX);
		float cosY = CosLookup(m_rotateY);

		m_up.x = sinX * -sinY;
		m_up.y = cosX;
		m_up.z = sinX * -cosY;

		Vec4 direction(-cosX * sinY, -sinX, -cosX * cosY, 0.0f);

		m_position = m_target - direction * m_distance;
	}

	void Camera::constructMatrix()
	{
		Vec4 lookDir = (m_target - m_position).Normalize();
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

		m_wcMatrix.TranslateThis(-m_position.x, -m_position.y, - m_position.z);

		m_update = false;
	}
}