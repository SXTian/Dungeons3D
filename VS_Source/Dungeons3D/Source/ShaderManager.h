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

#define GetLocationUseProgram(id, uniform)	if (!_programs[id]->_uniforms.count(uniform))\
												_programs[id]->_uniforms[uniform] = glGetUniformLocation(_programs[id]->_id, uniform.c_str());\
											glUseProgram(_programs[id]->_id);

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

		//	SETTER OVERLOADS
		//	Make 'em as you use 'em
		//----------------------------------------------------------------------------------------------------------
		//	1 float
		void SetUniform(ShaderID id, const std::string uniform, float value)
		{
			GetLocationUseProgram(id, uniform)
			glUniform1f(_programs[id]->_uniforms[uniform], value);
		}
		//	2 floats
		void SetUniform(ShaderID id, const std::string uniform, float value1, float value2)
		{
			GetLocationUseProgram(id, uniform)
			glUniform2f(_programs[id]->_uniforms[uniform], value1, value2);
		}
		//	3 floats
		void SetUniform(ShaderID id, const std::string uniform, float value1, float value2, float value3)
		{
			GetLocationUseProgram(id, uniform)
			glUniform3f(_programs[id]->_uniforms[uniform], value1, value2, value3);
		}

		//	4 floats
		void SetUniform(ShaderID id, const std::string uniform, float value1, float value2, float value3, float value4)
		{
			GetLocationUseProgram(id, uniform)
			glUniform4f(_programs[id]->_uniforms[uniform], value1, value2, value3, value4);
		}

		//	4x4 Matrix
		void SetUniform(ShaderID id, const std::string uniform, float * value)
		{
			GetLocationUseProgram(id, uniform)
			glUniformMatrix4fv(_programs[id]->_uniforms[uniform], 1, GL_TRUE, value);
		}


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
			GLuint _id;
			std::vector<GLuint> _shaders;
			std::map<std::string, GLuint> _uniforms;
		};
		////////////////////////////////////////
		////////////////////////////////////////
		////////////////////////////////////////		

		Program * _programs[SHA_Total];
	};
}