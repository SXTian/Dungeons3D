/*****************************************************************************************
Project      : 3D Game Engine
Author       : Sam Tian
Contributors :
******************************************************************************************/
#include "GraphicsSystem.h"
#include "MessageKeyboard.h"
#include "OpenGL.h"
#include "PantheonView.h"
#include <iostream>

namespace Dungeons3D
{

	GraphicsSystem::GraphicsSystem() : m_opengl(new OpenGL()), m_pantheonView(new PantheonView())
	{
		m_pantheonView->LoadMeshes();
		//	PRAISE BE THE LAMBDA!!
		Register(MSG_KeyPress, this, [&](IEventMessage * pMsg)
		{
			switch (((MessageKeyboard*)pMsg)->key)
			{
			case 'W': m_pantheonView->MoveCamTarget(0.0f, 0.0f, -4.0f); break;
			case 'S': m_pantheonView->MoveCamTarget(0.0f, 0.0f, 4.0f); break;
			case 'D': m_pantheonView->MoveCamTarget(4.0f, 0.0f, 0.0f); break;
			case 'A': m_pantheonView->MoveCamTarget(-4.0f, 0.0f, 0.0f); break;
			case 'E': m_pantheonView->MoveCamTarget(0.0f, -4.0f, 0.0f); break;
			case 'Q': m_pantheonView->MoveCamTarget(0.0f, 4.0f, 0.0f); break;

			case 'I': m_pantheonView->MoveCamPosition(0.0f, -1.125f, 0.0f); break;
			case 'K': m_pantheonView->MoveCamPosition(0.0f, 1.125f, 0.0f); break;
			case 'J': m_pantheonView->MoveCamPosition(-1.125f, 0.0f, 0.0f); break;
			case 'L': m_pantheonView->MoveCamPosition(1.125f, 0.0f, 0.0f); break;
			case 'O': m_pantheonView->MoveCamPosition(0.0f, 0.0f, -0.5f); break;
			case 'U': m_pantheonView->MoveCamPosition(0.0f, 0.0f, 0.5f); break;
			}
		});
	}

	GraphicsSystem::~GraphicsSystem()
	{
		delete m_opengl;
		delete m_pantheonView;
	}

	void GraphicsSystem::Update(float delta)
	{
		m_opengl->Display(m_pantheonView);
	}
}
