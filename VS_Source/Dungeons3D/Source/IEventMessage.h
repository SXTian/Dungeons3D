/*****************************************************************************************
Project      : 3D Game Engine
Author       : Sam Tian
Contributors :
******************************************************************************************/
#pragma once

#include <functional>

namespace Dungeons3D
{
	enum Events
	{
		MSG_Startup,
		MSG_Shutdown,
		MSG_KeyPress,
		MSG_Total
	};

	struct IEventMessage
	{
		Events msgID;
	};

	//	Function pointer that takes a message
	//typedef void (IEventMessageModule::*Callback)(IEventMessage * pMessage);

	typedef std::function<void(IEventMessage*)> Callback;

	class IEventMessageModule
	{
	public:
		IEventMessageModule();
		~IEventMessageModule();

		void Register(Events msgID, IEventMessageModule* pObj, Callback pFunc);
		void Unregister(Events msgID, IEventMessageModule* pObj, Callback pFunc);

		void PostMsg(IEventMessage * pMsg);
	};
}
