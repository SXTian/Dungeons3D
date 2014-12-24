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
		Mtx44 Matrix();

	private:
		void calculate();

		//	Position in spherical: Vec3(phi, theta, r)
		Vec3 _pos;
		//	Camera target
		Vec3 _target;
		//	Up vector
		Vec3 _up;

		//	World to camera transformation
		Mtx44 _wcMatrix;
		//	true = must call calculate()
		bool _update;

	};
}