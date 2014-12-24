/*****************************************************************************************
  Project      : 3D Game Engine
  Author       : Sam Tian
  Contributors :
******************************************************************************************/
#pragma once

#include <string>

namespace Dungeons3D
{
	struct MeshData;

	class Loader
	{
	protected:
		Loader();
		~Loader();
		void load(std::string filename);
		void render();

		MeshData * _data;
	};
}