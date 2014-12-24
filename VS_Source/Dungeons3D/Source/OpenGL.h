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

		ShaderManager _shaderManager;
		Camera _camera;

		//	Vertex Buffer Object
		GLuint _vbo;

		//	Index Buffer Object
		GLuint _ibo;

		//	Vertex Array Object
		GLuint _vao;

		//	Camera Position in Spherical
		Vec3 cameraPos;

		//	Camera Target
		Vec3 cameraTarget;

		//	Model to world
		Mtx44 _mwMtx;
		//	World to camera
		Mtx44 _wcMtx;
		//	Camera to clip
		Mtx44 _ccMtx;
	};
}
