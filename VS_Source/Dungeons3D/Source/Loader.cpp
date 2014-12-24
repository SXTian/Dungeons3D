/*****************************************************************************************
Project      : 3D Game Engine
Author       : Sam Tian
Contributors :
******************************************************************************************/
#include "Loader.h"
#include "GLHeaders.h"

#include <string>
#include <map>
#include <vector>
#include <fstream>

namespace Dungeons3D
{
	struct Renderer
	{
		Renderer(GLenum primitiveType) : type(primitiveType) {}

		GLenum type;				//	primitive type
		GLuint start;				
		GLuint count;				//	element count

		void Render()
		{
			//	Indexed drawing
			glDrawElements(type, count, GL_FLOAT, (void*)start);;
		}
	};

	struct MeshData
	{
		MeshData() : iAttribArrayBuffer(0), iIndexBuffer(0), iVAO(0) {}
		~MeshData()
		{
			glDeleteBuffers(1, &iAttribArrayBuffer);
			glDeleteBuffers(1, &iIndexBuffer);
			glDeleteVertexArrays(1, &iVAO);

			for (auto it = mapVAO.begin(); it != mapVAO.end(); ++it)
				glDeleteVertexArrays(1, &it->second);
		}

		GLuint iAttribArrayBuffer;
		GLuint iIndexBuffer;
		GLuint iVAO;

		std::map<std::string, GLuint> mapVAO;
		std::vector<Renderer> primatives;
	};

	Loader::Loader() : _data(new MeshData)
	{
	}

	Loader::~Loader()
	{
		delete _data;
	}

	void Loader::load(std::string filename)
	{
		std::ifstream file(filename.c_str(), std::ifstream::in);
		std::string keyword;
		
		while (!file.eof())
		{
			file >> keyword;
			if (keyword.compare("vertex_positions") == 0)
			{
			}
			else if (keyword.compare("vertex_colors") == 0)
			{
			}
			else if (keyword.compare("primitive_trifan") == 0)
			{
				_data->primatives.push_back(Renderer(GL_TRIANGLE_FAN));
			}
			else if (keyword.compare("primitive_tri") == 0)
			{
				_data->primatives.push_back(Renderer(GL_TRIANGLES));
			}
		}

	}
}