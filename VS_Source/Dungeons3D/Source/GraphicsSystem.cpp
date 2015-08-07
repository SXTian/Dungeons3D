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
#include <memory>

namespace Dungeons3D
{
	using namespace std;
	GraphicsSystem::GraphicsSystem() : m_opengl(new OpenGL())
	{
		m_views["Pantheon"] = std::make_unique<PantheonView>(m_opengl);
		m_views["Gimbal"] = std::make_unique<GimbalView>(m_opengl);
		m_views["Lights"] = std::make_unique<LightsView>(m_opengl);

		for (auto &i : m_views)
			i.second->Initialize();
	}
	GraphicsSystem::~GraphicsSystem()
	{
	}

	void GraphicsSystem::Update(float delta)
	{
		m_opengl->Display(*m_views["Lights"], delta); //  pass BaseView reference
	}
}
