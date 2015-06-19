/*****************************************************************************************
Project      : 3D Game Engine
Author       : Sam Tian
Contributors :
******************************************************************************************/
#include "Loader.h"
#include "MeshData.h"

#include <string>
#include <map>
#include <vector>
#include <fstream>

namespace Dungeons3D
{
	Loader::Loader() : m_data(new MeshData)
	{
	}

	Loader::~Loader()
	{

	}

	void Loader::load(std::string filename)
	{
		//	Temp buffers to store vertex and index data
		std::vector<float> vertexData;
		std::vector<GLushort> indexData;

		//	Counters for passing offsets into openGL buffers
		GLuint vertexOffset = 0;
		GLuint primitiveOffset = 0;
		GLuint indexCount = 0;

		//	File reading starts here
		std::ifstream file(filename.c_str(), std::ifstream::in);
		std::string keyword;
		float nextValue;;

		while (!file.eof())
		{
			if (!file)
				file.clear();

			file >> keyword;
			if (keyword.compare("position") == 0)
			{
				while (file >> nextValue)
				{
					vertexData.push_back(nextValue);
					++vertexOffset;
				}
			}
			else if (keyword.compare("color") == 0)
			{
				while (file >> nextValue)
					vertexData.push_back(nextValue);
			}
			else if (keyword.compare("primitive") == 0)
			{
				Renderer primitive;
				file >> keyword;
				if (keyword.compare("trifan") == 0)
					primitive.type = GL_TRIANGLE_FAN;
				else if (keyword.compare("tristrip") == 0)
					primitive.type = GL_TRIANGLE_STRIP;
				else if (keyword.compare("tri") == 0)
					primitive.type = GL_TRIANGLES;

				primitive.start = primitiveOffset;
				indexCount = 0;
				while (file >> nextValue)
				{
					indexData.push_back((GLushort)nextValue);
					++indexCount;
				}
				primitive.count = indexCount;
				primitiveOffset += indexCount;
				m_data->primatives.push_back(primitive);
			}
		}

		//	OpenGL buffer filling starts here
		glGenBuffers(1, &m_data->vertexBuffer);

		glBindBuffer(GL_ARRAY_BUFFER, m_data->vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertexData.size(), vertexData.data(), GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glGenBuffers(1, &m_data->indexBuffer);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_data->indexBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * indexData.size(), indexData.data(), GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		glGenVertexArrays(1, &m_data->vao);
		glBindVertexArray(m_data->vao);

		glBindBuffer(GL_ARRAY_BUFFER, m_data->vertexBuffer);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(float) * vertexOffset));
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_data->indexBuffer);

		glBindVertexArray(0);
	}

	void Loader::render()
	{
		if (!m_data->vao)
			return;

		glBindVertexArray(m_data->vao);

		for (auto &i : m_data->primatives)
			i.Render();
		
		glBindVertexArray(0);
	}
}