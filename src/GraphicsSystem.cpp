/*****************************************************************************************
Project      : 3D Game Engine
Author       : Sam Tian
Contributors :
******************************************************************************************/
#include "GraphicsSystem.h"
#include "Camera.h"
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
    auto camera = std::make_shared<Camera>(1.0f, 100.0f);
		m_views["Pantheon"] = std::make_unique<PantheonView>(camera, m_opengl);
		m_views["Gimbal"] = std::make_unique<GimbalView>(camera, m_opengl);
		m_views["Lights"] = std::make_unique<LightsView>(camera, m_opengl);

		for (auto &i : m_views)
			i.second->Initialize();
	}
	GraphicsSystem::~GraphicsSystem()
	{
	}

	void GraphicsSystem::Update(float delta)
	{
		m_opengl->Display(*m_views["Pantheon"], delta); //  pass BaseView reference
	}
}
