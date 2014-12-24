/*****************************************************************************************
  Project      : 3D Game Engine
  Author       : Sam Tian
  Contributors :
******************************************************************************************/
#include "GraphicsSystem.h"
#include "OpenGL.h"
#include "Loader.h"
#include <iostream>

namespace Dungeons3D
{

	GraphicsSystem::GraphicsSystem()
	{
		_openGL = new OpenGL();
	}

	GraphicsSystem::~GraphicsSystem()
	{
		delete _openGL;
	}

	void GraphicsSystem::Update(float delta)
	{
		_openGL->Display();
	}
}
