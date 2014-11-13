/*****************************************************************************************
  Project      : 3D Game Engine
  Author       : Sam Tian
  Contributors :
******************************************************************************************/
#include "EventMessage.h"
#include "MessagingSystem.h"

namespace Dungeons3D
{
	IEventMessageModule::IEventMessageModule()
	{
	}

	IEventMessageModule::~IEventMessageModule()
	{
	}

	void IEventMessageModule::Register(Events msgID, IEventMessageModule* pOjb, Callback pFunc)
	{
		MessagingSystem::GetInstance()->Register(msgID, pOjb, pFunc);
	}

	void IEventMessageModule::Unregister(Events msgID, IEventMessageModule* pOjb, Callback pFunc)
	{
		MessagingSystem::GetInstance()->Unregister(msgID, pOjb, pFunc);
	}

	void IEventMessageModule::PostMessage(IEventMessage * pMsg)
	{
		MessagingSystem::GetInstance()->PostMessage(pMsg);
	}
}
