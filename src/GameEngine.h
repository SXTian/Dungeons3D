/*****************************************************************************************
Project      : 3D Game Engine
Author       : Sam Tian
Contributors :
******************************************************************************************/
#pragma once

#include "IEventMessage.h"
#include <windows.h>
#include <vector>
#include <memory>

namespace Dungeons3D
{
	enum SystemID
	{
		SYS_WINDOWS,
		SYS_GRAPHICS,
		SYS_TOTAL
	};

	class BaseSystem;

	class GameEngine : public IEventMessageModule
	{
	public:
		GameEngine();
		~GameEngine();
		void AddSystem(SystemID id);
		void GameLoop();
	private:
		std::vector<BaseSystem*> m_systems;
		bool m_active;

		double m_curr;
		double m_prev;
		double m_dt;

		LARGE_INTEGER m_ticksPerSec;
		LARGE_INTEGER m_counter;
	};
}