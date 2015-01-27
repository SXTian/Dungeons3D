/*****************************************************************************************
Project      : 3D Game Engine
Author       : Sam Tian
Contributors :
******************************************************************************************/
#include "Loader3DS.h"
#include "MeshData.h"
#include "ChunkNames3DS.h"
#include <assert.h>

namespace Dungeons3D
{
	Loader3DS::Loader3DS()
	{
		for (auto &i : m_data)
			i = new MeshData();
	}

	Loader3DS::~Loader3DS()
	{
		for (auto &i : m_data)
			delete i;
	}

	void Loader3DS::load(std::string filename)
	{
		std::vector <unsigned short> indexData;

		unsigned polyCount = 0;

		LoadFile(filename.c_str());

		unsigned short vertices_qty;
		unsigned short polygons_qty;

		float * verts = NULL;
		unsigned short * faces = NULL;
		unsigned short chunkname;
		unsigned long mem = 0;
		unsigned short num = 0;

		unsigned facenum = 0;

		while(!Eof()) 
		{
			chunkname = GetChunkName();
			switch (chunkname) 
			{
			case MAIN3DS:
				EnterChunk();
				break;
			case EDIT3DS:
				EnterChunk();
				break;
			case EDIT_OBJECT:
				SkipStrData();
				break;
			case OBJ_TRIMESH:
				EnterChunk();
				break;
			case TRI_VERTEXL:
				GetChunkData(&vertices_qty, 2);
				mem = vertices_qty * 3 * sizeof(float);	//	3 values at 4 bytes per float
				verts = (float *)malloc(mem);
				assert(verts);
				GetChunkData(verts, mem, 2);

				glGenBuffers(1, &m_data[polyCount]->vertexBuffer);

				glBindBuffer(GL_ARRAY_BUFFER, m_data[polyCount]->vertexBuffer);
				glBufferData(GL_ARRAY_BUFFER, mem, verts, GL_STATIC_DRAW);
				glBindBuffer(GL_ARRAY_BUFFER, 0);

				free(verts);

				SkipChunk();
				break;
			case TRI_FACEL1:

				GetChunkData(&polygons_qty, 2);
				mem = polygons_qty * 4 * sizeof(unsigned short);	//	4 values at 2 bytes per short
				faces = (unsigned short *)malloc(mem);	
				assert(faces);
				GetChunkData(faces, mem, 2);

				for (unsigned i = 0; i < polygons_qty; ++i)
				{
					indexData.push_back(*(faces + (i * 4)));
					indexData.push_back(*(faces + (i * 4) + 1));
					indexData.push_back(*(faces + (i * 4) + 2));
				}

				glGenBuffers(1, &m_data[polyCount]->indexBuffer);

				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_data[polyCount]->indexBuffer);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short) * polygons_qty * 3, indexData.data(), GL_STATIC_DRAW);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

				free(faces);

				Renderer primitive;
				primitive.type = GL_TRIANGLES;
				primitive.start = 0;
				primitive.count = polygons_qty * 3;
				m_data[polyCount]->primatives.push_back(primitive);

				glGenVertexArrays(1, &m_data[polyCount]->vao);
				glBindVertexArray(m_data[polyCount]->vao);

				glBindBuffer(GL_ARRAY_BUFFER, m_data[polyCount]->vertexBuffer);
				glEnableVertexAttribArray(0);
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_data[polyCount]->indexBuffer);

				glBindVertexArray(0);

				++polyCount;
				indexData.clear();
				SkipChunk();
				break;

			case TRI_TEXCOORD:
				/*
				mem = pObj->vertices_qty * 2 * 4;	//	2 values at 4 bytes per float
				verts = (float*)malloc(mem);
				assert(verts);
				GetChunkData(verts, mem, 2);

				i = j = 0;
				while (j < pObj->vertices_qty)
				{
				pObj->textureList[j].u = *(verts + i++);
				pObj->textureList[j].v = *(verts + i++);
				++j;
				}
				free(verts);
				*/
				SkipChunk();
				break;
			default:
				SkipChunk();
				break;
			}
		}
	}

	void Loader3DS::render()
	{
		for (auto &i : m_data)
		{

			glBindVertexArray(i->vao);

			for (auto &j : i->primatives)
				j.Render();

			glBindVertexArray(0);
		}
	}
}