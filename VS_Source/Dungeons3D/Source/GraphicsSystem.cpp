/*****************************************************************************************
  Project      : 3D Game Engine
  Author       : Sam Tian
  Contributors :
******************************************************************************************/
#include "GraphicsSystem.h"
#include "OpenGL.h"
#include <iostream>

namespace Dungeons3D
{

	GraphicsSystem::GraphicsSystem()
	{
		_pOpenGL = NULL;
	}

	GraphicsSystem::~GraphicsSystem()
	{
		if (_pOpenGL != NULL)
			delete _pOpenGL;
	}

	void GraphicsSystem::Initialize()
	{
		_pOpenGL = new OpenGL();
		_pOpenGL->Initialize();
	}
	void GraphicsSystem::Update(float delta)
	{
		_pOpenGL->Display();
	}
}
