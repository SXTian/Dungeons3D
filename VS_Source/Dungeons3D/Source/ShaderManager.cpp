/*****************************************************************************************
Project      : 3D Game Engine
Author       : Sam Tian
Contributors :
******************************************************************************************/
#include "ShaderManager.h"
#include <iostream>
#include <fstream>

namespace Dungeons3D
{

	ShaderManager::ShaderManager()
	{
		for (unsigned i = 0; i < SHA_Total; ++i)
			_programs[i] = NULL;
	}

	ShaderManager::~ShaderManager()
	{
		for (Program* i : _programs)
		{
			if (i != NULL)
				delete i;
		}
	}
	ShaderManager::Program::Program()
	{
	}

	ShaderManager::Program::~Program()
	{
		glDeleteProgram(_id);
	}

	void ShaderManager::CreateProgram(ShaderID id)
	{
		if (_programs[id] != NULL)
			delete _programs[id];

		_programs[id] = new Program();
		_programs[id]->_id = glCreateProgram();
	}

	void ShaderManager::LoadShader(ShaderID id, const std::string fileName, GLenum shaderType)
	{
		if (_programs[id] == NULL)
			return;

		std::ifstream file;

		file.open(fileName.c_str(), std::ios_base::in);

		if (!file)
			return;

		std::string line, buffer;
		while(getline(file, line)) 
		{
			buffer.append(line);
			buffer.append("\r\n");
		}		 

		GLuint shader = glCreateShader(shaderType);

		const char * source = buffer.c_str();
		glShaderSource(shader, 1, &source, NULL);

		//	Check compile status
		GLint status;
		glCompileShader(shader);
		glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
		if (status == GL_FALSE)
		{
			GLint infoLogLength;		
			glGetShaderiv (shader, GL_INFO_LOG_LENGTH, &infoLogLength);
			GLchar *infoLog = new GLchar[infoLogLength];
			glGetShaderInfoLog (shader, infoLogLength, NULL, infoLog);
			std::cout << "Failed to compile " << fileName.c_str() << std::endl << "Compile Log:" << std::endl << infoLog << std::endl;
			delete [] infoLog;
		}
		else
		{
			std::cout << "Succesfully compiled " << fileName.c_str() << std::endl;
		}

		_programs[id]->_shaders.push_back(shader);
	}

	void ShaderManager::LinkProgram(ShaderID id)
	{
		if (_programs[id] == NULL)
			return;

		for (GLuint i : _programs[id]->_shaders)
			glAttachShader(_programs[id]->_id, i);

		//Check link status
		GLint status;
		glLinkProgram (_programs[id]->_id);
		glGetProgramiv(_programs[id]->_id, GL_LINK_STATUS, &status);

		if (status == GL_FALSE)
		{
			GLint infoLogLength;
			glGetProgramiv(_programs[id]->_id, GL_INFO_LOG_LENGTH, &infoLogLength);
			GLchar *infoLog = new GLchar[infoLogLength];
			glGetProgramInfoLog(_programs[id]->_id, infoLogLength, NULL, infoLog);
			std::cout << "Failed to link program " << id << std::endl << "Linker Log:" << std::endl << infoLog << std::endl;
			delete [] infoLog;
		}
		else
		{
			std::cout << "Succesfully Linked Program " << id << std::endl;
		}

		for (GLuint i : _programs[id]->_shaders)
		{
			glDeleteShader(i);
		}
	}

	GLuint ShaderManager::GetProgram(ShaderID id)
	{
		if (_programs[id] != NULL)
			return _programs[id]->_id;

		return 0;
	}

	void ShaderManager::Enable(ShaderID id)
	{
		if (_programs[id] != NULL)
			glUseProgram(_programs[id]->_id);
	}

	void ShaderManager::Disable()
	{
		glUseProgram(0);
	}
}