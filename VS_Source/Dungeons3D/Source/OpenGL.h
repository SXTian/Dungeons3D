/*****************************************************************************************
Project      : 3D Game Engine
Author       : Sam Tian
Contributors :
******************************************************************************************/
#pragma once

#include "System.h"
#include "GLHeaders.h"
#include "ShaderManager.h"
#include "Camera.h"
#include "Mesh.h"
#include "Loader.h"

namespace Dungeons3D
{
	class OpenGL 
	{
	friend class GraphicsSystem;

	public:
		OpenGL();
		~OpenGL();
		void Display();

	private:
		//	Methods
		void initGL();
		void configGL();
		void initShaders();

		Mtx44 calcProjection(float fovDeg, float zNear, float zFar);

		void drawGround();
		void drawForest();
		void drawParthenon();
		void drawColumn(Mtx44 matrix, float height = 5.0f);

		//	Members
		ShaderManager m_shaderManager;
		Camera m_camera;

		//	Model to world
		Mtx44 m_mwMtx;

		//	Camera to clip
		Mtx44 m_ccMtx;

		Mesh<Loader> m_meshCube;
		Mesh<Loader> m_meshCubeColor;
		Mesh<Loader> m_meshPlane;
		Mesh<Loader> m_meshCone;
		Mesh<Loader> m_meshCylinder;
		Mesh<Loader> m_meshSmallGimbal;
		Mesh<Loader> m_meshMediumGimbal;
		Mesh<Loader> m_meshLargeGimbal;

	};
}
