/*****************************************************************************************
  Project      : 3D Game Engine
  Author       : Sam Tian
  Contributors :
******************************************************************************************/
#pragma once

#include "System.h"
#include "EventMessage.h"
#include <string>

namespace Dungeons3D
{
	class OpenGL;

	class GraphicsSystem : public ISystem, public IEventMessageModule
	{
	public:
		GraphicsSystem();
		~GraphicsSystem();

		void Initialize();
		void Update(float delta);

	private:
		OpenGL* _pOpenGL;
	};
}