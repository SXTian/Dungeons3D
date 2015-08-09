/*****************************************************************************************
Project      : 3D Game Engine
Author       : Sam Tian
Contributors :
******************************************************************************************/
#include "LightsView.h"
#include "MatrixStack.h"
#include "EventMessages.h"
#include "OpenGL.h"
#include "WindowSize.h"
#include <memory>

namespace Dungeons3D
{
	using namespace std;
	LightsView::LightsView(shared_ptr<ShaderManager> pManager) : IShaderManager(pManager), Camera(1.0f, 100.0f)
	{
    m_mousePosition.x = 0;
    m_mousePosition.y = 0;

		Register(MSG_MouseMove, this, [&](IEventMessage * pMsg)
		{
      int x = ((MessageMouseMove*)pMsg)->x;
      int y = ((MessageMouseMove*)pMsg)->y;
      RotateCamY(Clamp(-(float)(x - m_mousePosition.x), -5.0f, 5.0f));
      RotateCamX(Clamp((float)(y - m_mousePosition.y), -5.0f, 5.0f));
      m_mousePosition.x = x;
      m_mousePosition.y = y;
		});

		Register(MSG_MouseWheel, this, [&](IEventMessage * pMsg)
		{
			ZoomCam(-((MessageMouseWheel*)pMsg)->wheel / 10.0f);
		});

		
		Register(MSG_KeyPress, this, [&](IEventMessage * pMsg)
		{
			switch (((MessageKeyboard*)pMsg)->key)
			{
			case 'W': ZoomCam(10.0f); break;
			case 'S': ZoomCam(-10.0f); break;
			}
		});
	}

	LightsView::~LightsView()
	{
	}

	void LightsView::Initialize()
	{
		m_meshPlane.Load("Resources/Meshes/UnitPlane.mesh");
		m_meshCylinder.Load("Resources/Meshes/UnitCylinder.mesh");
    SetShaderUniform(SHA_BasicLighting, "cameraToClipMatrix", ViewMatrix().m, 16);
	}

	void LightsView::Display()
	{
	}

	void LightsView::Display(float delta)
	{
    SetShaderUniform(SHA_BasicLighting, "lightDirection", 1.0f, 1.0f, 0.0f);
    SetShaderUniform(SHA_BasicLighting, "lightIntensity", 1.0f, 1.0f, 1.0f, 1.0f);

		MatrixStack mStack;
    Mtx44 mcMatrix;

    SetShaderUniform(SHA_BasicLighting, "worldToCameraMatrix", CamMatrix().m, 16);

		//mStack.Push();
    //mStack.matrix.ScaleThis(100.0f, 1.0f, 100.0f);

    //mcMatrix = CamMatrix().MultThis(mStack.matrix);

    //SetShaderUniform(SHA_BasicLighting, "modelToCameraMatrix", mcMatrix.m, 16);
    //SetShaderUniform(SHA_BasicLighting, "normalModelToCameraMatrix", mcMatrix.Slice().m, 9);

		//m_meshPlane.Render();

		//mStack.Pop();

    mStack.Push();
		mStack.matrix.TranslateThis(0.0f, 10.0f, 0.0f);
		mStack.matrix.ScaleThis(15.0f, 15.0f, 15.0f);
		
    mcMatrix = CamMatrix().MultThis(mStack.matrix);

    SetShaderUniform(SHA_BasicLighting, "modelToCameraMatrix", mcMatrix.m, 16);
    SetShaderUniform(SHA_BasicLighting, "normalModelToCameraMatrix", mcMatrix.Slice().m, 9);

		m_meshCylinder.Render();

    checkMousePos();
	}

  void LightsView::checkMousePos()
  {
    if (m_mousePosition.x <= 0 || m_mousePosition.x >= WINDOW_MAX_X - 1 || m_mousePosition.y <= 0 || m_mousePosition.y >= WINDOW_MAX_Y - 1)
    {
      int centerX = WINDOW_MAX_X / 2;
      int centerY = WINDOW_MAX_Y / 2;
      m_mousePosition.x = centerX;
      m_mousePosition.y = centerY;
      SetCursorPos(centerX, centerY);
    }
  }
}