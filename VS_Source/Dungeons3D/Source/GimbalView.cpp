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

	GimbalView::GimbalView(shared_ptr<ShaderManager> pShaderManager) : IShaderManager(pShaderManager), m_quat(1.0f, 0.0, 0.0, 0.0)
	{
		m_quat.QuaternizeThis();
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

		Resize(10.0f, 1.0f, 600.0f);
		SetShaderUniform(SHA_UniformColorLocal, "cameraToClipMatrix", ViewMatrix().m);
	}

	void GimbalView::Display()
	{
		MatrixStack mStack;

		mStack.matrix.TranslateThis(0.0f, 0.0f, -200);
		
		mStack.matrix.MultQuatThis(m_quat);
		//mStack.matrix.RotateThis(1.0f, 0.0f, 0.0f, m_x);

		//	Large Gimbal
		//drawLargeGimbal(mStack.matrix);

		//mStack.matrix.RotateThis(0.0f, 1.0f, 0.0f, m_y);

		//	Medium Gimbal
		//drawMediumGimbal(mStack.matrix);

		//mStack.matrix.RotateThis(0.0f, 0.0f, 1.0f, m_z);

		//drawSmallGimbal(mStack.matrix);

		mStack.matrix.ScaleThis(0.1f, 0.1f, 0.1f);
		//mStack.matrix.RotateThis(1.0f, 0.0f, 0.0f, 90.0f);
		mStack.matrix.TranslateThis(0.0f, -50.0f, -15.0f);

		SetShaderUniform(SHA_UniformColorLocal, "baseColor", 1.0f, 1.0f, 1.0f, 1.0f);
		SetShaderUniform(SHA_UniformColorLocal, "modelToCameraMatrix", mStack.matrix.m);
		m_katana.Render();
	}

	void GimbalView::ChangeAngle(float x, float y, float z, float deg)
	{
		Vec4 quat(x, y, z, deg);
		quat.NormalizeThis();

		//	Rotation in regards to world or object
		m_quat.MultQuatThis(quat.Quaternize());
		//m_quat = quat.Quaternize().MultQuat(m_quat);


		//	Quaternion Normalization...
		/*
		m_quat.x = m_quat.x / sqrt(m_quat.x * m_quat.x + m_quat.y * m_quat.y + m_quat.z * m_quat.z + m_quat.w * m_quat.w);
		m_quat.y = m_quat.y / sqrt(m_quat.x * m_quat.x + m_quat.y * m_quat.y + m_quat.z * m_quat.z + m_quat.w * m_quat.w);
		m_quat.z = m_quat.z / sqrt(m_quat.x * m_quat.x + m_quat.y * m_quat.y + m_quat.z * m_quat.z + m_quat.w * m_quat.w);
		m_quat.w = m_quat.w / sqrt(m_quat.x * m_quat.x + m_quat.y * m_quat.y + m_quat.z * m_quat.z + m_quat.w * m_quat.w);
		*/
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