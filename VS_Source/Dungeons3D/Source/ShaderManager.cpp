/*****************************************************************************************
Project      : 3D Game Engine
Author       : Sam Tian
Contributors :
******************************************************************************************/
#include "ShaderManager.h"
#include <iostream>
#include <fstream>

#define MATRIX_SIZE sizeof(float)*16

namespace Dungeons3D
{
	ShaderManager::ShaderManager()
	{
	}

	ShaderManager::~ShaderManager()
	{
	}

	ShaderManager::Program::Program()
	{
	}

	ShaderManager::Program::~Program()
	{
		glDeleteProgram(m_id);
	}

	void ShaderManager::CreateProgram(ShaderID id)
	{
		m_programs[id].reset(new Program());
		m_programs[id]->m_id = glCreateProgram();
	}

	void ShaderManager::LoadShader(ShaderID id, const std::string fileName, GLenum shaderType)
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

	GLuint ShaderManager::GetProgram(ShaderID id)
	{
		if (m_programs[id])
			return m_programs[id]->m_id;

		return 0;
	}

	void ShaderManager::Enable(ShaderID id)
	{
		if (m_programs[id])
			glUseProgram(m_programs[id]->m_id);
	}

	void ShaderManager::Disable()
	{
		glUseProgram(0);
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

	//	SETTER OVERLOADS
	//----------------------------------------------------------------------------------------------------------
	//	1 float
	void ShaderManager::SetUniform(ShaderID id, const std::string uniform, float value)
	{
		GetLocationUseProgram(id, uniform);
		glUniform1f(m_programs[id]->m_uniforms[uniform], value);
	}
	//	2 floats
	void ShaderManager::SetUniform(ShaderID id, const std::string uniform, float value1, float value2)
	{
		GetLocationUseProgram(id, uniform);
		glUniform2f(m_programs[id]->m_uniforms[uniform], value1, value2);
	}
	//	3 floats
	void ShaderManager::SetUniform(ShaderID id, const std::string uniform, float value1, float value2, float value3)
	{
		GetLocationUseProgram(id, uniform);
		glUniform3f(m_programs[id]->m_uniforms[uniform], value1, value2, value3);
	}

	//	4 floats
	void ShaderManager::SetUniform(ShaderID id, const std::string uniform, float value1, float value2, float value3, float value4)
	{
		GetLocationUseProgram(id, uniform);
		glUniform4f(m_programs[id]->m_uniforms[uniform], value1, value2, value3, value4);
	}

	//	4x4 Matrix
	void ShaderManager::SetUniform(ShaderID id, const std::string uniform, float * value)
	{
		GetLocationUseProgram(id, uniform);
		glUniformMatrix4fv(m_programs[id]->m_uniforms[uniform], 1, GL_TRUE, value);
	}

	//	4x4 Matrix Block
	void ShaderManager::SetUniformBlock(float * value, unsigned index)
	{
		glBindBuffer(GL_UNIFORM_BUFFER, m_globalUBO);
		glBufferSubData(GL_UNIFORM_BUFFER, index * MATRIX_SIZE, MATRIX_SIZE, value);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}
}