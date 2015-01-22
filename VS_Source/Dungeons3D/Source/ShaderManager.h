/*****************************************************************************************
Project      : 3D Game Engine
Author       : Sam Tian
Contributors :
******************************************************************************************/
#pragma once

#include "GLHeaders.h"
#include "Shaders.h"
#include <string>
#include <vector>
#include <map>
#include <memory>

namespace Dungeons3D
{
	class ShaderManager
	{
	public:

		ShaderManager();
		~ShaderManager();

		//	Create->Load->Link to setup a shader from a text file
		void CreateProgram(ShaderID id);
		void LoadShader(ShaderID id, const std::string fileName, GLenum shaderType);
		void LinkProgram(ShaderID id);

		GLuint GetProgram(ShaderID id);

		void Enable(ShaderID id);
		void Disable();

		void InitUBO();
		void BindUniformBlock(ShaderID id, const std::string uniform);

		//	SETTER OVERLOADS
		//	Make 'em as you use 'em
		//----------------------------------------------------------------------------------------------------------
		//	1 float
		void SetUniform(ShaderID id, const std::string uniform, float value);
		//	2 floats
		void SetUniform(ShaderID id, const std::string uniform, float value1, float value2);
		//	3 floats
		void SetUniform(ShaderID id, const std::string uniform, float value1, float value2, float value3);
		//	4 floats
		void SetUniform(ShaderID id, const std::string uniform, float value1, float value2, float value3, float value4);
		//	4x4 Matrix
		void SetUniform(ShaderID id, const std::string uniform, float * value);
		//	Uniform Block
		void SetUniformBlock(float * value, unsigned index);


	private:
		////////////////////////////////////////
		///////////PROGRAM CLASS////////////////
		////////////////////////////////////////
		class Program
		{
		public:
			friend class ShaderManager;

			Program();
			~Program();

		private:
			GLuint m_id;
			std::vector<GLuint> m_shaders;
			std::map<std::string, GLuint> m_uniforms;
		};
		////////////////////////////////////////
		////////////////////////////////////////
		////////////////////////////////////////		

		std::unique_ptr<Program> m_programs[SHA_Total];

		//	For UBOs
		GLuint m_globalUBO;
	};
}