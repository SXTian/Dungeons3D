/*****************************************************************************************
Project      : 3D Game Engine
Author       : Sam Tian
Contributors :
******************************************************************************************/

#include "GimbalView.h"
#include "ShaderManager.h"
#include "MatrixStack.h"
#include "Math.h"

namespace Dungeons3D
{
	using namespace std;

	GimbalView::GimbalView(shared_ptr<ShaderManager> pShaderManager) : IShaderManager(pShaderManager), m_quat(1.0f, 0.0, 0.0, 0.0), Camera(Vec4(90.0f, 0.0f, 66.0f), Vec4(0.0f, 20.0f, 0.0f), Vec4(0.0f, 1.0f, 0.0f))
	{
		m_quat.QuaternizeThis();
		m_currOrientation = ORI_MODEL;

		Register(MSG_KeyPress, this, [&](IEventMessage * pMsg)
		{
			switch (((MessageKeyboard*)pMsg)->key)
			{
			case 'W': ChangeAngle(1.0f, 0.0f, 0.0f, 9.0f); break;
			case 'S': ChangeAngle(-1.0f, 0.0f, 0.0f, 9.0f); break;
			case 'D': ChangeAngle(0.0f, 1.0f, 0.0f, 9.0f); break;
			case 'A': ChangeAngle(0.0f, -1.0f, 0.0f, 9.0f); break;
			case 'E': ChangeAngle(0.0f, 0.0f, 1.0f, 9.0f); break;
			case 'Q': ChangeAngle(0.0f, 0.0f, -1.0f, 9.0f); break;

			case 0x20 : //	Space Key
				switch (m_currOrientation)
				{
				case ORI_MODEL: m_currOrientation = ORI_WORLD; break;
				case ORI_WORLD: m_currOrientation = ORI_CAMERA; break;
				case ORI_CAMERA: m_currOrientation = ORI_MODEL; break;
				}
				break;
			}
		});
	}

	GimbalView::~GimbalView()
	{
	}

	void GimbalView::LoadMeshes()
	{
		m_smallGimbal.Load("Resources/Meshes/SmallGimbal.mesh");
		m_mediumGimbal.Load("Resources/Meshes/MediumGimbal.mesh");
		m_largeGimbal.Load("Resources/Meshes/LargeGimbal.mesh");
		m_katana.Load("Resources/Meshes/katana.3DS");
		m_plane.Load("Resources/Meshes/UnitPlane.mesh");

		Resize(20.0f, 1.0f, 600.0f);
		SetShaderUniform(SHA_UniformColorLocal, "cameraToClipMatrix", ViewMatrix().m);
	}

	void GimbalView::Display()
	{
		MatrixStack mStack;

		mStack.matrix = CamMatrix();

		//	Draw Plane
		mStack.Push();

		mStack.matrix.ScaleThis(100.0f, 1.0f, 100.0f);

		SetShaderUniform(SHA_UniformColorLocal, "baseColor", 0.2f, 0.5f, 0.2f, 1.0f);
		SetShaderUniform(SHA_UniformColorLocal, "modelToCameraMatrix", mStack.matrix.m);

		m_plane.Render();
		mStack.Pop();

		//	Draw Object

		mStack.Push();
		mStack.matrix.TranslateThis(0.0f, 15.0f, 0.0f);
		mStack.matrix.MultQuatThis(m_quat);
		mStack.matrix.ScaleThis(0.15f, 0.15f, 0.15f);
		mStack.matrix.RotateThis(1.0f, 0.0f, 0.0f, 90.0f);
		mStack.matrix.RotateThis(0.0f, 1.0f, 0.0f, 90.0f);
		mStack.matrix.TranslateThis(0.0f, -50.0f, -15.0f);


		SetShaderUniform(SHA_UniformColorLocal, "baseColor", 1.0f, 1.0f, 1.0f, 1.0f);
		SetShaderUniform(SHA_UniformColorLocal, "modelToCameraMatrix", mStack.matrix.m);
		m_katana.Render();
	}

	void GimbalView::ChangeAngle(float x, float y, float z, float deg)
	{
		Vec4 quat(x, y, z, deg);
		quat.NormalizeThis();

		switch (m_currOrientation)
		{
		case ORI_MODEL: 
			m_quat.MultQuatThis(quat.Quaternize()); 
			break;
		case ORI_WORLD: 
			m_quat = quat.Quaternize().MultQuat(m_quat); 
			break;
		case ORI_CAMERA:
			auto viewQuat = Vec4(CamMatrix().Quaternize());
			auto worldQuat = Vec4(viewQuat.Conjugate().MultQuat(quat.Quaternize()).MultQuat(viewQuat));
			m_quat = worldQuat.MultQuat(m_quat);
		}

		m_quat.NormalizeQuaternionThis();
	}

	void GimbalView::drawSmallGimbal(Mtx44 matrix)
	{
		matrix.RotateThis(0.0f, 1.0f, 0.0f, 90.0f);
		matrix.RotateThis(1.0f, 0.0f, 0.0f, 90.0f);
		SetShaderUniform(SHA_UniformColorLocal, "baseColor", 1.0f, 0.3f, 0.3f, 1.0f);
		SetShaderUniform(SHA_UniformColorLocal, "modelToCameraMatrix", matrix.m);
		m_mediumGimbal.Render();
	}

	void GimbalView::drawMediumGimbal(Mtx44 matrix)
	{
		matrix.RotateThis(0.0f, 0.0f, 1.0f, 90.0f);
		matrix.RotateThis(1.0f, 0.0f, 0.0f, 90.0f);
		SetShaderUniform(SHA_UniformColorLocal, "baseColor", 0.0f, 1.0f, 0.0f, 1.0f);
		SetShaderUniform(SHA_UniformColorLocal, "modelToCameraMatrix", matrix.m);
		m_mediumGimbal.Render();
	}

	void GimbalView::drawLargeGimbal(Mtx44 matrix)
	{
		SetShaderUniform(SHA_UniformColorLocal, "baseColor", 0.4f, 0.4f, 1.0f, 1.0f);
		SetShaderUniform(SHA_UniformColorLocal, "modelToCameraMatrix", matrix.m);
		m_largeGimbal.Render();
	}
}