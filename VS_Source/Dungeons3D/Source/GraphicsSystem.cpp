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
#include "LightsView.h"

#include <iostream>

namespace Dungeons3D
{
	using namespace std;
	GraphicsSystem::GraphicsSystem() : m_opengl(new OpenGL())
	{
		m_views["Pantheon"] = new PantheonView(m_opengl);
		m_views["Gimbal"] = new GimbalView(m_opengl);
		m_views["Lights"] = new LightsView(m_opengl);

		for (auto &i : m_views)
			i.second->LoadMeshes();
	}
	GraphicsSystem::~GraphicsSystem()
	{
		for (auto &i : m_views)
			delete i.second;
	}

	void GraphicsSystem::Update(float delta)
	{
		m_opengl->Display(m_views["Lights"], delta);
	}
}
