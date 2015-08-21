/*****************************************************************************************
Project      : 3D Game Engine
Author       : Sam Tian
Contributors :
******************************************************************************************/
#include "WinSystem.h"
#include "EventMessages.h"
#include "GLHeaders.h"
#include <tchar.h>
#include <windowsx.h>

namespace Dungeons3D
{
	static TCHAR winName[] = _T("3D Engine");
	WinSystem* pWinSystem = NULL;

	LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch(msg)
		{
		case WM_KEYDOWN:
			{
				MessageKeyboard msg(MSG_KeyPress);
				msg.key = wParam;
				pWinSystem->PostMsg(&msg);
			}
			break;
		case WM_MOUSEMOVE:
			{
				MessageMouseMove msg(MSG_MouseMove);
        msg.x = GET_X_LPARAM(lParam);
        msg.y = GET_Y_LPARAM(lParam);
				pWinSystem->PostMsg(&msg);
			}
		case WM_MOUSEWHEEL:
			{
				MessageMouseWheel msg(MSG_MouseWheel);
				msg.wheel = GET_WHEEL_DELTA_WPARAM(wParam);
				pWinSystem->PostMsg(&msg);
			}
		}
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}

	WinSystem::WinSystem(const char* config)
	{
		pWinSystem = this;
		//	TO DO: Read from config.txt

		//	1680 x 1050
		m_windowWidth = GetSystemMetrics(SM_CXSCREEN);
		m_windowHeight = GetSystemMetrics(SM_CYSCREEN);

		RECT windowRect = {0, 0, m_windowWidth, m_windowHeight};
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
		dmScreenSettings.dmPelsWidth = m_windowWidth;			// Selected Screen Width
		dmScreenSettings.dmPelsHeight = m_windowHeight;			// Selected Screen Height
		dmScreenSettings.dmBitsPerPel= 24;						// Selected Bits Per Pixel
		dmScreenSettings.dmFields = DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;
		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

		AdjustWindowRectEx(
			&windowRect,
			WS_POPUP | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 
			FALSE, 
			WS_EX_APPWINDOW);	

		m_hInstance = winClass.hInstance;

		m_hWnd = CreateWindow(
			winName,	
			_T("Engine Title"),						
			WS_POPUP | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,				
			CW_USEDEFAULT, CW_USEDEFAULT,
			windowRect.right - windowRect.left,	
			windowRect.bottom - windowRect.top,	
			GetDesktopWindow(),					
			NULL,								
			m_hInstance,							
			NULL);		

		if (!m_hWnd)
		{
			MessageBox(NULL,
				_T("Call to CreateWindow failed!"),
				_T("Win32 Guided Tour"),
				NULL);

			return;
		}

		DragAcceptFiles( m_hWnd, true );

		m_hDC = GetDC(m_hWnd);

		//	Set up the pixel format descriptor
		ZeroMemory(&m_pfd, sizeof(m_pfd));
		m_pfd.nSize = sizeof(m_pfd);

		m_pfd.nVersion = 1;
		m_pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
		m_pfd.iPixelType = PFD_TYPE_RGBA;
		m_pfd.cColorBits = 32;
		m_pfd.cDepthBits = 24;
		m_pfd.cStencilBits = 8;
		m_pfd.iLayerType = PFD_MAIN_PLANE;
		m_iFormat = ChoosePixelFormat(m_hDC, &m_pfd);
		SetPixelFormat(m_hDC, m_iFormat, &m_pfd);

		m_hGLRC = wglCreateContext(m_hDC);
		wglMakeCurrent(m_hDC, m_hGLRC);

		ClipCursor(&windowRect);
		ShowCursor(false);
		SetCursorPos(1024/2, 786/2);

		ShowWindow(m_hWnd, SW_SHOWDEFAULT);
		UpdateWindow(m_hWnd);
	}

	WinSystem::~WinSystem()
	{
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(m_hGLRC);

		ReleaseDC(m_hWnd, m_hDC);
		UnregisterClass(winName, m_hInstance);
	}

	void WinSystem::Update(float delta)
	{
		MSG msg;
		RECT r;
		GetWindowRect(m_hWnd, &r);
		ClipCursor(&r);

		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) 
		{
			TranslateMessage(&msg);	
			DispatchMessage(&msg);	
		}
		SwapBuffers(m_hDC);
	}
}