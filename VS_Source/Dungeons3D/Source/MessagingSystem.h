/*****************************************************************************************
  Project      : 3D Game Engine
  Author       : Sam Tian
  Contributors :
******************************************************************************************/
#pragma once

#include "System.h"
#include "EventMessage.h"

#include <vector>

namespace Dungeons3D
{
	struct CallbackObj
	{
		IEventMessageModule* pObj;
		Callback pFunc;
	};

	class MessagingSystem : public ISystem
	{
	public:
		static MessagingSystem* GetInstance();

		void Update(float delta);

		void Register(Events msgID, IEventMessageModule* pObj, Callback pFunc);
		void Unregister(Events msgID, IEventMessageModule* pObj, Callback pFunc);
		void PostMessage(IEventMessage * pMsg);

	private: //	Methods
		MessagingSystem();
		~MessagingSystem();
	private: //	Members
		static MessagingSystem* _instance;
		std::vector<CallbackObj> _registry[MSG_Total];
	};
}
