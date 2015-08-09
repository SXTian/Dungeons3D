/*****************************************************************************************
Project      : 3D Game Engine
Author       : Sam Tian
Contributors :
******************************************************************************************/
#pragma once

#include "IEventMessage.h"

namespace Dungeons3D
{
  struct MessageMouseMove : IEventMessage
  {
    MessageMouseMove(Events id) { msgID = id; }
    int x;
    int y;
  };
}