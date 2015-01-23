/*****************************************************************************************
  Project      : 3D Game Engine
  Author       : Sam Tian
  Contributors :
******************************************************************************************/
#pragma once

#include "Camera.h"

namespace Dungeons3D
{
	class OpenGL;
	 
	class IView : public ICamera
	{
		public:
			virtual ~IView(){}
			virtual void LoadMeshes() = 0;
			virtual void Display(OpenGL * opengl) = 0;
	};
}