/*****************************************************************************************
  Project      : 3D Game Engine
  Author       : Sam Tian
  Contributors :
******************************************************************************************/
#include "MessagingSystem.h"

namespace Dungeons3D
{
	MessagingSystem* MessagingSystem::_instance = 0;

	MessagingSystem::MessagingSystem()
	{
	}

	MessagingSystem::~MessagingSystem()
	{
	}

	MessagingSystem* MessagingSystem::GetInstance()
	{
		if (!_instance)
			_instance = new MessagingSystem();
		return _instance;
	}

	void MessagingSystem::Update(float delta)
	{
	}

	void MessagingSystem::Register(Events msgID, IEventMessageModule* pObj, Callback pFunc)
	{
		for (auto &c : _registry[msgID])
		{
			if (c.pObj == pObj && c.pFunc == pFunc)
				return;
		}

		CallbackObj callback = {pObj, pFunc};
		_registry[msgID].push_back(callback);
	}

	void MessagingSystem::Unregister(Events msgID, IEventMessageModule* pObj, Callback pFunc)
	{
		for (std::vector<CallbackObj>::iterator it = _registry[msgID].begin(); it < _registry[msgID].end(); ++it)
		{
			if (it->pObj == pObj && it->pFunc == pFunc)
				_registry[msgID].erase(it);
		}
	}

	void MessagingSystem::PostMessage(IEventMessage * pMsg)
	{
	}
}
