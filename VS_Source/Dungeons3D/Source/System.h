/*****************************************************************************************
  Project      : 3D Game Engine
  Author       : Sam Tian
  Contributors :
******************************************************************************************/
#pragma once

namespace Dungeons3D
{
	class ISystem
	{
	public:
		virtual ~ISystem(){}
		virtual void Initialize() = 0;
		virtual void Update(float delta) = 0;
	};
}