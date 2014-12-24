/*****************************************************************************************
Project      : 3D Game Engine
Author       : Sam Tian
Contributors :
******************************************************************************************/
#include "WinSystem.h"
#include "GLHeaders.h"
#include <tchar.h>

namespace Dungeons3D
{
	static TCHAR winName[] = _T("3D Engine");

	LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}

	WinSystem::WinSystem(const char* config)
	{
		//	TO DO: Read from config.txt

		//	1680 x 1050
		_windowWidth = GetSystemMetrics(SM_CXSCREEN);
		_windowHeight = GetSystemMetrics(SM_CYSCREEN);

		RECT windowRect = {0, 0, _windowWidth, _windowHeight};
		AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, FALSE);

		//	Make window class
		WNDCLASSEX winClass = {
			sizeof(WNDCLASSEX),
			CS_OWNDC,
			WndProc,
			0, 0,
			GetModuleHandle(NULL),
			NULL,
			LoadCursor(NULL, IDC_ARROW),
			NULL,
			NULL,
			winName,
			NULL
		};

		//	Register the class
		RegisterClassEx(&winClass);

		//	Device settings
		DEVMODE dmScreenSettings;								// Device Mode
		memset(&dmScreenSettings,0,sizeof(dmScreenSettings));	// Makes Sure Memory's Cleared
		dmScreenSettings.dmSize=sizeof(dmScreenSettings);		// Size Of The Devmode Structure
		dmScreenSettings.dmPelsWidth	= _windowWidth;			// Selected Screen Width
		dmScreenSettings.dmPelsHeight	= _windowHeight;		// Selected Screen Height
		dmScreenSettings.dmBitsPerPel= 24;						// Selected Bits Per Pixel
		dmScreenSettings.dmFields = DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;
		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

		AdjustWindowRectEx(
			&windowRect,
			WS_POPUP | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 
			FALSE, 
			WS_EX_APPWINDOW);	

		_hInstance = winClass.hInstance;

		_hWnd = CreateWindow(
			winName,	
			_T("Engine Title"),						
			WS_POPUP | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,				
			CW_USEDEFAULT, CW_USEDEFAULT,
			windowRect.right - windowRect.left,	
			windowRect.bottom - windowRect.top,	
			GetDesktopWindow(),					
			NULL,								
			_hInstance,							
			NULL);		

		if (!_hWnd)
		{
			MessageBox(NULL,
				_T("Call to CreateWindow failed!"),
				_T("Win32 Guided Tour"),
				NULL);

			return;
		}

		DragAcceptFiles( _hWnd, true );

		_hDC = GetDC(_hWnd);

		//	Set up the pixel format descriptor
		ZeroMemory(&_pfd, sizeof(_pfd));
		_pfd.nSize = sizeof(_pfd);

		_pfd.nVersion = 1;
		_pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
		_pfd.iPixelType = PFD_TYPE_RGBA;
		_pfd.cColorBits = 32;
		_pfd.cDepthBits = 24;
		_pfd.cStencilBits = 8;
		_pfd.iLayerType = PFD_MAIN_PLANE;
		_iFormat = ChoosePixelFormat(_hDC, &_pfd);
		SetPixelFormat(_hDC, _iFormat, &_pfd);


		_hGLRC = wglCreateContext(_hDC);
		wglMakeCurrent(_hDC, _hGLRC);

		ClipCursor(&windowRect);
		ShowCursor(false);
		SetCursorPos(1024/2, 786/2);
	}


	WinSystem::~WinSystem()
	{
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(_hGLRC);

		ReleaseDC(_hWnd, _hDC);
		UnregisterClass(winName, _hInstance);
	}

	void WinSystem::Update(float delta)
	{
		MSG msg;
		RECT r;
		GetWindowRect(_hWnd, &r);
		ClipCursor(&r);

		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) 
		{
			TranslateMessage(&msg);	
			DispatchMessage(&msg);	
		}
		SwapBuffers(_hDC);
	}

	void WinSystem::ActivateWindow()
	{
		ShowWindow(_hWnd, SW_SHOWDEFAULT);
		UpdateWindow(_hWnd);
	}
}