/*****************************************************************************************
Project      : 3D Game Engine
Author       : Sam Tian
Contributors :
******************************************************************************************/
#include "LightsView.h"
#include <memory>

namespace Dungeons3D
{
	using namespace std;
	LightsView::LightsView(shared_ptr<ShaderManager> pManager) : IShaderManager(pManager), Camera(1.0f, 1000.0f)
	{
	}

	LightsView::~LightsView()
	{
	}

	void LightsView::LoadMeshes()
	{
		m_meshPlane.Load("Resources/Meshes/UnitPlane.mesh");

		//	Transpose to column-wise, 0 is for the index in the uniform block
		SetShaderUniformBlock(ViewMatrix().Transpose().m, 0);
	}

	void LightsView::Display()
	{
		//	Transpose to column-wise
		SetShaderUniformBlock(CamMatrix().Transpose().m, 1);


	}



}