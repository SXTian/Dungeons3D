/*****************************************************************************************
  Project      : 3D Game Engine
  Author       : Sam Tian
  Contributors :
******************************************************************************************/
#include "GameEngine.h"

using namespace Dungeons3D;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	GameEngine dungeons3D;
  dungeons3D.AddSystem(SYS_WINDOWS);
  dungeons3D.AddSystem(SYS_GRAPHICS);
  dungeons3D.GameLoop();
}