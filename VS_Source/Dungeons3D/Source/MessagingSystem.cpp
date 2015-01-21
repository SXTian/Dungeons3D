/*****************************************************************************************
  Project      : 3D Game Engine
  Author       : Sam Tian
  Contributors :
******************************************************************************************/
#include "MessagingSystem.h"

namespace Dungeons3D
{
	MessagingSystem* MessagingSystem::m_instance = 0;

	MessagingSystem::MessagingSystem()
	{
	}

	MessagingSystem::~MessagingSystem()
	{
	}

	MessagingSystem* MessagingSystem::GetInstance()
	{
		if (!m_instance)
			m_instance = new MessagingSystem();
		return m_instance;
	}

	void MessagingSystem::Update(float delta)
	{
	}

	void MessagingSystem::Register(Events msgID, IEventMessageModule* pObj, Callback pFunc)
	{
		CallbackObj callback = {pObj, pFunc};
		m_registry[msgID].push_back(callback);
	}

	void MessagingSystem::Unregister(Events msgID, IEventMessageModule* pObj, Callback pFunc)
	{
		for (std::vector<CallbackObj>::iterator it = m_registry[msgID].begin(); it < m_registry[msgID].end(); ++it)
		{
			if (it->pObj == pObj)
				m_registry[msgID].erase(it);
		}
	}

	void MessagingSystem::PostMsg(IEventMessage * pMsg)
	{
		for (auto &c : m_registry[pMsg->msgID])
			c.pFunc(pMsg);
	}
}
