/*****************************************************************************************
Project      : 3D Game Engine
Author       : Sam Tian
Contributors :
******************************************************************************************/
#include "Orientation.h"

namespace Dungeons3D
{

	static Vec4 s_orients[] =
	{
		Vec4(0.7071f, 0.0f, 0.0f, 0.7071f),
		Vec4(0.5f, -0.5f, 0.5f, 0.5f),
		Vec4(-0.7892f, -0.3700f, -0.02514f, -0.4895f),
		Vec4(0.7892f, 0.3700f, 0.02514f, 0.4895f),

		Vec4(-0.1591f, -0.7991f, -0.4344f, 0.3840f),
		Vec4(0.5208f, 0.6483f, 0.0410f, 0.5537f),
		Vec4(0.0f, 1.0f, 0.0f, 0.0f)
	};

	Orientation::Orientation() : m_isAnimating(false), m_currOrient(0), m_slerp(false)
	{
		for (auto &i : s_orients)
			i.QuaternizeThis();
	}

	bool Orientation::ToggleSlerp()
	{
		m_slerp = !m_slerp;
		return m_slerp;
	}

	Vec4 Orientation::GetOrient()
	{
		if(m_isAnimating)
			return m_anim.GetOrient(s_orients[m_currOrient], m_slerp);
		else
			return s_orients[m_currOrient];
	}

	bool Orientation::IsAnimating()
	{
		return m_isAnimating;
	}

	void Orientation::UpdateTime(float delta)
	{
		if(m_isAnimating)
		{
			bool isFinished = m_anim.UpdateTime(delta);
			if(isFinished)
			{
				m_isAnimating = false;
				m_currOrient = m_anim.GetFinal();
			}
		}
	}

	void Orientation::AnimateToOrient(int destination)
	{
		if(m_currOrient == destination)
			return;

		m_anim.StartAnimation(destination, 1.0f);
		m_isAnimating = true;
	}

	bool Orientation::Animation::UpdateTime(float delta)
	{
		m_currTime += delta;

		if (m_currTime > m_duration)
			return true;
		else
			return false;

	}
	Vec4 Orientation::Animation::GetOrient(const Vec4 &initial, bool isSlerp)
	{
		if (isSlerp)
		{
			return slerp(initial, s_orients[m_finalOrient], Clamp(m_currTime / m_duration, 0.0f, 1.0f));
		}
		else
		{
			Vec4 result = Mix(initial, s_orients[m_finalOrient], Clamp(m_currTime / m_duration, 0.0f, 1.0f));
			return result.NormalizeQuaternion();
		}

		return initial;
	}

	void Orientation::Animation::StartAnimation(int destination, float duration)
	{
		m_finalOrient = destination;
		m_duration = duration;
		m_currTime = 0.0f;
	}

	int Orientation::Animation::GetFinal() const 
	{ 
		return m_finalOrient; 
	}

	Vec4 Orientation::Animation::slerp(const Vec4 &v0, const Vec4 &v1, float alpha)
	{
		float dot = v0 * v1;

		const float DOT_THRESHOLD = 0.9995f;

		if (dot > DOT_THRESHOLD)
			return Mix(v0, v1, alpha);

		Clamp(dot, -1.0f, 1.0f);
		float theta = acosf(dot) * alpha;

		Vec4 v2 = v1 - (v0 * dot);
		v2.NormalizeQuaternionThis();

		return v0 * cos(theta) + v2 * sin(theta);
	}
}