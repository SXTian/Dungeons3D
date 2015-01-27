/*****************************************************************************************
Project      : 3D Game Engine
Author       : Sam Tian
Contributors :
******************************************************************************************/
#include "GraphicsSystem.h"
#include "MessageKeyboard.h"
#include "OpenGL.h"
#include "PantheonView.h"
#include "GimbalView.h"

#include <iostream>

namespace Dungeons3D
{
	using namespace std;
	GraphicsSystem::GraphicsSystem() : m_opengl(new OpenGL())
	{
		m_views["Pantheon"] = new PantheonView(m_opengl);
		m_views["Gimbal"] = new GimbalView(m_opengl);

		for (auto &i : m_views)
			i.second->LoadMeshes();

		//	PRAISE BE THE LAMBDA!!
		Register(MSG_KeyPress, this, [&](IEventMessage * pMsg)
		{
			switch (((MessageKeyboard*)pMsg)->key)
			{
			case 'W': for (auto &i : m_views) i.second->ChangeAngle(1.0f, 0.0f, 0.0f, 9.0f); break;
			case 'S': for (auto &i : m_views) i.second->ChangeAngle(-1.0f, 0.0f, 0.0f, 9.0f); break;
			case 'D': for (auto &i : m_views) i.second->ChangeAngle(0.0f, -1.0f, 0.0f, 9.0f); break;
			case 'A': for (auto &i : m_views) i.second->ChangeAngle(0.0f, 1.0f, 0.0f, 9.0f); break;
			case 'E': for (auto &i : m_views) i.second->ChangeAngle(0.0f, 0.0f, -1.0f, 9.0f); break;
			case 'Q': for (auto &i : m_views) i.second->ChangeAngle(0.0f, 0.0f, 1.0f, 9.0f); break;

			case 'I': for (auto &i : m_views) i.second->MoveCamPosition(0.0f, -1.125f, 0.0f); break;
			case 'K': for (auto &i : m_views) i.second->MoveCamPosition(0.0f, 1.125f, 0.0f); break;
			case 'J': for (auto &i : m_views) i.second->MoveCamPosition(-1.125f, 0.0f, 0.0f); break;
			case 'L': for (auto &i : m_views) i.second->MoveCamPosition(1.125f, 0.0f, 0.0f); break;
			case 'O': for (auto &i : m_views) i.second->MoveCamPosition(0.0f, 0.0f, -0.5f); break;
			case 'U': for (auto &i : m_views) i.second->MoveCamPosition(0.0f, 0.0f, 0.5f); break;
			}
		});
	}

	GraphicsSystem::~GraphicsSystem()
	{
		for (auto &i : m_views)
			delete i.second;
	}

	void GraphicsSystem::Update(float delta)
	{
		m_opengl->Display(m_views["Gimbal"]);
	}
}
