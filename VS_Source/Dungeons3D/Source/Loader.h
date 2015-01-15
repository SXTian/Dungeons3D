/*****************************************************************************************
  Project      : 3D Game Engine
  Author       : Sam Tian
  Contributors :
******************************************************************************************/
#pragma once

#include <string>
#include <memory>

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

		std::unique_ptr<MeshData> m_data;
	};
}