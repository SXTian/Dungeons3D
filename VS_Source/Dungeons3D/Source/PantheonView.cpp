/*****************************************************************************************
Project      : 3D Game Engine
Author       : Sam Tian
Contributors :
******************************************************************************************/
#include "PantheonView.h"
#include "Camera.h"
#include "MatrixStack.h"
#include "EventMessages.h"
#include "WindowSize.h"
#include "OpenGL.h"

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

	PantheonView::PantheonView(shared_ptr<Camera> pCamera, shared_ptr<ShaderManager> pManager) : CameraView(pCamera), IShaderManager(pManager)
	{
    m_mousePosition.x = 0;
    m_mousePosition.y = 0;

    lightAngleX = 90.0f;
    lightAngleZ = 90.0f;

		Register(MSG_MouseMove, this, [&](IEventMessage * pMsg)
		{
      int x = ((MessageMouseMove*)pMsg)->x;
      int y = ((MessageMouseMove*)pMsg)->y;
      GetCamera().RotateCamY(Clamp(-(float)(x - m_mousePosition.x), -7.5f, 7.5f));
      GetCamera().RotateCamX(Clamp((float)(y - m_mousePosition.y), -7.5f, 7.5f));
      m_mousePosition.x = x;
      m_mousePosition.y = y;
		});

		Register(MSG_MouseWheel, this, [&](IEventMessage * pMsg)
		{
			GetCamera().ZoomCam(-((MessageMouseWheel*)pMsg)->wheel / 10.0f);
		});

		
		Register(MSG_KeyPress, this, [&](IEventMessage * pMsg)
		{
			switch (((MessageKeyboard*)pMsg)->key)
			{
			case 'W': lightAngleZ = Wrap(lightAngleZ + 5.0f, -180.0f, 180.0f); break;
			case 'S': lightAngleZ = Wrap(lightAngleZ - 5.0f, -180.0f, 180.0f); break;
      case 'A': lightAngleX = Wrap(lightAngleX + 5.0f, -180.0f, 180.0f); break;
      case 'D': lightAngleX = Wrap(lightAngleX - 5.0f, -180.0f, 180.0f); break;
			}
		});
	}

	PantheonView::~PantheonView()
	{
	}

	void PantheonView::Initialize()
	{
		m_meshCube.Load("Resources/Meshes/UnitCube.mesh");
		m_meshCubeColor.Load("Resources/Meshes/UnitCubeColor.mesh");
		m_meshPlane.Load("Resources/Meshes/UnitPlane.mesh");
    m_meshTreetrunk.Load("Resources/Meshes/Treetrunk.mesh");
		m_meshTreetop.Load("Resources/Meshes/Treetop.mesh");
		m_meshCylinder.Load("Resources/Meshes/UnitCylinder.mesh");
		m_wizard.Load("Resources/Meshes/wizard.3DS");

    SetShaderUniform(SHA_AmbientLighting, "cameraToClipMatrix", ViewMatrix().m, 16);
	}

	void PantheonView::Display()
	{
		//	Transpose to column-wise
		SetShaderUniformBlock(WCMatrix().Transpose().m, 1);

		drawGround();
		drawForest();
		drawParthenon();
	}

	void PantheonView::Display(float delta)
	{
    SetShaderUniform(SHA_AmbientLighting, "lightDirection", CosLookup(lightAngleX), Min(SinLookup(lightAngleX), SinLookup(lightAngleZ)), CosLookup(lightAngleZ));
    SetShaderUniform(SHA_AmbientLighting, "lightIntensity", 0.9f, 0.9f, 0.9f, 1.0f);
    SetShaderUniform(SHA_AmbientLighting, "ambientIntensity", 0.1f, 0.1f, 0.1f, 1.0f);

    SetShaderUniform(SHA_AmbientLighting, "worldToCameraMatrix", WCMatrix().m, 16);

		drawGround();
		drawForest();
		drawParthenon();

    checkMousePos();
	}

	void PantheonView::drawGround()
	{
		MatrixStack mStack;

    mStack.matrix.ScaleThis(100.0f, 1.0f, 100.0f);

    SetShaderUniform(SHA_AmbientLighting, "modelToCameraMatrix", MCMatrix(mStack.matrix).m, 16);
    SetShaderUniform(SHA_AmbientLighting, "normalModelToCameraMatrix", MCMatrix().Slice().m, 9);
		m_meshPlane.Render();

	}

	void PantheonView::drawForest()
	{
		MatrixStack mStack;
    Mtx44 mcMatrix;

		for (auto i : forest)
		{
			mStack.matrix.TranslateThis(i.xPos, 0.0f, i.zPos);

			//	Draw Trunk
			mStack.Push();

			mStack.matrix.ScaleThis(1.0f, i.heightTrunk, 1.0f);
			mStack.matrix.TranslateThis(0.0f, 0.5f, 0.0f);

      SetShaderUniform(SHA_AmbientLighting, "modelToCameraMatrix", MCMatrix(mStack.matrix).m, 16);
      SetShaderUniform(SHA_AmbientLighting, "normalModelToCameraMatrix", MCMatrix().Slice().m, 9);
			m_meshTreetrunk.Render();

			mStack.Pop();

			//	Draw Treetop
			mStack.Push();

			mStack.matrix.TranslateThis(0.0f, i.heightTrunk * 1.5f , 0.0f);
			mStack.matrix.ScaleThis(3.0f, i.heightCone, 3.0f);

      SetShaderUniform(SHA_AmbientLighting, "modelToCameraMatrix", MCMatrix(mStack.matrix).m, 16);
      SetShaderUniform(SHA_AmbientLighting, "normalModelToCameraMatrix", MCMatrix().Slice().m, 9);
			m_meshTreetop.Render();

			mStack.Pop();
			mStack.matrix.IdentityThis();
		}
	}

	void PantheonView::drawParthenon()
	{
		MatrixStack mStack;
    Mtx44 mcMatrix;

		mStack.matrix.TranslateThis(20.0f, 0.0f, -10.0f);	

		//	Draw base
		mStack.Push();

		mStack.matrix.ScaleThis(parthenonWidth, parthenonBaseHeight, parthenonLength);
		mStack.matrix.TranslateThis(0.0f, 0.5f, 0.0f);

    SetShaderUniform(SHA_AmbientLighting, "modelToCameraMatrix", MCMatrix(mStack.matrix).m, 16);
    SetShaderUniform(SHA_AmbientLighting, "normalModelToCameraMatrix", MCMatrix().Slice().m, 9);
		m_meshCube.Render();

		mStack.Pop();

		//	Draw top
		mStack.Push();

		mStack.matrix.TranslateThis(0.0f, parthenonColumnHeight + parthenonBaseHeight, 0.0f);
		mStack.matrix.ScaleThis(parthenonWidth, parthenonTopHeight, parthenonLength);
		mStack.matrix.TranslateThis(0.0f, 0.5f, 0.0f);

    SetShaderUniform(SHA_AmbientLighting, "modelToCameraMatrix", MCMatrix(mStack.matrix).m, 16);
    SetShaderUniform(SHA_AmbientLighting, "normalModelToCameraMatrix", MCMatrix().Slice().m, 9);
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
    Mtx44 mcMatrix;

		mStack.matrix = matrix;

		//	Draw bottom
		mStack.Push();

		mStack.matrix.ScaleThis(1.0f, columnBaseHeight, 1.0f);
		mStack.matrix.TranslateThis(0.0f, 0.5f, 0.0f);

    SetShaderUniform(SHA_AmbientLighting, "modelToCameraMatrix", MCMatrix(mStack.matrix).m, 16);
    SetShaderUniform(SHA_AmbientLighting, "normalModelToCameraMatrix", MCMatrix().Slice().m, 9);
		m_meshCube.Render();

		mStack.Pop();

		//	Draw top
		mStack.Push();

		mStack.matrix.TranslateThis(0.0f, height - columnBaseHeight, 0.0f);
		mStack.matrix.ScaleThis(1.0f, columnBaseHeight, 1.0f);
		mStack.matrix.TranslateThis(0.0f, 0.5f, 0.0f);

    SetShaderUniform(SHA_AmbientLighting, "modelToCameraMatrix", MCMatrix(mStack.matrix).m, 16);
    SetShaderUniform(SHA_AmbientLighting, "normalModelToCameraMatrix", MCMatrix().Slice().m, 9);
		m_meshCube.Render();

		mStack.Pop();

		//	Draw main column
		mStack.Push();

		mStack.matrix.TranslateThis(0.0f, columnBaseHeight, 0.0f);
		mStack.matrix.ScaleThis(0.8f, height - (columnBaseHeight * 2.0f), 0.8f);
		mStack.matrix.TranslateThis(0.0f, 0.5f, 0.0f);

    SetShaderUniform(SHA_AmbientLighting, "modelToCameraMatrix", MCMatrix(mStack.matrix).m, 16);
    SetShaderUniform(SHA_AmbientLighting, "normalModelToCameraMatrix", MCMatrix().Slice().m, 9);
		m_meshCylinder.Render();
	}

  void PantheonView::checkMousePos()
  {
    if (m_mousePosition.x <= 0 || m_mousePosition.x >= WINDOW_MAX_X - 1 || m_mousePosition.y <= 0 || m_mousePosition.y >= WINDOW_MAX_Y - 1)
    {
      int centerX = WINDOW_MAX_X / 2;
      int centerY = WINDOW_MAX_Y / 2;
      m_mousePosition.x = centerX;
      m_mousePosition.y = centerY;
      SetCursorPos(centerX, centerY);
    }
  }
}