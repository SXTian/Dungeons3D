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
		Camera(float distMin, float distMax);

		Mtx44 CamMatrix();

		void ZoomCam(float dist);
		void RotateCamX(float deg);
		void RotateCamY(float deg);

	private:
		void updatePosition();
		void constructMatrix();

		//	World to camera transformation
		Mtx44 m_wcMatrix;

		Vec4 m_position;
		Vec4 m_target;
		Vec4 m_up;

		float m_distance;
		float m_min;
		float m_max;

		float m_rotateX;
		float m_rotateY;

		//	true = must call calculate()
		bool m_update;
	};
}