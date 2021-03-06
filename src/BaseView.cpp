/*****************************************************************************************
Project      : 3D Game Engine
Author       : Sam Tian
Contributors :
******************************************************************************************/
#pragma once

#include "BaseView.h"
#include "Math.h"
#include "OpenGL.h"


namespace Dungeons3D
{
	BaseView::BaseView() : m_fovDeg(45.0f), m_zNear(1.0f), m_zFar(1000.0f), m_update(true)
	{
	}

	void BaseView::Display(float delta)
	{
		Display();
	}

	void BaseView::Resize(float fovDeg, float zNear, float zFar)
	{
		m_fovDeg = fovDeg;
		m_zNear = zNear;
		m_zFar = zFar;

		m_update = true;
	}

	Mtx44 BaseView::ViewMatrix()
	{
		if (m_update)
			calculate();

		return m_cvMtx;
	}

	void BaseView::calculate()
	{
		float yMax = m_zNear * TanD(m_fovDeg);
		float yMin = -yMax;
		float xMax = yMax * ((float)1680 / (float)1050);
		float xMin = -xMax;

    m_cvMtx.IdentityThis();

    m_cvMtx.RowCol(0, 0) = (2.0f * m_zNear) / (xMax - xMin);
    m_cvMtx.RowCol(1, 1) = (2.0f * m_zNear) / (yMax - yMin);
    m_cvMtx.RowCol(0, 2) = (xMax + xMin)  / (xMax - xMin);
    m_cvMtx.RowCol(1, 2) = (yMax + yMin)  / (yMax - yMin);
    m_cvMtx.RowCol(2, 2) = (-m_zFar - m_zNear) / (m_zFar - m_zNear);
    m_cvMtx.RowCol(3, 2) = -1.0f;
    m_cvMtx.RowCol(2, 3) = (-2.0f * m_zNear * m_zFar) / (m_zFar - m_zNear);
    m_cvMtx.RowCol(3, 3) = 0.0f;

		m_update = false;
	}
}