/*****************************************************************************************
Project      : 3D Game Engine
Author       : Sam Tian
Contributors :
******************************************************************************************/

#include "OpenGL.h"
#include "Math.h"
#include "MatrixStack.h"
#include "View.h"
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
		initShaders();
	}

	OpenGL::~OpenGL()
	{
	}

	void OpenGL::Display(IView * view)
	{
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClearDepth(1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		view->Display(this);

		DisableProgram();
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

		m_ccMtx = calcProjection(45.0f, 1.0f, 1000.0f);
	}

	void OpenGL::initShaders()
	{
		CreateProgram(SHA_UniformColor);
		LoadShader(SHA_UniformColor, "Resources/Shaders/PosOnlyWorldTransform.vert", GL_VERTEX_SHADER);
		LoadShader(SHA_UniformColor, "Resources/Shaders/ColorUniform.frag", GL_FRAGMENT_SHADER);
		LinkProgram(SHA_UniformColor);

		CreateProgram(SHA_ObjectColor);
		LoadShader(SHA_ObjectColor, "Resources/Shaders/PosColorWorldTransform.vert", GL_VERTEX_SHADER);
		LoadShader(SHA_ObjectColor, "Resources/Shaders/ColorPassthrough.frag", GL_FRAGMENT_SHADER);
		LinkProgram(SHA_ObjectColor);

		CreateProgram(SHA_UniformColorTint);
		LoadShader(SHA_UniformColorTint, "Resources/Shaders/PosColorWorldTransform.vert", GL_VERTEX_SHADER);
		LoadShader(SHA_UniformColorTint, "Resources/Shaders/ColorMultUniform.frag", GL_FRAGMENT_SHADER);
		LinkProgram(SHA_UniformColorTint);

		BindUniformBlock(SHA_UniformColor, "GlobalMatrices");
		BindUniformBlock(SHA_ObjectColor, "GlobalMatrices");
		BindUniformBlock(SHA_UniformColorTint, "GlobalMatrices");
		InitUBO();

		//	Transpose to column-wise
		SetShaderUniformBlock(m_ccMtx.Transpose().m, 0);

		/*
		m_shaderManager.CreateProgram(SHA_Default);
		m_shaderManager.LoadShader(SHA_Default, "Resources/Shaders/Default.vert", GL_VERTEX_SHADER);
		m_shaderManager.LoadShader(SHA_Default, "Resources/Shaders/Default.frag", GL_FRAGMENT_SHADER);
		m_shaderManager.LinkProgram(SHA_Default);

		m_shaderManager.SetUniform(SHA_Default, "perspectiveMatrix", m_ccMtx.m);
		*/
	}

	Mtx44 OpenGL::calcProjection(float fovDeg, float zNear, float zFar)
	{
		float yMax = zNear * TanLookup(fovDeg);
		float yMin = -yMax;
		float xMax = yMax * ((float)1680 / (float)1050);
		float xMin = -xMax;

		Mtx44 matrix(Mtx44::Identity());

		matrix.RowCol(0, 0) = (2.0f * zNear) / (xMax - xMin);
		matrix.RowCol(1, 1) = (2.0f * zNear) / (yMax - yMin);
		matrix.RowCol(0, 2) = (xMax + xMin)  / (xMax - xMin);
		matrix.RowCol(1, 2) = (yMax + yMin)  / (yMax - yMin);
		matrix.RowCol(2, 2) = (-zFar - zNear) / (zFar - zNear);
		matrix.RowCol(3, 2) = -1.0f;
		matrix.RowCol(2, 3) = (-2.0f * zNear * zFar) / (zFar - zNear);
		matrix.RowCol(3, 3) = 0.0f;

		return matrix;
	}
}
