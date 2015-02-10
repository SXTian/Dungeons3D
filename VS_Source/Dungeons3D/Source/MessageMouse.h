/*****************************************************************************************
Project      : 3D Game Engine
Author       : Sam Tian
Contributors :
******************************************************************************************/
#pragma once

#include "IEventMessage.h"

namespace Dungeons3D
{
	struct MessageMouse : IEventMessage
	{
		MessageMouse(Events id) { msgID = id; }
		int wheel;
		unsigned key;
	};
}