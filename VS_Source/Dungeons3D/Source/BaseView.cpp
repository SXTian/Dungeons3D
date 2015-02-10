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
		//	For maths
		GenerateLookupTable();
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

		return m_ccMtx;
	}

	void BaseView::calculate()
	{
		float yMax = m_zNear * TanLookup(m_fovDeg);
		float yMin = -yMax;
		float xMax = yMax * ((float)1680 / (float)1050);
		float xMin = -xMax;

		m_ccMtx.IdentityThis();

		m_ccMtx.RowCol(0, 0) = (2.0f * m_zNear) / (xMax - xMin);
		m_ccMtx.RowCol(1, 1) = (2.0f * m_zNear) / (yMax - yMin);
		m_ccMtx.RowCol(0, 2) = (xMax + xMin)  / (xMax - xMin);
		m_ccMtx.RowCol(1, 2) = (yMax + yMin)  / (yMax - yMin);
		m_ccMtx.RowCol(2, 2) = (-m_zFar - m_zNear) / (m_zFar - m_zNear);
		m_ccMtx.RowCol(3, 2) = -1.0f;
		m_ccMtx.RowCol(2, 3) = (-2.0f * m_zNear * m_zFar) / (m_zFar - m_zNear);
		m_ccMtx.RowCol(3, 3) = 0.0f;

		m_update = false;
	}
}