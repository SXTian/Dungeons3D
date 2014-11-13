/*****************************************************************************************
Project      : 3D Game Engine
Author       : Sam Tian
Contributors :
******************************************************************************************/
#pragma once

#include "GLHeaders.h"
#include <string>
#include <vector>
#include <map>

namespace Dungeons3D
{
	//	List of all shaders
	enum ShaderID
	{
		SHA_Default,
		SHA_Total
	};

	class ShaderManager
	{
	public:
		ShaderManager();
		~ShaderManager();

		//	Create->Load->Link to setup a shader from a text file
		void CreateProgram(ShaderID id);
		void LoadShader(ShaderID id, const std::string fileName, GLenum shaderType);
		void LinkProgram(ShaderID id);

		//	Add shader vars
		void AddAttribute(ShaderID id, const std::string attribute);
		void AddUniform(ShaderID id, const std::string uniform);

		//	Get shader vars
		GLuint GetAttribute(ShaderID id, const std::string attribute);
		GLuint GetUniform(ShaderID id, const std::string uniform);

		GLuint GetProgram(ShaderID id);

		void Enable(ShaderID id);
		void Disable();

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
			std::map<std::string, GLuint> _attributes;
			std::map<std::string, GLuint> _uniforms;
		};
		////////////////////////////////////////
		////////////////////////////////////////
		////////////////////////////////////////		

		Program * _programs[SHA_Total];
	};
}