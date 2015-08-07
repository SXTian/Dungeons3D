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
	class PantheonView : public BaseView, public Camera, public IShaderManager, public IEventMessageModule
	{
	public: 
		PantheonView(std::shared_ptr<ShaderManager> pManager);
		~PantheonView();

		void Initialize();
	private:
		void Display();
		void Display(float delta);

		void drawGround();
		void drawForest();
		void drawParthenon();
		void drawColumn(Mtx44 matrix, float height = 5.0f);

		void drawWizard();

		Mesh<Loader> m_meshCube;
		Mesh<Loader> m_meshCubeColor;
		Mesh<Loader> m_meshPlane;
		Mesh<Loader> m_meshCone;
		Mesh<Loader> m_meshCylinder;

		Mesh<Loader3DS> m_wizard;

		int m_mouseDelta[2];
		int m_oldMouseDelta[2];
	};

	struct TreeData
	{
		float xPos;
		float zPos;
		float heightTrunk;
		float heightCone;
	};
}