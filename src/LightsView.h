/*****************************************************************************************
Project      : 3D Game Engine
Author       : Sam Tian
Contributors :
******************************************************************************************/
#pragma once

#include "CameraView.h"
#include "IShaderManager.h"
#include "IEventMessage.h"
#include "Mesh.h"
#include "Loader.h"
#include "Loader3DS.h"
#include "MousePosition.h"

namespace Dungeons3D
{
	class LightsView : public CameraView, private IShaderManager, private IEventMessageModule
	{
	public: 
		LightsView(std::shared_ptr<Camera> pCamera, std::shared_ptr<ShaderManager> pManager);
		~LightsView();

		void Initialize();

    void Display();
    void Display(float delta);
	private:

    MousePosition m_mousePosition;
    void checkMousePos();

    bool ambient;

		Mesh<Loader> m_meshPlane;
		Mesh<Loader> m_meshCylinder;
	};

}