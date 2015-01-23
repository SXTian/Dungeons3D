/*****************************************************************************************
  Project      : 3D Game Engine
  Author       : Sam Tian
  Contributors :
******************************************************************************************/
#pragma once

#include "ISystem.h"
#include "IEventMessage.h"

#include <string>
#include <map>
#include <memory>

namespace Dungeons3D
{
	class OpenGL; class IView;

	class GraphicsSystem : public ISystem, public IEventMessageModule
	{
	public:
		GraphicsSystem();
		~GraphicsSystem();

		void Update(float delta);

	private:
		std::shared_ptr<OpenGL> m_opengl;
		std::map<std::string, IView*> m_views;
	};
}