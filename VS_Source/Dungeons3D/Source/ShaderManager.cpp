/*****************************************************************************************
Project      : 3D Game Engine
Author       : Sam Tian
Contributors :
******************************************************************************************/	
#include "ShaderManager.h"
#include "GLHeaders.h"

#include <string>
#include <iostream>
#include <fstream>

#define MATRIX_SIZE sizeof(float)*16

namespace Dungeons3D
{
	using namespace std;

	Program::Program(unsigned id) : m_id(id)
	{
	}

	Program::~Program()
	{
		glDeleteProgram(m_id);
	}

	void ShaderManager::CreateProgram(ShaderID id)
	{
		m_programs[id].reset(new Program(glCreateProgram()));
	}

	void ShaderManager::LoadVertexShader(ShaderID id, const std::string fileName)
	{
		if (!m_programs[id])
			return;

		std::ifstream file;

		file.open(fileName.c_str(), std::ios_base::in);

		if (!file)
			return;

		string line, buffer;
		while(getline(file, line)) 
		{
			buffer.append(line);
			buffer.append("\r\n");
		}		 

		GLuint shader = glCreateShader(GL_VERTEX_SHADER);

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

		m_programs[id]->m_shaders.push_back(shader);
	}

	void ShaderManager::LoadFragmentShader(ShaderID id, const std::string fileName)
	{
		if (!m_programs[id])
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

		GLuint shader = glCreateShader(GL_FRAGMENT_SHADER);

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

		m_programs[id]->m_shaders.push_back(shader);
	}

	void ShaderManager::LinkProgram(ShaderID id)
	{
		if (!m_programs[id])
			return;

		for (GLuint i : m_programs[id]->m_shaders)
			glAttachShader(m_programs[id]->m_id, i);

		//Check link status
		GLint status;
		glLinkProgram (m_programs[id]->m_id);
		glGetProgramiv(m_programs[id]->m_id, GL_LINK_STATUS, &status);

		if (status == GL_FALSE)
		{
			GLint infoLogLength;
			glGetProgramiv(m_programs[id]->m_id, GL_INFO_LOG_LENGTH, &infoLogLength);
			GLchar *infoLog = new GLchar[infoLogLength];
			glGetProgramInfoLog(m_programs[id]->m_id, infoLogLength, NULL, infoLog);
			std::cout << "Failed to link program " << id << std::endl << "Linker Log:" << std::endl << infoLog << std::endl;
			delete [] infoLog;
		}
		else
		{
			std::cout << "Succesfully Linked Program " << id << std::endl;
		}

		for (GLuint i : m_programs[id]->m_shaders)
		{
			glDeleteShader(i);
		}
	}

	void ShaderManager::InitUBO()
	{
		glGenBuffers(1, &m_globalUBO);
		glBindBuffer(GL_UNIFORM_BUFFER, m_globalUBO);
		glBufferData(GL_UNIFORM_BUFFER, MATRIX_SIZE * 2, NULL, GL_STREAM_DRAW);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);

		glBindBufferRange(GL_UNIFORM_BUFFER, 0, m_globalUBO, 0, MATRIX_SIZE * 2);
	}

	void ShaderManager::BindUniformBlock(ShaderID id, const std::string uniform)
	{
		if (!m_programs[id]->m_uniforms.count(uniform))
		{
			m_programs[id]->m_uniforms[uniform] = glGetUniformBlockIndex(m_programs[id]->m_id, uniform.c_str());
			glUniformBlockBinding(m_programs[id]->m_id, m_programs[id]->m_uniforms[uniform], 0);
		}
	}

		unsigned ShaderManager::GetProgram(ShaderID id)
	{
		if (!m_programs[id])
			CreateProgram(id);

		return m_programs[id]->m_id;
	}

	unsigned ShaderManager::GetUniform(ShaderID id, string uniform)
	{
		if (!m_programs[id])
			CreateProgram(id);

		if (!m_programs[id]->m_uniforms.count(uniform))
			m_programs[id]->m_uniforms[uniform] = glGetUniformLocation(m_programs[id]->m_id, uniform.c_str());

		return m_programs[id]->m_uniforms[uniform];
	}

	unsigned ShaderManager::GetUBO()
	{
		return m_globalUBO;
	}
}