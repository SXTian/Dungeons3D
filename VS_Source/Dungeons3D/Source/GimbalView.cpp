/*****************************************************************************************
Project      : 3D Game Engine
Author       : Sam Tian
Contributors :
******************************************************************************************/

#include "GimbalView.h"
#include "ShaderManager.h"
#include "MatrixStack.h"

namespace Dungeons3D
{
	using namespace std;

	GimbalView::GimbalView(shared_ptr<ShaderManager> pShaderManager) : IShaderManager(pShaderManager)
	{
	}

	GimbalView::~GimbalView()
	{
	}

	void GimbalView::LoadMeshes()
	{
		m_smallGimbal.Load("Resources/Meshes/SmallGimbal.mesh");
		m_mediumGimbal.Load("Resources/Meshes/MediumGimbal.mesh");
		m_largeGimbal.Load("Resources/Meshes/LargeGimbal.mesh");

		SetShaderUniform(SHA_UniformColorLocal, "cameraToClipMatrix", ViewMatrix().m);
	}

	void GimbalView::Display()
	{
		//	Transpose to column-wise
		SetShaderUniformBlock(CamMatrix().Transpose().m, 1);

		MatrixStack mStack;

		mStack.matrix.ScaleThis(10.0f, 10.0f, 10.0f);

		SetShaderUniform(SHA_UniformColor, "modelToWorldMatrix", mStack.matrix.m);
		SetShaderUniform(SHA_UniformColor, "baseColor", 0.302f, 0.416f, 0.0589f, 1.0f);
		m_smallGimbal.Render();
	}
}