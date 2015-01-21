/*****************************************************************************************
Project      : 3D Game Engine
Author       : Sam Tian
Contributors :
******************************************************************************************/
#include "GraphicsSystem.h"
#include "MessageKeyboard.h"
#include "OpenGL.h"
#include "Loader.h"
#include <iostream>

namespace Dungeons3D
{

	GraphicsSystem::GraphicsSystem()
	{
		m_openGL = new OpenGL();

		//	PRAISE BE THE LAMBDA!!
		Register(MSG_KeyPress, this, [&](IEventMessage * pMsg)
		{
			switch (((MessageKeyboard*)pMsg)->key)
			{
			case 'W': this->m_openGL->m_camera.MoveTarget(0.0f, 0.0f, -4.0f); break;
			case 'S': this->m_openGL->m_camera.MoveTarget(0.0f, 0.0f, 4.0f); break;
			case 'D': this->m_openGL->m_camera.MoveTarget(4.0f, 0.0f, 0.0f); break;
			case 'A': this->m_openGL->m_camera.MoveTarget(-4.0f, 0.0f, 0.0f); break;
			case 'E': this->m_openGL->m_camera.MoveTarget(0.0f, -4.0f, 0.0f); break;
			case 'Q': this->m_openGL->m_camera.MoveTarget(0.0f, 4.0f, 0.0f); break;

			case 'I': this->m_openGL->m_camera.MovePosition(0.0f, -1.125f, 0.0f); break;
			case 'K': this->m_openGL->m_camera.MovePosition(0.0f, 1.125f, 0.0f); break;
			case 'J': this->m_openGL->m_camera.MovePosition(-1.125f, 0.0f, 0.0f); break;
			case 'L': this->m_openGL->m_camera.MovePosition(1.125f, 0.0f, 0.0f); break;
			case 'O': this->m_openGL->m_camera.MovePosition(0.0f, 0.0f, -0.5f); break;
			case 'U': this->m_openGL->m_camera.MovePosition(0.0f, 0.0f, 0.5f); break;
			}
		});
	}

	GraphicsSystem::~GraphicsSystem()
	{
		delete m_openGL;
	}

	void GraphicsSystem::Update(float delta)
	{
		m_openGL->Display();
	}
}
