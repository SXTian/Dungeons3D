/*****************************************************************************************
Project      : 3D Game Engine
Author       : Sam Tian
Contributors :
******************************************************************************************/
#pragma once

#include "GLHeaders.h"
#include "ShaderManager.h"

namespace Dungeons3D
{
	class IView;

	class OpenGL : public ShaderManager
	{
	public:
		OpenGL();
		~OpenGL();
		void Display(IView * view);

	private:
		void initGL();
		void configGL();
		void initShaders();
	};
}
