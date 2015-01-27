/*****************************************************************************************
Project      : 3D Game Engine
Author       : Sam Tian
Contributors :
******************************************************************************************/
#pragma once

#include "Shaders.h"
#include <string>
#include <vector>
#include <map>
#include <memory>

namespace Dungeons3D
{
	class ShaderManager;

	//	This is used as an interface to manipulate shader variables held in the ShaderManager class.
	class IShaderManager
	{
	public:
		IShaderManager(std::shared_ptr<ShaderManager> pManager);

		void EnableProgram(ShaderID id);
		void DisablePrograms();

		void InitUBO();
		void BindUniformBlock(ShaderID id, const std::string uniform);

		//	SETTER OVERLOADS
		//	Make 'em as you use 'em
		//----------------------------------------------------------------------------------------------------------
		//	1 float
		void SetShaderUniform(ShaderID id, const std::string uniform, float value);
		//	2 floats
		void SetShaderUniform(ShaderID id, const std::string uniform, float value1, float value2);
		//	3 floats
		void SetShaderUniform(ShaderID id, const std::string uniform, float value1, float value2, float value3);
		//	4 floats
		void SetShaderUniform(ShaderID id, const std::string uniform, float value1, float value2, float value3, float value4);
		//	4x4 Matrix
		void SetShaderUniform(ShaderID id, const std::string uniform, float * value);
		//	Uniform Block
		void SetShaderUniformBlock(float * value, unsigned index);

	private:		
		std::shared_ptr<ShaderManager> m_pManager;
	};
}