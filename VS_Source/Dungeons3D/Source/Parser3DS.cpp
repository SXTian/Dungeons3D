/*****************************************************************************************
Project      : 3D Game Engine
Author       : Sam Tian
Contributors :
******************************************************************************************/

#include "Parser3DS.h"
#include <windows.h>

namespace Dungeons3D
{
	Parser3DS::Parser3DS()
	{
		header.id = 0;
		header.length = 0;
		m_file = NULL;
	}

	Parser3DS::Parser3DS(char *filename)
	{
		header.id = 0;
		header.length = 0;
		m_file = NULL;
		LoadFile(filename);
	}

	Parser3DS::~Parser3DS(void)
	{
		if (m_file)
			fclose(m_file);
	}

	unsigned short Parser3DS::GetChunkName(void)
	{
		return header.id;
	}

	void Parser3DS :: SkipChunk(void)
	{
		if (m_file == NULL)
			return;
		fseek(m_file, header.length - 6, SEEK_CUR);
		Read();
	}


	void Parser3DS :: EnterChunk(long datalength)
	{
		if (m_file == NULL)
			return;
		fseek(m_file, (signed long)datalength, SEEK_CUR);
		Read();
	}


	unsigned long Parser3DS :: GetChunkLength(void)
	{
		return header.length;
	}


	void Parser3DS :: GetChunkData(void *buffer, unsigned long buffersize, unsigned long skip)
	{
		fseek(m_file, skip, SEEK_CUR);
		unsigned long amt = min(buffersize, header.length - 6);
		amt = fread(buffer, 1, amt, m_file);
		fseek(m_file, (long)-1 * ((signed long)amt + (signed long)skip), SEEK_CUR);
	}


	void Parser3DS :: Rewind(void)
	{
		if (m_file == NULL)
			return;
		fseek(m_file, 0, SEEK_SET);
		Read();
	}

	unsigned long Parser3DS::StrDataLength(bool skipData)
	{
		unsigned char buf;
		long len = 0;
		do {
			fread(&buf, 1, 1, m_file);
			len++;
		} while (buf != 0x00);
		if (!skipData)
			fseek(m_file, -1 * len, SEEK_CUR);
		else
			Read();
		return len;
	}


	void Parser3DS :: Read(void)
	{
		//fread(&header, 6, 1, m_file);	// need to look into why this doesn't work.
		fread(&header.id, 2, 1, m_file);
		fread(&header.length, 4, 1, m_file);
	}

	void Parser3DS :: CloseFile(void)
	{
		if (m_file != NULL) {
			fclose(m_file);
			m_file = NULL;
		}
	}

	int Parser3DS :: Eof(void)
	{
		if (m_file)
			return feof(m_file);
		else
			return true;
	}

	bool Parser3DS :: LoadFile(const char *filename)
	{
		if (m_file != NULL) {
			fclose(m_file);
		}
		fopen_s(&m_file, filename, "rbR");	// rbR = read, binary, Random-access
		if (m_file) {
			Read();
			return true;
		} else
			return false;
	}

}