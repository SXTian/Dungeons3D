/*****************************************************************************************
Project      : 3D Game Engine
Author       : Sam Tian
Contributors :
******************************************************************************************/
#pragma once

#include "View.h"
#include "Mesh.h"
#include "Loader.h"

namespace Dungeons3D
{
	class PantheonView : public IView
	{
	public: 
		PantheonView();
		~PantheonView();

		void LoadMeshes();
		void Display(OpenGL * opengl);

	private:

		void drawGround(OpenGL * opengl);
		void drawForest(OpenGL * opengl);
		void drawParthenon(OpenGL * opengl);
		void drawColumn(OpenGL * opengl, Mtx44 matrix, float height = 5.0f);

		Mesh<Loader> m_meshCube;
		Mesh<Loader> m_meshCubeColor;
		Mesh<Loader> m_meshPlane;
		Mesh<Loader> m_meshCone;
		Mesh<Loader> m_meshCylinder;
	};

	struct TreeData
	{
		float xPos;
		float zPos;
		float heightTrunk;
		float heightCone;
	};
}