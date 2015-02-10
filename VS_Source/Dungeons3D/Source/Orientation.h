/*****************************************************************************************
Project      : 3D Game Engine
Author       : Sam Tian
Contributors :
******************************************************************************************/
#pragma once

#include "Vector.h"
#include "Math.h"

namespace Dungeons3D
{
	class Orientation
	{
	public:
		Orientation();
		bool ToggleSlerp();
		Vec4 GetOrient();
		bool IsAnimating();
		void UpdateTime(float delta);
		void AnimateToOrient(int destination);

	private:
		class Animation
		{
		public:
			//  Returns true if the animation is over.
			bool UpdateTime(float delta);
			Vec4 GetOrient(const Vec4 &initial, bool isSlerp);
			void StartAnimation(int destination, float duration);
			int GetFinal() const;

		private:
			Vec4 slerp(const Vec4 &v0, const Vec4 &v1, float alpha);

			int m_finalOrient;

			float m_currTime;
			float m_duration;
		};

		bool m_isAnimating;
		int m_currOrient;
		bool m_slerp;

		Animation m_anim;
	};
}