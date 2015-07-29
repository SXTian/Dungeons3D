/*****************************************************************************************
Project      : 3D Game Engine
Author       : Sam Tian
Contributors :
******************************************************************************************/
#include "PantheonView.h"
#include "OpenGL.h"
#include "MatrixStack.h"
#include "MessageKeyboard.h"
#include "MessageMouse.h"

namespace Dungeons3D
{
	using namespace std;

	static const TreeData forest[] =
	{
		{-45.0f, -40.0f, 2.0f, 3.0f},
		{-42.0f, -35.0f, 2.0f, 3.0f},
		{-39.0f, -29.0f, 2.0f, 4.0f},
		{-44.0f, -26.0f, 3.0f, 3.0f},
		{-40.0f, -22.0f, 2.0f, 4.0f},
		{-36.0f, -15.0f, 3.0f, 3.0f},
		{-41.0f, -11.0f, 2.0f, 3.0f},
		{-37.0f, -6.0f, 3.0f, 3.0f},
		{-45.0f, 0.0f, 2.0f, 3.0f},
		{-39.0f, 4.0f, 3.0f, 4.0f},
		{-36.0f, 8.0f, 2.0f, 3.0f},
		{-44.0f, 13.0f, 3.0f, 3.0f},
		{-42.0f, 17.0f, 2.0f, 3.0f},
		{-38.0f, 23.0f, 3.0f, 4.0f},
		{-41.0f, 27.0f, 2.0f, 3.0f},
		{-39.0f, 32.0f, 3.0f, 3.0f},
		{-44.0f, 37.0f, 3.0f, 4.0f},
		{-36.0f, 42.0f, 2.0f, 3.0f},
		{-32.0f, -45.0f, 2.0f, 3.0f},
		{-30.0f, -42.0f, 2.0f, 4.0f},
		{-34.0f, -38.0f, 3.0f, 5.0f},
		{-33.0f, -35.0f, 3.0f, 4.0f},
		{-29.0f, -28.0f, 2.0f, 3.0f},
		{-26.0f, -25.0f, 3.0f, 5.0f},
		{-35.0f, -21.0f, 3.0f, 4.0f},
		{-31.0f, -17.0f, 3.0f, 3.0f},
		{-28.0f, -12.0f, 2.0f, 4.0f},
		{-29.0f, -7.0f, 3.0f, 3.0f},
		{-26.0f, -1.0f, 2.0f, 4.0f},
		{-32.0f, 6.0f, 2.0f, 3.0f},
		{-30.0f, 10.0f, 3.0f, 5.0f},
		{-33.0f, 14.0f, 2.0f, 4.0f},
		{-35.0f, 19.0f, 3.0f, 4.0f},
		{-28.0f, 22.0f, 2.0f, 3.0f},
		{-33.0f, 26.0f, 3.0f, 3.0f},
		{-29.0f, 31.0f, 3.0f, 4.0f},
		{-32.0f, 38.0f, 2.0f, 3.0f},
		{-27.0f, 41.0f, 3.0f, 4.0f},
		{-31.0f, 45.0f, 2.0f, 4.0f},
		{-28.0f, 48.0f, 3.0f, 5.0f},
		{-25.0f, -48.0f, 2.0f, 3.0f},
		{-20.0f, -42.0f, 3.0f, 4.0f},
		{-22.0f, -39.0f, 2.0f, 3.0f},
		{-19.0f, -34.0f, 2.0f, 3.0f},
		{-23.0f, -30.0f, 3.0f, 4.0f},
		{-24.0f, -24.0f, 2.0f, 3.0f},
		{-16.0f, -21.0f, 2.0f, 3.0f},
		{-17.0f, -17.0f, 3.0f, 3.0f},
		{-25.0f, -13.0f, 2.0f, 4.0f},
		{-23.0f, -8.0f, 2.0f, 3.0f},
		{-17.0f, -2.0f, 3.0f, 3.0f},
		{-16.0f, 1.0f, 2.0f, 3.0f},
		{-19.0f, 4.0f, 3.0f, 3.0f},
		{-22.0f, 8.0f, 2.0f, 4.0f},
		{-21.0f, 14.0f, 2.0f, 3.0f},
		{-16.0f, 19.0f, 2.0f, 3.0f},
		{-23.0f, 24.0f, 3.0f, 3.0f},
		{-18.0f, 28.0f, 2.0f, 4.0f},
		{-24.0f, 31.0f, 2.0f, 3.0f},
		{-20.0f, 36.0f, 2.0f, 3.0f},
		{-22.0f, 41.0f, 3.0f, 3.0f},
		{-21.0f, 45.0f, 2.0f, 3.0f},
		{-12.0f, -40.0f, 2.0f, 4.0f},
		{-11.0f, -35.0f, 3.0f, 3.0f},
		{-10.0f, -29.0f, 1.0f, 3.0f},
		{-9.0f, -26.0f, 2.0f, 2.0f},
		{-6.0f, -22.0f, 2.0f, 3.0f},
		{-15.0f, -15.0f, 1.0f, 3.0f},
		{-8.0f, -11.0f, 2.0f, 3.0f},
		{-14.0f, -6.0f, 2.0f, 4.0f},
		{-12.0f, 0.0f, 2.0f, 3.0f},
		{-7.0f, 4.0f, 2.0f, 2.0f},
		{-13.0f, 8.0f, 2.0f, 2.0f},
		{-9.0f, 13.0f, 1.0f, 3.0f},
		{-13.0f, 17.0f, 3.0f, 4.0f},
		{-6.0f, 23.0f, 2.0f, 3.0f},
		{-12.0f, 27.0f, 1.0f, 2.0f},
		{-8.0f, 32.0f, 2.0f, 3.0f},
		{-10.0f, 37.0f, 3.0f, 3.0f},
		{-11.0f, 42.0f, 2.0f, 2.0f},
		{15.0f, 5.0f, 2.0f, 3.0f},
		{15.0f, 10.0f, 2.0f, 3.0f},
		{15.0f, 15.0f, 2.0f, 3.0f},
		{15.0f, 20.0f, 2.0f, 3.0f},
		{15.0f, 25.0f, 2.0f, 3.0f},
		{15.0f, 30.0f, 2.0f, 3.0f},
		{15.0f, 35.0f, 2.0f, 3.0f},
		{15.0f, 40.0f, 2.0f, 3.0f},
		{15.0f, 45.0f, 2.0f, 3.0f},
		{25.0f, 5.0f, 2.0f, 3.0f},
		{25.0f, 10.0f, 2.0f, 3.0f},
		{25.0f, 15.0f, 2.0f, 3.0f},
		{25.0f, 20.0f, 2.0f, 3.0f},
		{25.0f, 25.0f, 2.0f, 3.0f},
		{25.0f, 30.0f, 2.0f, 3.0f},
		{25.0f, 35.0f, 2.0f, 3.0f},
		{25.0f, 40.0f, 2.0f, 3.0f},
		{25.0f, 45.0f, 2.0f, 3.0f},
	};

	const float parthenonWidth = 14.0f;
	const float parthenonLength = 20.0f;
	const float parthenonColumnHeight = 5.0f;
	const float parthenonBaseHeight = 1.0f;
	const float parthenonTopHeight = 2.0f;

	const float frontZ = (parthenonLength / 2.0f) - 1.0f;
	const float rightX = (parthenonWidth / 2.0f) - 1.0f;

	const float columnBaseHeight = 0.25f;

	PantheonView::PantheonView(shared_ptr<ShaderManager> pManager) : IShaderManager(pManager), Camera(1.0f, 100.0f)
	{
		m_mouseDelta[0] = 0;
		m_mouseDelta[1] = 0;
		m_oldMouseDelta[0] = 0;
		m_oldMouseDelta[1] = 0;

		Register(MSG_MouseMove, this, [&](IEventMessage * pMsg)
		{
			POINT mousePos;
			GetCursorPos(&mousePos);
			m_mouseDelta[0] = mousePos.x - m_oldMouseDelta[0];
			m_mouseDelta[1] = mousePos.y - m_oldMouseDelta[1];
			m_oldMouseDelta[0] = mousePos.x;
			m_oldMouseDelta[1] = mousePos.y;
		});

		Register(MSG_MouseWheel, this, [&](IEventMessage * pMsg)
		{
			ZoomCam(-((MessageMouse*)pMsg)->wheel / 10.0f);
		});

		
		Register(MSG_KeyPress, this, [&](IEventMessage * pMsg)
		{
			switch (((MessageKeyboard*)pMsg)->key)
			{
			case 'W': ZoomCam(10.0f); break;
			case 'S': ZoomCam(-10.0f); break;
			}
		});
	}

	PantheonView::~PantheonView()
	{
	}

	void PantheonView::LoadMeshes()
	{
		m_meshCube.Load("Resources/Meshes/UnitCube.mesh");
		m_meshCubeColor.Load("Resources/Meshes/UnitCubeColor.mesh");
		m_meshPlane.Load("Resources/Meshes/UnitPlane.mesh");
		m_meshCone.Load("Resources/Meshes/UnitCone.mesh");
		m_meshCylinder.Load("Resources/Meshes/UnitCylinder.mesh");
		m_wizard.Load("Resources/Meshes/wizard.3DS");

		//	Transpose to column-wise, 0 is for the index in the uniform block
		SetShaderUniformBlock(ViewMatrix().Transpose().m, 0);
	}

	void PantheonView::Display()
	{
		//	Transpose to column-wise
		SetShaderUniformBlock(CamMatrix().Transpose().m, 1);

		drawGround();
		drawForest();
		drawParthenon();
	}

	void PantheonView::Display(float delta)
	{
		RotateCamY(Clamp(-(float)m_mouseDelta[0], -5.0f, 5.0f));
		RotateCamX(Clamp((float)m_mouseDelta[1], -5.0f, 5.0f));

		m_mouseDelta[0] = 0;
		m_mouseDelta[1] = 0;

		//	Transpose to column-wise
		SetShaderUniformBlock(CamMatrix().Transpose().m, 1);

		drawGround();
		drawForest();
		drawParthenon();
	}

	void PantheonView::drawGround()
	{
		MatrixStack mStack;

		mStack.matrix.ScaleThis(100.0f, 1.0f, 100.0f);

		SetShaderUniform(SHA_UniformColor, "modelToWorldMatrix", mStack.matrix.m);
		SetShaderUniform(SHA_UniformColor, "baseColor", 0.302f, 0.416f, 0.0589f, 1.0f);
		m_meshPlane.Render();

	}

	void PantheonView::drawForest()
	{
		MatrixStack mStack;
		for (auto i : forest)
		{
			mStack.matrix.TranslateThis(i.xPos, 0.0f, i.zPos);

			//	Draw Trunk
			mStack.Push();

			mStack.matrix.ScaleThis(1.0f, i.heightTrunk, 1.0f);
			mStack.matrix.TranslateThis(0.0f, 0.5f, 0.0f);

			SetShaderUniform(SHA_UniformColorTint, "modelToWorldMatrix", mStack.matrix.m);
			SetShaderUniform(SHA_UniformColorTint, "baseColor", 0.694f, 0.4f, 0.106f, 1.0f);
			m_meshCylinder.Render();

			mStack.Pop();

			//	Draw Trunk
			mStack.Push();

			mStack.matrix.TranslateThis(0.0f, i.heightTrunk, 0.0f);
			mStack.matrix.ScaleThis(3.0f, i.heightCone, 3.0f);

			SetShaderUniform(SHA_UniformColorTint, "modelToWorldMatrix", mStack.matrix.m);
			SetShaderUniform(SHA_UniformColorTint, "baseColor", 0.0f, 1.0f, 0.0f, 1.0f);
			m_meshCone.Render();

			mStack.Pop();
			mStack.matrix.IdentityThis();
		}
	}

	void PantheonView::drawParthenon()
	{
		MatrixStack mStack;

		mStack.matrix.TranslateThis(20.0f, 0.0f, -10.0f);	

		//	Draw base
		mStack.Push();

		mStack.matrix.ScaleThis(parthenonWidth, parthenonBaseHeight, parthenonLength);
		mStack.matrix.TranslateThis(0.0f, 0.5f, 0.0f);

		SetShaderUniform(SHA_UniformColorTint, "modelToWorldMatrix", mStack.matrix.m);
		SetShaderUniform(SHA_UniformColorTint, "baseColor", 0.9f, 0.9f, 0.9f, 0.9f);
		m_meshCube.Render();

		mStack.Pop();

		//	Draw top
		mStack.Push();

		mStack.matrix.TranslateThis(0.0f, parthenonColumnHeight + parthenonBaseHeight, 0.0f);
		mStack.matrix.ScaleThis(parthenonWidth, parthenonTopHeight, parthenonLength);
		mStack.matrix.TranslateThis(0.0f, 0.5f, 0.0f);

		SetShaderUniform(SHA_UniformColorTint, "modelToWorldMatrix", mStack.matrix.m);
		SetShaderUniform(SHA_UniformColorTint, "baseColor", 0.9f, 0.9f, 0.9f, 0.9f);
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

	void PantheonView::drawColumn(Mtx44 matrix, float height)
	{
		MatrixStack mStack;
		mStack.matrix = matrix;

		//	Draw bottom
		mStack.Push();

		mStack.matrix.ScaleThis(1.0f, columnBaseHeight, 1.0f);
		mStack.matrix.TranslateThis(0.0f, 0.5f, 0.0f);

		SetShaderUniform(SHA_UniformColorTint, "modelToWorldMatrix", mStack.matrix.m);
		SetShaderUniform(SHA_UniformColorTint, "baseColor", 0.9f, 0.9f, 0.9f, 0.9f);
		m_meshCube.Render();

		mStack.Pop();

		//	Draw top
		mStack.Push();

		mStack.matrix.TranslateThis(0.0f, height - columnBaseHeight, 0.0f);
		mStack.matrix.ScaleThis(1.0f, columnBaseHeight, 1.0f);
		mStack.matrix.TranslateThis(0.0f, 0.5f, 0.0f);

		SetShaderUniform(SHA_UniformColorTint, "modelToWorldMatrix", mStack.matrix.m);
		SetShaderUniform(SHA_UniformColorTint, "baseColor", 0.9f, 0.9f, 0.9f, 0.9f);
		m_meshCube.Render();

		mStack.Pop();

		//	Draw main column
		mStack.Push();

		mStack.matrix.TranslateThis(0.0f, columnBaseHeight, 0.0f);
		mStack.matrix.ScaleThis(0.8f, height - (columnBaseHeight * 2.0f), 0.8f);
		mStack.matrix.TranslateThis(0.0f, 0.5f, 0.0f);

		SetShaderUniform(SHA_UniformColorTint, "modelToWorldMatrix", mStack.matrix.m);
		SetShaderUniform(SHA_UniformColorTint, "baseColor", 0.9f, 0.9f, 0.9f, 0.9f);
		m_meshCylinder.Render();
	}

	void PantheonView::drawWizard()
	{
		MatrixStack mStack;

		mStack.matrix.TranslateThis(20.0f, 0.0f, -10.0f);	
		mStack.matrix.RotateThis(1.0f, 0.0f, 0.f, 20);
		SetShaderUniform(SHA_UniformColor, "modelToWorldMatrix", mStack.matrix.m);
		SetShaderUniform(SHA_UniformColor, "baseColor", 0.9f, 0.9f, 0.9f, 0.9f);
		m_wizard.Render();
	}
}