/*****************************************************************************************
Project      : 3D Game Engine
Author       : Sam Tian
Contributors :
******************************************************************************************/
#include "IShaderManager.h"
#include "ShaderManager.h"
#include "GLHeaders.h"
#include <iostream>
#include <fstream>

//	This + Uniform block binding stuff needs to get refactored
#define MATRIX_SIZE sizeof(float)*16

namespace Dungeons3D
{
	using namespace std;

	IShaderManager::IShaderManager(shared_ptr<ShaderManager> pManager) : m_pManager(pManager)
	{
	}

	void IShaderManager::EnableProgram(ShaderID id)
	{
		glUseProgram(m_pManager->GetProgram(id));
	}

	void IShaderManager::DisablePrograms()
	{
		glUseProgram(0);
	}

	//	SETTER OVERLOADS
	//----------------------------------------------------------------------------------------------------------
	//	1 float
	void IShaderManager::SetShaderUniform(ShaderID id, const std::string uniform, float value)
	{
		glUseProgram(m_pManager->GetProgram(id));
		glUniform1f(m_pManager->GetUniform(id, uniform), value);
	}
	//	2 floats
	void IShaderManager::SetShaderUniform(ShaderID id, const std::string uniform, float value1, float value2)
	{
		glUseProgram(m_pManager->GetProgram(id));
		glUniform2f(m_pManager->GetUniform(id, uniform), value1, value2);
	}
	//	3 floats
	void IShaderManager::SetShaderUniform(ShaderID id, const std::string uniform, float value1, float value2, float value3)
	{
		glUseProgram(m_pManager->GetProgram(id));
		glUniform3f(m_pManager->GetUniform(id, uniform), value1, value2, value3);
	}

	//	4 floats
	void IShaderManager::SetShaderUniform(ShaderID id, const std::string uniform, float value1, float value2, float value3, float value4)
	{
		glUseProgram(m_pManager->GetProgram(id));
		glUniform4f(m_pManager->GetUniform(id, uniform), value1, value2, value3, value4);
	}

	//	4x4 Matrix
	void IShaderManager::SetShaderUniform(ShaderID id, const std::string uniform, const float * value, int size)
	{
		glUseProgram(m_pManager->GetProgram(id));
    if (size == 16)
		  glUniformMatrix4fv(m_pManager->GetUniform(id, uniform), 1, GL_TRUE, value);
    else if (size == 9)
      glUniformMatrix3fv(m_pManager->GetUniform(id, uniform), 1, GL_TRUE, value);
	}

	//	4x4 Matrix Block
	void IShaderManager::SetShaderUniformBlock(float * value, unsigned index)
	{
		glBindBuffer(GL_UNIFORM_BUFFER, m_pManager->GetUBO());
		glBufferSubData(GL_UNIFORM_BUFFER, index * MATRIX_SIZE, MATRIX_SIZE, value);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}
}