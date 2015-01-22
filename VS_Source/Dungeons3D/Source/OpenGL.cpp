/*****************************************************************************************
Project      : 3D Game Engine
Author       : Sam Tian
Contributors :
******************************************************************************************/

#include "OpenGL.h"
#include "Math.h"
#include "MatrixStack.h"
#include "Parthenon.h"
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

		m_meshCube.Load("Resources/Meshes/UnitCube.mesh");
		m_meshCubeColor.Load("Resources/Meshes/UnitCubeColor.mesh");
		m_meshPlane.Load("Resources/Meshes/UnitPlane.mesh");
		m_meshCone.Load("Resources/Meshes/UnitCone.mesh");
		m_meshCylinder.Load("Resources/Meshes/UnitCylinder.mesh");
	}

	OpenGL::~OpenGL()
	{
	}

	void OpenGL::Display()
	{
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClearDepth(1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//	Transpose to column-wise
		m_shaderManager.SetUniformBlock(m_camera.Matrix().Transpose().m, 1);

		drawGround();
		drawForest();
		drawParthenon();

		m_shaderManager.Disable();
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
		m_shaderManager.CreateProgram(SHA_UniformColor);
		m_shaderManager.LoadShader(SHA_UniformColor, "Resources/Shaders/PosOnlyWorldTransform.vert", GL_VERTEX_SHADER);
		m_shaderManager.LoadShader(SHA_UniformColor, "Resources/Shaders/ColorUniform.frag", GL_FRAGMENT_SHADER);
		m_shaderManager.LinkProgram(SHA_UniformColor);

		m_shaderManager.CreateProgram(SHA_ObjectColor);
		m_shaderManager.LoadShader(SHA_ObjectColor, "Resources/Shaders/PosColorWorldTransform.vert", GL_VERTEX_SHADER);
		m_shaderManager.LoadShader(SHA_ObjectColor, "Resources/Shaders/ColorPassthrough.frag", GL_FRAGMENT_SHADER);
		m_shaderManager.LinkProgram(SHA_ObjectColor);

		m_shaderManager.CreateProgram(SHA_UniformColorTint);
		m_shaderManager.LoadShader(SHA_UniformColorTint, "Resources/Shaders/PosColorWorldTransform.vert", GL_VERTEX_SHADER);
		m_shaderManager.LoadShader(SHA_UniformColorTint, "Resources/Shaders/ColorMultUniform.frag", GL_FRAGMENT_SHADER);
		m_shaderManager.LinkProgram(SHA_UniformColorTint);

		m_shaderManager.BindUniformBlock(SHA_UniformColor, "GlobalMatrices");
		m_shaderManager.BindUniformBlock(SHA_ObjectColor, "GlobalMatrices");
		m_shaderManager.BindUniformBlock(SHA_UniformColorTint, "GlobalMatrices");
		m_shaderManager.InitUBO();

		//	Transpose to column-wise
		m_shaderManager.SetUniformBlock(m_ccMtx.Transpose().m, 0);

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

	void OpenGL::drawGround()
	{
		m_mwMtx.IdentityThis();
		m_mwMtx.ScaleThis(100.0f, 1.0f, 100.0f);

		m_shaderManager.SetUniform(SHA_UniformColor, "modelToWorldMatrix", m_mwMtx.m);
		m_shaderManager.SetUniform(SHA_UniformColor, "baseColor", 0.302f, 0.416f, 0.0589f, 1.0f);
		m_meshPlane.Render();
	}

	void OpenGL::drawForest()
	{
		MatrixStack mStack;
		for (auto i : forest)
		{
			mStack.matrix.TranslateThis(i.xPos, 0.0f, i.zPos);

			//	Draw Trunk
			mStack.Push();

			mStack.matrix.ScaleThis(1.0f, i.heightTrunk, 1.0f);
			mStack.matrix.TranslateThis(0.0f, 0.5f, 0.0f);

			m_shaderManager.SetUniform(SHA_UniformColorTint, "modelToWorldMatrix", mStack.matrix.m);
			m_shaderManager.SetUniform(SHA_UniformColorTint, "baseColor", 0.694f, 0.4f, 0.106f, 1.0f);
			m_meshCylinder.Render();

			mStack.Pop();

			//	Draw Trunk
			mStack.Push();

			mStack.matrix.TranslateThis(0.0f, i.heightTrunk, 0.0f);
			mStack.matrix.ScaleThis(3.0f, i.heightCone, 3.0f);

			m_shaderManager.SetUniform(SHA_UniformColorTint, "modelToWorldMatrix", mStack.matrix.m);
			m_shaderManager.SetUniform(SHA_UniformColorTint, "baseColor", 0.0f, 1.0f, 0.0f, 1.0f);
			m_meshCone.Render();

			mStack.Pop();
			mStack.matrix.IdentityThis();
		}
	}

	void OpenGL::drawParthenon()
	{
		MatrixStack mStack;

		mStack.matrix.TranslateThis(20.0f, 0.0f, -10.0f);

		//	Draw base
		mStack.Push();

		mStack.matrix.ScaleThis(parthenonWidth, parthenonBaseHeight, parthenonLength);
		mStack.matrix.TranslateThis(0.0f, 0.5f, 0.0f);

		m_shaderManager.SetUniform(SHA_UniformColorTint, "modelToWorldMatrix", mStack.matrix.m);
		m_shaderManager.SetUniform(SHA_UniformColorTint, "baseColor", 0.9f, 0.9f, 0.9f, 0.9f);
		m_meshCube.Render();

		mStack.Pop();

		//	Draw top
		mStack.Push();

		mStack.matrix.TranslateThis(0.0f, parthenonColumnHeight + parthenonBaseHeight, 0.0f);
		mStack.matrix.ScaleThis(parthenonWidth, parthenonTopHeight, parthenonLength);
		mStack.matrix.TranslateThis(0.0f, 0.5f, 0.0f);

		m_shaderManager.SetUniform(SHA_UniformColorTint, "modelToWorldMatrix", mStack.matrix.m);
		m_shaderManager.SetUniform(SHA_UniformColorTint, "baseColor", 0.9f, 0.9f, 0.9f, 0.9f);
		m_meshCube.Render();

		mStack.Pop();

		//	Draw front & back columns
		for (int iColumn = 0; iColumn < int(parthenonWidth / 2.0f); ++iColumn)
		{
			//	Front
			mStack.Push();
			mStack.matrix.TranslateThis((2.0f * iColumn) - (parthenonWidth / 2.0f) + 1.0f, parthenonBaseHeight, frontZ);
			drawColumn(mStack.matrix, parthenonColumnHeight);
			mStack.Pop();

			//	Back
			mStack.Push();
			mStack.matrix.TranslateThis((2.0f * iColumn) - (parthenonWidth / 2.0f) + 1.0f, parthenonBaseHeight, -frontZ);
			drawColumn(mStack.matrix, parthenonColumnHeight);
			mStack.Pop();
		}

		//	Draw left & right columns (no doublecount first/last)
		for (int iColumn = 1; iColumn < int((parthenonLength - 2.0f) / 2.0f); ++iColumn)
		{
			//	Left
			mStack.Push();
			mStack.matrix.TranslateThis(rightX, parthenonBaseHeight, (2.0f * iColumn) - (parthenonLength / 2.0f) + 1.0f);
			drawColumn(mStack.matrix, parthenonColumnHeight);
			mStack.Pop();

			//	Right
			mStack.Push();
			mStack.matrix.TranslateThis(-rightX, parthenonBaseHeight, (2.0f * iColumn) - (parthenonLength / 2.0f) + 1.0f);
			drawColumn(mStack.matrix, parthenonColumnHeight);
			mStack.Pop();
		}

		/*
		//	Draw interior
		mStack.Push();

		mStack.matrix.TranslateThis(0.0f, 1.0f, 0.0f);
		mStack.matrix.ScaleThis(parthenonWidth - 6.0f, parthenonColumnHeight, parthenonLength - 6.0f);
		mStack.matrix.TranslateThis(0.0f, 0.5f, 0.0f);

		m_shaderManager.SetUniform(SHA_ObjectColor, "modelToWorldMatrix", mStack.matrix.m);
		m_meshCubeColor.Render();

		mStack.Pop();

		//	Draw headpiece
		mStack.Push();

		mStack.matrix.TranslateThis(0.0f, parthenonColumnHeight + parthenonBaseHeight + (parthenonTopHeight / 2.0f), parthenonLength / 2.0f);
		mStack.matrix.RotateThis(1.0f, 0.0f, 0.0f, -135.0f);
		mStack.matrix.RotateThis(0.0f, 1.0f, 0.0f, 45.0f);

		m_shaderManager.SetUniform(SHA_ObjectColor, "modelToWorldMatrix", mStack.matrix.m);
		m_meshCubeColor.Render();

		mStack.Pop();
		*/
	}

	void OpenGL::drawColumn(Mtx44 matrix, float height)
	{
		MatrixStack mStack;
		mStack.matrix = matrix;

		//	Draw bottom
		mStack.Push();

		mStack.matrix.ScaleThis(1.0f, columnBaseHeight, 1.0f);
		mStack.matrix.TranslateThis(0.0f, 0.5f, 0.0f);

		m_shaderManager.SetUniform(SHA_UniformColorTint, "modelToWorldMatrix", mStack.matrix.m);
		m_shaderManager.SetUniform(SHA_UniformColorTint, "baseColor", 0.9f, 0.9f, 0.9f, 0.9f);
		m_meshCube.Render();

		mStack.Pop();

		//	Draw top
		mStack.Push();

		mStack.matrix.TranslateThis(0.0f, height - columnBaseHeight, 0.0f);
		mStack.matrix.ScaleThis(1.0f, columnBaseHeight, 1.0f);
		mStack.matrix.TranslateThis(0.0f, 0.5f, 0.0f);

		m_shaderManager.SetUniform(SHA_UniformColorTint, "modelToWorldMatrix", mStack.matrix.m);
		m_shaderManager.SetUniform(SHA_UniformColorTint, "baseColor", 0.9f, 0.9f, 0.9f, 0.9f);
		m_meshCube.Render();

		mStack.Pop();

		//	Draw main column
		mStack.Push();

		mStack.matrix.TranslateThis(0.0f, columnBaseHeight, 0.0f);
		mStack.matrix.ScaleThis(0.8f, height - (columnBaseHeight * 2.0f), 0.8f);
		mStack.matrix.TranslateThis(0.0f, 0.5f, 0.0f);

		m_shaderManager.SetUniform(SHA_UniformColorTint, "modelToWorldMatrix", mStack.matrix.m);
		m_shaderManager.SetUniform(SHA_UniformColorTint, "baseColor", 0.9f, 0.9f, 0.9f, 0.9f);
		m_meshCylinder.Render();
	}
}
