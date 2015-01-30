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

		void ActivateWindow();

	private:
		HWND _hWnd;
		HINSTANCE _hInstance;
		HDC _hDC;
		PIXELFORMATDESCRIPTOR _pfd;
		HGLRC _hGLRC;
		int _iFormat;

		//	In pixels
		int _windowWidth;
		int _windowHeight;
	};

	extern WinSystem* pWinSystem;
}