/*****************************************************************************************
  Project      : 3D Game Engine
  Author       : Sam Tian
  Contributors :
******************************************************************************************/

#include "Mesh.h"

namespace Dungeons3D
{

	Mesh::Mesh()
	{
		_loader = new 
	}

	void GraphicsSystem::Initialize()
	{
		_openGL.Initialize();
	}
	void GraphicsSystem::Update(float delta)
	{
		_openGL.Display();
	}
}
