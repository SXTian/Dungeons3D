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
	class PantheonView : public CameraView, private IShaderManager, private IEventMessageModule
	{
	public: 
    PantheonView(std::shared_ptr<Camera> pCamera, std::shared_ptr<ShaderManager> pManager);
		~PantheonView();

		void Initialize();

		void Display();
		void Display(float delta);

  private:
		void drawGround();
		void drawForest();
		void drawParthenon();
		void drawColumn(Mtx44 matrix, float height = 5.0f);

    void checkMousePos();

		Mesh<Loader> m_meshCube;
		Mesh<Loader> m_meshCubeColor;
		Mesh<Loader> m_meshPlane;
		Mesh<Loader> m_meshCylinder;

    Mesh<Loader> m_meshTreetop;
    Mesh<Loader> m_meshTreetrunk;

		Mesh<Loader3DS> m_wizard;

    MousePosition m_mousePosition;

    float lightAngleX;
    float lightAngleZ;
	};

	struct TreeData
	{
		float xPos;
		float zPos;
		float heightTrunk;
		float heightCone;
	};
}