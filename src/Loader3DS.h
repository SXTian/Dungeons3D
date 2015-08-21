/*****************************************************************************************
  Project      : 3D Game Engine
  Author       : Sam Tian
  Contributors :
******************************************************************************************/
#pragma once

#include "Parser3DS.h"

#include <string>
#include <memory>
#include <vector>

namespace Dungeons3D
{
	struct MeshData;

	class Loader3DS : Parser3DS
	{
	protected:
		Loader3DS();
		~Loader3DS();
		void load(std::string filename);
		void render();

		MeshData * m_data[5];
	};
}