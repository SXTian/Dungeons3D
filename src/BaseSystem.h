/*****************************************************************************************
  Project      : 3D Game Engine
  Author       : Sam Tian
  Contributors :
******************************************************************************************/
#pragma once

namespace Dungeons3D
{
	class BaseSystem
	{
	public:
		virtual ~BaseSystem(){}
		virtual void Update(float delta) = 0;
	};
}