/*****************************************************************************************
Project      : 3D Game Engine
Author       : Sam Tian
Contributors :
******************************************************************************************/
#pragma once

#include "Shaders.h"

#include <vector>
#include <map>
#include <memory>

namespace Dungeons3D
{
	struct Program
	{
		Program(unsigned id);
		~Program();

		unsigned m_id;
		std::vector<unsigned> m_shaders;
		std::map<std::string, unsigned> m_uniforms;
	};

	class ShaderManager
	{
	public:
		//	Create->Load->Link to setup a shader from a text file
		void CreateProgram(ShaderID id);
		void LoadVertexShader(ShaderID id, const std::string fileName);
		void LoadFragmentShader(ShaderID id, const std::string fileName);
		void LinkProgram(ShaderID id);

		void InitUBO();
		void BindUniformBlock(ShaderID id, const std::string uniform);

		unsigned GetProgram(ShaderID id);
		unsigned GetUniform(ShaderID id, std::string uniform);
		unsigned GetUBO();

	private:
		std::unique_ptr<Program> m_programs[SHA_Total];
		unsigned m_globalUBO;
	};
}