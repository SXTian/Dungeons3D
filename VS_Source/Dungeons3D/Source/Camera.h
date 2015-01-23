/*****************************************************************************************
  Project      : 3D Game Engine
  Author       : Sam Tian
  Contributors :
******************************************************************************************/
#pragma once

#include "Matrix.h"

namespace Dungeons3D
{
	class Camera
	{
	public:
		Camera();
		Mtx44 CamMatrix();

		void MoveCamTarget(float x, float y, float z);
		void MoveCamPosition(float x, float y, float z);

	private:
		void calculate();

		//	Position in spherical: Vec3(phi, theta, r)
		Vec3 m_pos;
		//	Camera target
		Vec3 m_target;
		//	Up vector
		Vec3 m_up;

		//	World to camera transformation
		Mtx44 m_wcMatrix;

		//	true = must call calculate()
		bool m_update;
	};
}