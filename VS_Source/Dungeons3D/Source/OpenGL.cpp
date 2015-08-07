/*****************************************************************************************
Project      : 3D Game Engine
Author       : Sam Tian
Contributors :
******************************************************************************************/

#include "OpenGL.h"
#include "Math.h"
#include "MatrixStack.h"
#include "BaseView.h"
#include <iostream>
#include <vector>
#include <algorithm>

namespace Dungeons3D
{
	OpenGL::OpenGL()
	{
		//	For maths
		GenerateLookupTable();

		initGL();
		configGL();
		configShaders();
	}

	OpenGL::~OpenGL()
	{
	}

	void OpenGL::Display(BaseView& view)
	{
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClearDepth(1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		view.Display();

		glUseProgram(0);

	}

	void OpenGL::Display(BaseView& view, float delta)
	{
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClearDepth(1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		view.Display(delta);

		glUseProgram(0);

	}

	//////////////////////////////////PRIVATE HELPERS///////////////////////////////////////

	void OpenGL::initGL()
	{
		glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	
		glutInitContextVersion (3, 3);
		glutInitContextFlags (GLUT_CORE_PROFILE | GLUT_DEBUG);

		glewExperimental = GL_TRUE;

		GLenum err = glewInit();

		if (GLEW_OK != err)	
			std::cout << "Error: " << glewGetErrorString(err) << std::endl;
		else 
		{
			if (GLEW_VERSION_3_3)
			{
				std::cout<<"Driver supports OpenGL 3.3\nDetails:" << std::endl;
			}
		}

		std::cout << "Using GLEW " << glewGetString(GLEW_VERSION) << std::endl;
		std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
		std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
		std::cout << "Version: " << glGetString(GL_VERSION) << std::endl;
		std::cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
	}

	void OpenGL::configGL()
	{
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glFrontFace(GL_CW);

		glEnable(GL_DEPTH_TEST);
		glDepthMask(GL_TRUE);
		glDepthFunc(GL_LEQUAL);
		glDepthRange(0.0f, 1.0f);
		glEnable(GL_DEPTH_CLAMP);

		glViewport(0, 0, 1680, 1050);
	}

	void OpenGL::configShaders()
	{
    CreateProgram(SHA_BasicLighting);
    LoadVertexShader(SHA_BasicLighting, "Resources/Shaders/BasicLighting.vert");
    LoadFragmentShader(SHA_BasicLighting, "Resources/Shaders/ColorPassthrough.frag");
    LinkProgram(SHA_BasicLighting);

		CreateProgram(SHA_UniformColor);
		LoadVertexShader(SHA_UniformColor, "Resources/Shaders/PosOnlyWorldTransform.vert");
		LoadFragmentShader(SHA_UniformColor, "Resources/Shaders/ColorUniform.frag");
		LinkProgram(SHA_UniformColor);

		CreateProgram(SHA_ObjectColor);
		LoadVertexShader(SHA_ObjectColor, "Resources/Shaders/PosColorWorldTransform.vert");
		LoadFragmentShader(SHA_ObjectColor, "Resources/Shaders/ColorPassthrough.frag");
		LinkProgram(SHA_ObjectColor);

		CreateProgram(SHA_UniformColorTint);
		LoadVertexShader(SHA_UniformColorTint, "Resources/Shaders/PosColorWorldTransform.vert");
		LoadFragmentShader(SHA_UniformColorTint, "Resources/Shaders/ColorMultUniform.frag");
		LinkProgram(SHA_UniformColorTint);

		BindUniformBlock(SHA_UniformColor, "GlobalMatrices");
		BindUniformBlock(SHA_ObjectColor, "GlobalMatrices");
		BindUniformBlock(SHA_UniformColorTint, "GlobalMatrices");

		CreateProgram(SHA_UniformColorLocal);
		LoadVertexShader(SHA_UniformColorLocal, "Resources/Shaders/PosColorLocalTransform.vert");
		LoadFragmentShader(SHA_UniformColorLocal, "Resources/Shaders/ColorMultUniform.frag");
		LinkProgram(SHA_UniformColorLocal);

		InitUBO();
	}
}
