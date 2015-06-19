/*****************************************************************************************
Project      : 3D Game Engine
Author       : Sam Tian
Contributors :
******************************************************************************************/
#pragma once

#include "BaseView.h"
#include "Camera.h"
#include "IShaderManager.h"
#include "IEventMessage.h"
#include "Mesh.h"
#include "Loader.h"
#include "Loader3DS.h"

namespace Dungeons3D
{
	class ShaderManager;

	class LightsView : public BaseView, public Camera, public IShaderManager, public IEventMessageModule
	{
	public: 
		LightsView(std::shared_ptr<ShaderManager> pManager);
		~LightsView();

		void LoadMeshes();
	private:

		int m_mouseDelta[2];
		int m_oldMouseDelta[2];

		void Display();
		void Display(float delta);

		Mesh<Loader> m_meshPlane;
		Mesh<Loader> m_meshCylinder;
	};

}