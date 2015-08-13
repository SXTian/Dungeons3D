/*****************************************************************************************
Project      : 3D Game Engine
Author       : Sam Tian
Contributors :
******************************************************************************************/

#include "GimbalView.h"
#include "MatrixStack.h"

namespace Dungeons3D
{
	using namespace std;

	GimbalView::GimbalView(shared_ptr<Camera> pCamera, shared_ptr<ShaderManager> pManager) : CameraView(pCamera), IShaderManager(pManager)
	{
		m_quat.QuaternizeThis();
		m_currOrientation = ORI_MODEL;

		Register(MSG_KeyPress, this, [&](IEventMessage * pMsg)
		{
			switch (((MessageKeyboard*)pMsg)->key)
			{
			case 'Q': if (!m_orientation.IsAnimating()) {m_orientation.AnimateToOrient(0);} break;
			case 'W': if (!m_orientation.IsAnimating()) {m_orientation.AnimateToOrient(1);} break;
			case 'E': if (!m_orientation.IsAnimating()) {m_orientation.AnimateToOrient(2);} break;
			case 'R': if (!m_orientation.IsAnimating()) {m_orientation.AnimateToOrient(3);} break;
			case 'T': if (!m_orientation.IsAnimating()) {m_orientation.AnimateToOrient(4);} break;
			case 'Y': if (!m_orientation.IsAnimating()) {m_orientation.AnimateToOrient(5);} break;
			case 'U': if (!m_orientation.IsAnimating()) {m_orientation.AnimateToOrient(6);} break;

			case 0x20 : //	Space Key
				m_orientation.ToggleSlerp();
				break;
			}
		});
	}

	GimbalView::~GimbalView()
	{
	}

	void GimbalView::Initialize()
	{
		m_smallGimbal.Load("Resources/Meshes/SmallGimbal.mesh");
		m_mediumGimbal.Load("Resources/Meshes/MediumGimbal.mesh");
		m_largeGimbal.Load("Resources/Meshes/LargeGimbal.mesh");
		m_katana.Load("Resources/Meshes/katana.3DS");
		m_plane.Load("Resources/Meshes/UnitPlane.mesh");

		Resize(20.0f, 1.0f, 600.0f);
		SetShaderUniform(SHA_UniformColorLocal, "cameraToClipMatrix", ViewMatrix().m, 16);
	}

	void GimbalView::Display()
	{
		MatrixStack mStack;

    mStack.matrix = WCMatrix();

		//	Draw Plane
		mStack.Push();

		mStack.matrix.ScaleThis(100.0f, 1.0f, 100.0f);

		SetShaderUniform(SHA_UniformColorLocal, "baseColor", 0.2f, 0.5f, 0.2f, 1.0f);
		SetShaderUniform(SHA_UniformColorLocal, "modelToCameraMatrix", mStack.matrix.m, 16);

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
		SetShaderUniform(SHA_UniformColorLocal, "modelToCameraMatrix", mStack.matrix.m, 16);
		m_katana.Render();
	}

	void GimbalView::Display(float delta)
	{
		m_orientation.UpdateTime(delta);

		MatrixStack mStack;
		mStack.matrix.TranslateThis(0.0f, 0.0f, -200.0f);
		mStack.matrix.MultQuatThis(m_orientation.GetOrient());

		mStack.matrix.RotateThis(1.0f, 0.0f, 0.0f, 90.0f);
		mStack.matrix.RotateThis(0.0f, 1.0f, 0.0f, 90.0f);
		mStack.matrix.TranslateThis(0.0f, -50.0f, -15.0f);


		SetShaderUniform(SHA_UniformColorLocal, "baseColor", 1.0f, 1.0f, 1.0f, 1.0f);
		SetShaderUniform(SHA_UniformColorLocal, "modelToCameraMatrix", mStack.matrix.m, 16);
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
			auto viewQuat = Vec4(WCMatrix().Quaternize());
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
		SetShaderUniform(SHA_UniformColorLocal, "modelToCameraMatrix", matrix.m, 16);
		m_mediumGimbal.Render();
	}

	void GimbalView::drawMediumGimbal(Mtx44 matrix)
	{
		matrix.RotateThis(0.0f, 0.0f, 1.0f, 90.0f);
		matrix.RotateThis(1.0f, 0.0f, 0.0f, 90.0f);
		SetShaderUniform(SHA_UniformColorLocal, "baseColor", 0.0f, 1.0f, 0.0f, 1.0f);
		SetShaderUniform(SHA_UniformColorLocal, "modelToCameraMatrix", matrix.m, 16);
		m_mediumGimbal.Render();
	}

	void GimbalView::drawLargeGimbal(Mtx44 matrix)
	{
		SetShaderUniform(SHA_UniformColorLocal, "baseColor", 0.4f, 0.4f, 1.0f, 1.0f);
		SetShaderUniform(SHA_UniformColorLocal, "modelToCameraMatrix", matrix.m, 16);
		m_largeGimbal.Render();
	}
}