/*****************************************************************************************
  Project      : 3D Game Engine
  Author       : Sam Tian
  Contributors :
******************************************************************************************/
#pragma once

#include <cstdio>

namespace Dungeons3D
{
	struct ChunkHeader
	{
		unsigned short id;
		unsigned long length;
	};

	class Parser3DS
	{
	public:
		Parser3DS(void);
		Parser3DS(char *filename);
		~Parser3DS(void);

		unsigned short GetChunkName(void);
		void SkipChunk(void);
		void EnterChunk(long datalength = 0);
		unsigned long GetChunkLength(void);
		void GetChunkData(void *buffer, unsigned long buffersize, unsigned long skip = 0);
		void SkipStrData(void) { StrDataLength(true); }
		unsigned long GetStrDataLength(void) { return StrDataLength(false); }
		void Rewind(void);
		bool LoadFile(const char *filename);
		int Eof(void);
		void CloseFile(void);
	protected:
		unsigned long StrDataLength(bool skipData);
		void Read(void);

		ChunkHeader header;
		FILE *m_file;
	};
}