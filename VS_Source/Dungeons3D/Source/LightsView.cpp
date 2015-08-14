/*****************************************************************************************
Project      : 3D Game Engine
Author       : Sam Tian
Contributors :
******************************************************************************************/
#include "LightsView.h"
#include "Camera.h"
#include "MatrixStack.h"
#include "EventMessages.h"
#include "WindowSize.h"
#include "OpenGL.h"

namespace Dungeons3D
{
	using namespace std;
	LightsView::LightsView(shared_ptr<Camera> pCamera, shared_ptr<ShaderManager> pManager) : CameraView(pCamera), IShaderManager(pManager)
	{
    m_mousePosition.x = 0;
    m_mousePosition.y = 0;
    ambient = true;

		Register(MSG_MouseMove, this, [&](IEventMessage * pMsg)
		{
      int x = ((MessageMouseMove*)pMsg)->x;
      int y = ((MessageMouseMove*)pMsg)->y;
      GetCamera().RotateCamY(Clamp(-(float)(x - m_mousePosition.x), -5.0f, 5.0f));
      GetCamera().RotateCamX(Clamp((float)(y - m_mousePosition.y), -5.0f, 5.0f));
      m_mousePosition.x = x;
      m_mousePosition.y = y;
		});

		Register(MSG_MouseWheel, this, [&](IEventMessage * pMsg)
		{
			GetCamera().ZoomCam(-((MessageMouseWheel*)pMsg)->wheel / 10.0f);
		});

		
		Register(MSG_KeyPress, this, [&](IEventMessage * pMsg)
		{
			switch (((MessageKeyboard*)pMsg)->key)
			{
      case VK_SPACE:
        ambient = !ambient;
        break;
			}
		});
	}

	LightsView::~LightsView()
	{
	}

	void LightsView::Initialize()
	{
		m_meshPlane.Load("Resources/Meshes/UnitPlane.mesh");
		m_meshCylinder.Load("Resources/Meshes/RedCylinder.mesh");
    SetShaderUniform(SHA_BasicLighting, "cameraToClipMatrix", ViewMatrix().m, 16);
    SetShaderUniform(SHA_AmbientLighting, "cameraToClipMatrix", ViewMatrix().m, 16);
	}

	void LightsView::Display()
	{
	}

	void LightsView::Display(float delta)
	{
    if (ambient)
    {
      SetShaderUniform(SHA_AmbientLighting, "lightDirection", 0.8666f, 0.5f, 0.0f);
      SetShaderUniform(SHA_AmbientLighting, "lightIntensity", 0.8f, 0.8f, 0.8f, 1.0f);
      SetShaderUniform(SHA_AmbientLighting, "ambientIntensity", 0.2f, 0.2f, 0.2f, 1.0f);

      MatrixStack mStack;
      Mtx44 mcMatrix;

      SetShaderUniform(SHA_AmbientLighting, "worldToCameraMatrix", WCMatrix().m, 16);

      mStack.Push();
      mStack.matrix.ScaleThis(100.0f, 1.0f, 100.0f);

      SetShaderUniform(SHA_AmbientLighting, "modelToCameraMatrix", MCMatrix(mStack.matrix).m, 16);
      SetShaderUniform(SHA_AmbientLighting, "normalModelToCameraMatrix", MCMatrix().Slice().m, 9);

      m_meshPlane.Render();

      mStack.Pop();

      mStack.Push();
      mStack.matrix.TranslateThis(0.0f, 10.0f, 0.0f);
      mStack.matrix.ScaleThis(15.0f, 15.0f, 15.0f);

      SetShaderUniform(SHA_AmbientLighting, "modelToCameraMatrix", MCMatrix(mStack.matrix).m, 16);
      SetShaderUniform(SHA_AmbientLighting, "normalModelToCameraMatrix", MCMatrix().Slice().m, 9);

      m_meshCylinder.Render();

      checkMousePos();
    }
    else
    {
      SetShaderUniform(SHA_BasicLighting, "lightDirection", 0.8666f, 0.5f, 0.0f);
      SetShaderUniform(SHA_BasicLighting, "lightIntensity", 1.0f, 1.0f, 1.0f, 1.0f);

      MatrixStack mStack;
      Mtx44 mcMatrix;

      SetShaderUniform(SHA_BasicLighting, "worldToCameraMatrix", WCMatrix().m, 16);

      mStack.Push();
      mStack.matrix.ScaleThis(100.0f, 1.0f, 100.0f);

      SetShaderUniform(SHA_BasicLighting, "modelToCameraMatrix", MCMatrix(mStack.matrix).m, 16);
      SetShaderUniform(SHA_BasicLighting, "normalModelToCameraMatrix", MCMatrix().Slice().m, 9);

      m_meshPlane.Render();

      mStack.Pop();

      mStack.Push();
      mStack.matrix.TranslateThis(0.0f, 10.0f, 0.0f);
      mStack.matrix.ScaleThis(15.0f, 15.0f, 15.0f);

      SetShaderUniform(SHA_BasicLighting, "modelToCameraMatrix", MCMatrix(mStack.matrix).m, 16);
      SetShaderUniform(SHA_BasicLighting, "normalModelToCameraMatrix", MCMatrix().Slice().m, 9);

      m_meshCylinder.Render();

      checkMousePos();
    }

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