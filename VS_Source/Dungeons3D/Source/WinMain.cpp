/*****************************************************************************************
  Project      : 3D Game Engine
  Author       : Sam Tian
  Contributors :
******************************************************************************************/
#include "WinSystem.h"
#include "GraphicsSystem.h"

using namespace Dungeons3D;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	WinSystem * winSystem = new WinSystem("./Resources/config.txt");
	GraphicsSystem * graphicsSystem = new GraphicsSystem();

	winSystem->ActivateWindow();

	while (true)
	{
		winSystem->Update(0);
		graphicsSystem->Update(0);
	}


}