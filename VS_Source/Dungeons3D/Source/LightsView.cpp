/*****************************************************************************************
Project      : 3D Game Engine
Author       : Sam Tian
Contributors :
******************************************************************************************/
#include "LightsView.h"
#include "MatrixStack.h"
#include "MessageKeyboard.h"
#include "MessageMouse.h"
#include "OpenGL.h"
#include <memory>

namespace Dungeons3D
{
	using namespace std;
	LightsView::LightsView(shared_ptr<ShaderManager> pManager) : IShaderManager(pManager), Camera(1.0f, 100.0f)
	{
		m_mouseDelta[0] = 0;
		m_mouseDelta[1] = 0;
		m_oldMouseDelta[0] = 0;
		m_oldMouseDelta[1] = 0;

		Register(MSG_MouseMove, this, [&](IEventMessage * pMsg)
		{
			POINT mousePos;
			GetCursorPos(&mousePos);
			m_mouseDelta[0] = mousePos.x - m_oldMouseDelta[0];
			m_mouseDelta[1] = mousePos.y - m_oldMouseDelta[1];
			m_oldMouseDelta[0] = mousePos.x;
			m_oldMouseDelta[1] = mousePos.y;
		});

		Register(MSG_MouseWheel, this, [&](IEventMessage * pMsg)
		{
			ZoomCam(-((MessageMouse*)pMsg)->wheel / 10.0f);
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

	void LightsView::LoadMeshes()
	{
		m_meshPlane.Load("Resources/Meshes/UnitPlane.mesh");
		m_meshCylinder.Load("Resources/Meshes/UnitCylinder.mesh");

		//	Transpose to column-wise, 0 is for the index in the uniform block
		SetShaderUniformBlock(ViewMatrix().Transpose().m, 0);
	}

	void LightsView::Display()
	{
	}

	void LightsView::Display(float delta)
	{
		RotateCamY(Clamp(-(float)m_mouseDelta[0], -5.0f, 5.0f));
		RotateCamX(Clamp((float)m_mouseDelta[1], -5.0f, 5.0f));

		m_mouseDelta[0] = 0;
		m_mouseDelta[1] = 0;

		//	Transpose to column-wise
		SetShaderUniformBlock(CamMatrix().Transpose().m, 1);

		MatrixStack mStack;

		mStack.Push();

		mStack.matrix.ScaleThis(100.0f, 1.0f, 100.0f);

		SetShaderUniform(SHA_ObjectColor, "modelToWorldMatrix", mStack.matrix.m);
		//SetShaderUniform(SHA_UniformColor, "baseColor", 1.0f, 1.0f, 1.0f, 1.0f);
		m_meshPlane.Render();

		mStack.Pop();

		mStack.matrix.TranslateThis(0.0f, 10.0f, 0.0f);
		mStack.matrix.ScaleThis(15.0f, 15.0f, 15.0f);
		

		SetShaderUniform(SHA_ObjectColor, "modelToWorldMatrix", mStack.matrix.m);
		//SetShaderUniform(SHA_UniformColor, "baseColor", 1.0f, 0.3f, 0.3f, 1.0f);
		m_meshCylinder.Render();

	}
}