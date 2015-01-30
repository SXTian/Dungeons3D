/*****************************************************************************************
  Project      : 3D Game Engine
  Author       : Sam Tian
  Contributors :
******************************************************************************************/
#pragma once

#include "BaseSystem.h"
#include "IEventMessage.h"

#include <string>
#include <map>
#include <memory>

namespace Dungeons3D
{
	class OpenGL; class BaseView;

	class GraphicsSystem : public BaseSystem, public IEventMessageModule
	{
	public:
		GraphicsSystem();
		~GraphicsSystem();

		void Update(float delta);

	private:
		std::shared_ptr<OpenGL> m_opengl;
		std::map<std::string, BaseView*> m_views;
	};
}