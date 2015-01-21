/*****************************************************************************************
Project      : 3D Game Engine
Author       : Sam Tian
Contributors :
******************************************************************************************/
#pragma once

#include "EventMessage.h"

namespace Dungeons3D
{
	struct MessageKeyboard : IEventMessage
	{
		MessageKeyboard(Events id) { msgID = id; }
		unsigned key;
	};
}