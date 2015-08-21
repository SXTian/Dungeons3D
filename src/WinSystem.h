/*****************************************************************************************
  Project      : 3D Game Engine
  Author       : Sam Tian
  Contributors :
******************************************************************************************/
#pragma once

#include "BaseSystem.h"
#include "IEventMessage.h"

#include <windows.h>
#include <string>

namespace Dungeons3D
{
	class WinSystem : public BaseSystem, public IEventMessageModule
	{
	public:
		WinSystem(const char* config);
		~WinSystem();

		void Initialize();
		void Update(float delta);

	private:
		HWND m_hWnd;
		HINSTANCE m_hInstance;
		HDC m_hDC;
		PIXELFORMATDESCRIPTOR m_pfd;
		HGLRC m_hGLRC;
		int m_iFormat;

		//	In pixels
		int m_windowWidth;
		int m_windowHeight;
	};

	//	For WndProc()...
	extern WinSystem* pWinSystem;
}