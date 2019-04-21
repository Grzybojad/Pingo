#include <time.h>

#include <psp2/kernel/processmgr.h>

#include "game.hpp"


int main()
{
	srand(time(NULL));

    Game game;

	game.mainLoop();

	sceKernelExitProcess( 0 );
	return 0;
}