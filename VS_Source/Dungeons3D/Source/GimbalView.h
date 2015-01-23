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
	class GimbalView : public IView, public IShaderManager
	{
	public: 
		GimbalView(std::shared_ptr<ShaderManager> pManager);
		~GimbalView();

		void LoadMeshes();
		void Display();

	private:
		Mesh<Loader> m_smallGimbal;
		Mesh<Loader> m_mediumGimbal;
		Mesh<Loader> m_largeGimbal;
	};
}