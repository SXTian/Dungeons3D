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
#include "Camera.h"
#include "Mesh.h"
#include "Loader.h"

namespace Dungeons3D
{
	class OpenGL 
	{
	public:
		OpenGL();
		~OpenGL();
		void Display();

	private:
		void initShaders();
		void initVertexBuffer();
		void initVertexArrays();

		Mtx44 CalculateProjection(float fovDeg, float zNear, float zFar);

		ShaderManager m_shaderManager;
		Camera m_camera;

		//	Model to world
		Mtx44 m_mwMtx;

		//	Camera to clip
		Mtx44 m_ccMtx;

		Mesh<Loader> test;

		GLuint m_vbo;
		GLuint m_ibo;
		GLuint m_vao;
	};
}
