#include "Main\Game.h"
#include "MetroidGameContent\MetroidContent.h"
#include "MetroidGameContent\MetroidScene.h"
#include <Windows.h>

int  main() //WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	srand((unsigned int)time(NULL));
	MetroidContent content;
	Game Metroid(&content);
	return Metroid.Run();
}
