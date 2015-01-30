/*****************************************************************************************
Project      : 3D Game Engine
Author       : Sam Tian
Contributors :
******************************************************************************************/
#pragma once

#include "Vector.h"
#include "Math.h"

static Vec4 s_orients[] =
{
	Vec4(0.7071f, 0.0f, 0.0f, 0.7071f).Quaternize(),
	Vec4(0.5f, -0.5f, 0.5f, 0.5f).Quaternize(),
	Vec4(-0.7892f, -0.3700f, -0.02514f, -0.4895f).Quaternize(),
	Vec4(0.7892f, 0.3700f, 0.02514f, 0.4895f).Quaternize(),

	Vec4(-0.1591f, -0.7991f, -0.4344f, 0.3840f).Quaternize(),
	Vec4(0.5208f, 0.6483f, 0.0410f, 0.5537f).Quaternize(),
	Vec4(0.0f, 1.0f, 0.0f, 0.0f).Quaternize()
};

class Orientation
{
public:
	Orientation() : m_isAnimating(false), m_currOrient(0), m_slerp(false) {}

	bool ToggleSlerp()
	{
		m_slerp = !m_slerp;
		return m_slerp;
	}

	Vec4 GetOrient() const
	{
		if(m_isAnimating)
			return m_anim.GetOrient(s_orients[m_currOrient], m_slerp);
		else
			return s_orients[m_currOrient];
	}

	bool IsAnimating() const {return m_isAnimating;}

	void UpdateTime()
	{
		if(m_isAnimating)
		{
			bool isFinished = m_anim.UpdateTime();
			if(isFinished)
			{
				m_isAnimating = false;
				m_currOrient = m_anim.GetFinal();
			}
		}
	}

	void AnimateToOrient(int destination)
	{
		if(m_currOrient == destination)
			return;

		m_anim.StartAnimation(destination, 1.0f);
		m_isAnimating = true;
	}

private:
	class Animation
	{
	public:
		//Returns true if the animation is over.
		bool UpdateTime()
		{
			return m_currTimer.Update();
		}

		Vec4 GetOrient(const Vec4 &initial, bool slerp) const
		{
			if(slerp)
			{
				return Slerp(initial, s_orients[m_finalOrient], m_currTimer.GetAlpha());
			}
			else
			{
				Vec4 result = Mix(initial, s_orients[m_finalOrient], m_currTimer.GetAlpha());
				return result.NormalizeQuaternion();
			}

			return initial;
		}

		void StartAnimation(int destination, float duration)
		{
			m_finalOrient = destination;
			m_currTimer = Framework::Timer(Framework::Timer::TT_SINGLE, duration);
		}

		int GetFinal() const { return m_finalOrient; }

	private:
		int m_finalOrient;
		Framework::Timer m_currTimer;
	};

	bool m_isAnimating;
	int m_currOrient;
	bool m_slerp;

	Animation m_anim;
};

Orientation s_orient;

class Animation
{
public:

private:
	Vec4 m_finalOrient;
};


glm::fquat Slerp(const glm::fquat &v0, const glm::fquat &v1, float alpha)
{
	float dot = glm::dot(v0, v1);

	const float DOT_THRESHOLD = 0.9995f;
	if (dot > DOT_THRESHOLD)
		return Lerp(v0, v1, alpha);

	glm::clamp(dot, -1.0f, 1.0f);
	float theta_0 = acosf(dot);
	float theta = theta_0*alpha;

	glm::fquat v2 = v1 + -(v0*dot);
	v2 = glm::normalize(v2);

	return v0*cos(theta) + v2*sin(theta);
}