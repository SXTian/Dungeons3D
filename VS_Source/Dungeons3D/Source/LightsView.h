/*****************************************************************************************
Project      : 3D Game Engine
Author       : Sam Tian
Contributors :
******************************************************************************************/
#pragma once

#include "BaseView.h"
#include "Camera.h"
#include "IShaderManager.h"
#include "Mesh.h"
#include "Loader.h"
#include "Loader3DS.h"

namespace Dungeons3D
{
	class ShaderManager;

	class LightsView : public BaseView, public Camera, public IShaderManager
	{
	public: 
		LightsView(std::shared_ptr<ShaderManager> pManager);
		~LightsView();

		void LoadMeshes();
	private:
		void Display();

		Mesh<Loader> m_meshPlane;
	};

}