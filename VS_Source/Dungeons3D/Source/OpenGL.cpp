/*****************************************************************************************
Project      : 3D Game Engine
Author       : Sam Tian
Contributors :
******************************************************************************************/

#include "OpenGL.h"
#include <iostream>
#include <vector>
#include <algorithm>

const float vertexData[] = {
     0.0f,    0.5f, 0.0f, 1.0f,
     0.5f, -0.366f, 0.0f, 1.0f,
    -0.5f, -0.366f, 0.0f, 1.0f,
     1.0f,    0.0f, 0.0f, 1.0f,
     0.0f,    1.0f, 0.0f, 1.0f,
     0.0f,    0.0f, 1.0f, 1.0f,
};

namespace Dungeons3D
{
	OpenGL::OpenGL()
	{
		_pShaderManager = NULL;
	}

	OpenGL::~OpenGL()
	{
		if (_pShaderManager != NULL)
			delete _pShaderManager;
	}

	void display();

	void OpenGL::Initialize()
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


		glClearColor(0.0, 0.0, 0.0, 0.0);
		glShadeModel(GL_SMOOTH);
		glEnable(GL_DEPTH_TEST);
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		initShaders();
		initVertexBuffer();
	}

	void OpenGL::Display()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		_pShaderManager->Enable(SHA_Default);

		glBindBuffer(GL_ARRAY_BUFFER, _positionBuffer);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)48);

		glDrawArrays(GL_TRIANGLES, 0, 3);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		_pShaderManager->Disable();

		glFlush();
		
	}

	void OpenGL::initShaders()
	{
		_pShaderManager = new ShaderManager();

		_pShaderManager->CreateProgram(SHA_Default);
		_pShaderManager->LoadShader(SHA_Default, "Resources/Shaders/Vertex.txt", GL_VERTEX_SHADER);
		_pShaderManager->LoadShader(SHA_Default, "Resources/Shaders/Fragment.txt", GL_FRAGMENT_SHADER);
		_pShaderManager->LinkProgram(SHA_Default);
	}

	void OpenGL::initVertexBuffer()
	{
		glGenBuffers(1, &_positionBuffer);

		glBindBuffer(GL_ARRAY_BUFFER, _positionBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}