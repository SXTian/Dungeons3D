/*****************************************************************************************
Project      : 3D Game Engine
Author       : Sam Tian
Contributors :
******************************************************************************************/

#include "OpenGL.h"
#include "Math.h"
#include <iostream>
#include <vector>
#include <algorithm>

#define ARRAY_COUNT( array ) (sizeof( array ) / (sizeof( array[0] ) * (sizeof( array ) != sizeof(void*) || sizeof( array[0] ) <= sizeof(void*))))

#define GREEN_COLOR 0.0f, 1.0f, 0.0f, 1.0f
#define BLUE_COLOR 	0.0f, 0.0f, 1.0f, 1.0f
#define RED_COLOR 1.0f, 0.0f, 0.0f, 1.0f
#define GREY_COLOR 0.8f, 0.8f, 0.8f, 1.0f
#define BROWN_COLOR 0.5f, 0.5f, 0.0f, 1.0f

const float vertexData[] =
{
	+1.0f, +1.0f, +1.0f,
	-1.0f, -1.0f, +1.0f,
	-1.0f, +1.0f, -1.0f,
	+1.0f, -1.0f, -1.0f,

	-1.0f, -1.0f, -1.0f,
	+1.0f, +1.0f, -1.0f,
	+1.0f, -1.0f, +1.0f,
	-1.0f, +1.0f, +1.0f,

	GREEN_COLOR,
	BLUE_COLOR,
	RED_COLOR,
	BROWN_COLOR,

	GREEN_COLOR,
	BLUE_COLOR,
	RED_COLOR,
	BROWN_COLOR,
};

const GLshort indexData[] =
{
	0, 1, 2,
	1, 0, 3,
	2, 3, 0,
	3, 2, 1,

	5, 4, 6,
	4, 5, 7,
	7, 6, 4,
	6, 7, 5,
};

const int numberOfVertices = 8;


namespace Dungeons3D
{
	OpenGL::OpenGL()
	{
		//	For maths
		GenerateLookupTable();

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

		initShaders();
		initVertexBuffer();
		initVertexArrays();

		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glFrontFace(GL_CW);

		glEnable(GL_DEPTH_TEST);
		glDepthMask(GL_TRUE);
		glDepthFunc(GL_LEQUAL);
		glDepthRange(0.0f, 1.0f);
		glEnable(GL_DEPTH_CLAMP);

		glClearColor(0.0, 0.0, 0.0, 0.0);
		glClearDepth(1.0f);

		m_ccMtx = CalculateProjection(45.0f, 1.0f, 1000.0f);

		m_shaderManager.SetUniform(SHA_UniformColor, "cameraToClipMatrix", m_ccMtx.m);
		m_shaderManager.SetUniform(SHA_ObjectColor, "cameraToClipMatrix", m_ccMtx.m);
		m_shaderManager.SetUniform(SHA_UniformColorTint, "cameraToClipMatrix", m_ccMtx.m);

		glViewport(0, 0, 1680, 1050);

		test.Load("Resources/Meshes/UnitCubeColor.mesh");
	}

	OpenGL::~OpenGL()
	{
	}

	void display();


	void OpenGL::Display()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		for (auto i = 0; i < SHA_Total; ++i)
			m_shaderManager.SetUniform((ShaderID)i, "wordToCameraMatrx", m_camera.Matrix().m);

		m_shaderManager.Enable(SHA_Default);

		test.Render();

		/*
		glBindVertexArray(_vao);
		_shaderManager.SetUniform(SHA_Default, "offset", 0.0f, 0.0f, 0.5f);
		glDrawElements(GL_TRIANGLES, ARRAY_COUNT(indexData), GL_UNSIGNED_SHORT, 0);

		_shaderManager.SetUniform(SHA_Default, "offset", 0.0f, 0.0f, -1.0f);
		glDrawElementsBaseVertex(GL_TRIANGLES, ARRAY_COUNT(indexData), GL_UNSIGNED_SHORT, 0, numberOfVertices / 2);
		glBindVertexArray(0);
		_shaderManager.Disable();
		*/

	}

	//////////////////////////////////PRIVATE HELPERS///////////////////////////////////////
	void OpenGL::initShaders()
	{
		m_shaderManager.CreateProgram(SHA_UniformColor);
		m_shaderManager.LoadShader(SHA_UniformColor, "Resources/Shaders/PosOnlyWorldTransform.vert", GL_VERTEX_SHADER);
		m_shaderManager.LoadShader(SHA_UniformColor, "Resources/Shaders/ColorUniform.frag", GL_FRAGMENT_SHADER);
		m_shaderManager.LinkProgram(SHA_UniformColor);

		m_shaderManager.CreateProgram(SHA_ObjectColor);
		m_shaderManager.LoadShader(SHA_ObjectColor, "Resources/Shaders/PosColorWorldTransform.vert", GL_VERTEX_SHADER);
		m_shaderManager.LoadShader(SHA_ObjectColor, "Resources/Shaders/ColorPassthrough.frag", GL_FRAGMENT_SHADER);
		m_shaderManager.LinkProgram(SHA_ObjectColor);

		m_shaderManager.CreateProgram(SHA_UniformColorTint);
		m_shaderManager.LoadShader(SHA_UniformColorTint, "Resources/Shaders/PoasColorWorldTransform.vert", GL_VERTEX_SHADER);
		m_shaderManager.LoadShader(SHA_UniformColorTint, "Resources/Shaders/ColorMultiUniform.frag", GL_FRAGMENT_SHADER);
		m_shaderManager.LinkProgram(SHA_UniformColorTint);

		m_shaderManager.CreateProgram(SHA_Default);
		m_shaderManager.LoadShader(SHA_Default, "Resources/Shaders/Default.vert", GL_VERTEX_SHADER);
		m_shaderManager.LoadShader(SHA_Default, "Resources/Shaders/Default.frag", GL_FRAGMENT_SHADER);
		m_shaderManager.LinkProgram(SHA_Default);
	}

	void OpenGL::initVertexBuffer()
	{
		/*
		glGenBuffers(1, &_vbo);

		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glGenBuffers(1, &_ibo);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexData), indexData, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		*/
	}

	void OpenGL::initVertexArrays()
	{
		/*
		glGenVertexArrays(1, &_vao);
		glBindVertexArray(_vao);

		size_t colorDataOffset = sizeof(float) * 3 * numberOfVertices;

		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)colorDataOffset);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);

		glBindVertexArray(0);
		*/
	}

	Mtx44 OpenGL::CalculateProjection(float fovDeg, float zNear, float zFar)
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
