/*****************************************************************************************
  Project      : 3D Game Engine
  Author       : Sam Tian
  Contributors :
******************************************************************************************/
#pragma once

#include "BaseSystem.h"
#include "IEventMessage.h"

#include <vector>

namespace Dungeons3D
{
	struct CallbackObj
	{
		IEventMessageModule* pObj;
		Callback pFunc;
	};

	class MessagingSystem : public BaseSystem
	{
	public:
		static MessagingSystem* GetInstance();

		void Update(float delta);

		void Register(Events msgID, IEventMessageModule* pObj, Callback pFunc);
		void Unregister(Events msgID, IEventMessageModule* pObj, Callback pFunc);
		void PostMsg(IEventMessage * pMsg);

	private: //	Methods
		MessagingSystem();
		~MessagingSystem();
	private: //	Members
		static MessagingSystem* m_instance;
		std::vector<CallbackObj> m_registry[MSG_Total];
	};
}
