/*****************************************************************************************
Project      : 3D Game Engine
Author       : Sam Tian
Contributors :
******************************************************************************************/
#pragma once

#include "IView.h"
#include "IShaderManager.h"
#include "Mesh.h"
#include "Loader.h"
#include "Loader3DS.h"

namespace Dungeons3D
{
	class ShaderManager;

	class GimbalView : public IView, public IShaderManager
	{
	public: 
		GimbalView(std::shared_ptr<ShaderManager> pManager);
		~GimbalView();

		void LoadMeshes();
		void Display();

		void ChangeAngle(float x, float y, float z, float deg);

	private:
		void drawSmallGimbal(Mtx44 matrix);
		void drawMediumGimbal(Mtx44 matrix);
		void drawLargeGimbal(Mtx44 matrix);

		Mesh<Loader> m_smallGimbal;
		Mesh<Loader> m_mediumGimbal;
		Mesh<Loader> m_largeGimbal;

		Mesh<Loader3DS> m_katana;

		Vec4 m_quat;
	};
}