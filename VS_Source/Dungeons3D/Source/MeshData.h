/*****************************************************************************************
Project      : 3D Game Engine
Author       : Sam Tian
Contributors :
******************************************************************************************/
#pragma once

#include "GLHeaders.h"

#include <vector>

namespace Dungeons3D
{
	struct Renderer
	{
		GLenum type;				//	primitive type
		GLuint start;				
		GLuint count;				//	element count

		void Render()
		{
			//	Indexed drawing
			glDrawElements(type, count, GL_UNSIGNED_SHORT, (void*)(start * sizeof(GLushort)));
		}
	};

	struct MeshData
	{
		MeshData() : vertexBuffer(0), indexBuffer(0), vao(0) {}
		~MeshData()
		{
			glDeleteBuffers(1, &vertexBuffer);
			glDeleteBuffers(1, &indexBuffer);
			glDeleteVertexArrays(1, &vao);
		}

		GLuint vertexBuffer;
		GLuint indexBuffer;
		GLuint vao;

		std::vector<Renderer> primatives;
	};
}