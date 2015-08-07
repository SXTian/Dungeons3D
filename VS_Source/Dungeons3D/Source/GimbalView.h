/*****************************************************************************************
Project      : 3D Game Engine
Author       : Sam Tian
Contributors :
******************************************************************************************/
#pragma once

#include "BaseView.h"
#include "Camera.h"
#include "IShaderManager.h"
#include "MessageKeyboard.h"
#include "Mesh.h"
#include "Loader.h"
#include "Loader3DS.h"
#include "Orientation.h"


namespace Dungeons3D
{
	enum OrientationType
	{
		ORI_MODEL,
		ORI_WORLD,
		ORI_CAMERA,
		ORI_TOTAL
	};

	class ShaderManager;

	class GimbalView : public BaseView, public Camera, public IShaderManager, public IEventMessageModule
	{
	public: 
		GimbalView(std::shared_ptr<ShaderManager> pManager);
		~GimbalView();

		void Initialize();
		void Display();
		void Display(float delta);

		void ChangeAngle(float x, float y, float z, float deg);

	private:
		void drawSmallGimbal(Mtx44 matrix);
		void drawMediumGimbal(Mtx44 matrix);
		void drawLargeGimbal(Mtx44 matrix);

		Mesh<Loader> m_smallGimbal;
		Mesh<Loader> m_mediumGimbal;
		Mesh<Loader> m_largeGimbal;

		Mesh<Loader3DS> m_katana;
		Mesh<Loader> m_plane;

		Vec4 m_quat;
		OrientationType m_currOrientation;

		Orientation m_orientation;
	};

}