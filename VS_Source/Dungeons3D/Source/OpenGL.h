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
	class BaseView;

	class OpenGL : public ShaderManager
	{
	public:
		OpenGL();
		~OpenGL();
		void Display(BaseView& view);
		void Display(BaseView& view, float delta);

	private:
		void initGL();
		void configGL();
		void initShaders();
	};
}
