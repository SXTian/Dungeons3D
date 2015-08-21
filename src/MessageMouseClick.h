/*****************************************************************************************
Project      : 3D Game Engine
Author       : Sam Tian
Contributors :
******************************************************************************************/
#pragma once

#include "IEventMessage.h"

namespace Dungeons3D
{
  struct MessageMouseClick : IEventMessage
  {
    MessageMouseClick(Events id) { msgID = id; }
    int key;
  };
}