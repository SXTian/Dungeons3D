/*****************************************************************************************
Project      : 3D Game Engine
Author       : Sam Tian
Contributors :
******************************************************************************************/
#pragma once

#include "GLHeaders.h"
#include "ShaderManager.h"
#include "Matrix.h"

namespace Dungeons3D
{
	class IView;

	class OpenGL : public IShaderManager
	{
	public:
		OpenGL();
		~OpenGL();
		void Display(IView * view);

	private:
		//	Methods
		void initGL();
		void configGL();
		void initShaders();

		Mtx44 calcProjection(float fovDeg, float zNear, float zFar);

		//	Camera to clip
		Mtx44 m_ccMtx;
	};
}
