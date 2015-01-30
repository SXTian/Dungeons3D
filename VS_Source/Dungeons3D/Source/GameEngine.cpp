/*****************************************************************************************
Project      : 3D Game Engine
Author       : Sam Tian
Contributors :
******************************************************************************************/
#include "GameEngine.h"
#include "MessageKeyboard.h"
#include "WinSystem.h"
#include "GraphicsSystem.h"

namespace Dungeons3D
{
	GameEngine::GameEngine() : m_curr(0), m_dt(0), m_active(true)
	{
		QueryPerformanceFrequency(&m_ticksPerSec);
		QueryPerformanceCounter(&m_counter);

		m_prev = (double)m_counter.QuadPart;

		Register(MSG_KeyPress, this, [&](IEventMessage * pMsg)
		{
			switch (((MessageKeyboard*)pMsg)->key)
			{
			case VK_ESCAPE: m_active = false; break;
			}
		});
	}

	GameEngine::~GameEngine()
	{
	}

	void GameEngine::AddSystem(SystemID id)
	{
		switch (id)
		{
		case SYS_WINDOWS: m_systems.push_back(new WinSystem("./Resources/config.txt")); break;
		case SYS_GRAPHICS:m_systems.push_back(new GraphicsSystem()); break;
		}
	}

	void GameEngine::GameLoop()
	{
		while(m_active)
		{
			QueryPerformanceCounter(&m_counter);

			m_curr = (double)m_counter.QuadPart;
			m_dt = (m_curr - m_prev) * (1.0 / (double)m_ticksPerSec.QuadPart);

			m_prev = m_curr;

			for (auto &i : m_systems)
				i->Update((float)m_dt);
		}
	}

}