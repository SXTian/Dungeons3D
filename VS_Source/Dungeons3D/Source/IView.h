/*****************************************************************************************
Project      : 3D Game Engine
Author       : Sam Tian
Contributors :
******************************************************************************************/
#pragma once

#include "Camera.h"
#include "IShaderManager.h"

namespace Dungeons3D
{
	class OpenGL;

	class IView : public Camera
	{
	public:
		IView();
		virtual ~IView(){}

		virtual void LoadMeshes() = 0;
		virtual void Display() = 0;

		Mtx44 ViewMatrix();

		void Resize(float fovDeg, float zNear, float zFar);
	private:
		void calculate();

		float m_fovDeg;
		float m_zNear;
		float m_zFar;

		//	Camera to clipspace transformation
		Mtx44 m_ccMtx;

		//	true = must call calculate()
		bool m_update;
	};
}