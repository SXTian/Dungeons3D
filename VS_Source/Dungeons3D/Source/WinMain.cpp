/*****************************************************************************************
  Project      : 3D Game Engine
  Author       : Sam Tian
  Contributors :
******************************************************************************************/
#include "GameEngine.h"

using namespace Dungeons3D;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	GameEngine game;
	game.AddSystem(SYS_WINDOWS);
	game.AddSystem(SYS_GRAPHICS);
	game.GameLoop();
}