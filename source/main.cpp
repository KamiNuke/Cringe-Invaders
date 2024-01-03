#include "SDL.h"

#include "MainClass.h"

int main(int argc, char* argv[])
{
	MainClass* game{ new MainClass{} };

	game->Loop();

	delete game;
	return 0;
}