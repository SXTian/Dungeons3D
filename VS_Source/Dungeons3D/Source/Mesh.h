/*****************************************************************************************
  Project      : 3D Game Engine
  Author       : Sam Tian
  Contributors :
******************************************************************************************/
#pragma once

#include <string>

namespace Dungeons3D
{
	template <typename SerializePolicy>
	class Mesh : private SerializePolicy
	{
	public:
		Mesh() {}
		void Load(std::string filename) { load(filename); }
		void Render() { render(); }
	};
}