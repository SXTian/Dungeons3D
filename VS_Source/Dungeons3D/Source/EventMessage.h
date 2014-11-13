/*****************************************************************************************
  Project      : 3D Game Engine
  Author       : Sam Tian
  Contributors :
******************************************************************************************/
#pragma once

namespace Dungeons3D
{
	//	This is the boilerplate code for the event messaging system

	enum Events
	{
		MSG_Startup,
		MSG_Shutdown,

		MSG_Total
	};

	struct IEventMessage
	{
		Events msgID;
	};

	class IEventMessageModule;

	//	Function pointer that takes a message
	typedef void (IEventMessageModule::*Callback)(IEventMessage * pMessage);

	class IEventMessageModule
	{
	public:
		IEventMessageModule();
		~IEventMessageModule();

		void Register(Events msgID, IEventMessageModule* pObj, Callback pFunc);
		void Unregister(Events msgID, IEventMessageModule* pObj, Callback pFunc);

		void PostMessage(IEventMessage * pMsg);
	};
}
