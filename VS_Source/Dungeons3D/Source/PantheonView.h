/*****************************************************************************************
Project      : 3D Game Engine
Author       : Sam Tian
Contributors :
******************************************************************************************/
#pragma once

#include "IView.h"
#include "IShaderManager.h"
#include "Mesh.h"
#include "Loader.h"

namespace Dungeons3D
{
	class ShaderManager;
	class PantheonView : public IView, public IShaderManager
	{
	public: 
		PantheonView(std::shared_ptr<ShaderManager> pManager);
		~PantheonView();

		void LoadMeshes();
	private:
		void Display();
		void drawGround();
		void drawForest();
		void drawParthenon();
		void drawColumn(Mtx44 matrix, float height = 5.0f);

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