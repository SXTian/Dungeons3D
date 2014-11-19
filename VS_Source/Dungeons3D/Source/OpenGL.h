/*****************************************************************************************
Project      : 3D Game Engine
Author       : Sam Tian
Contributors :
******************************************************************************************/
#pragma once

#include "System.h"
#include "GLHeaders.h"
#include "Matrix.h"
#include "ShaderManager.h"

namespace Dungeons3D
{
	class OpenGL
	{
	public:
		OpenGL();
		~OpenGL();

		void Initialize();
		void Display();

	private:
		void initShaders();
		void initVertexBuffer();

		ShaderManager* _pShaderManager;

		GLuint _vbo;
		GLuint _vao;

		float _zNear;
		float _zFar;
		const float _frustumScale;
		Mtx44 _perspectiveMtx;
	};
}
