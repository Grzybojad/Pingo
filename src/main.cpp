#include "game.hpp"

#include <psp2/kernel/processmgr.h> 

int main()
{
    Game game;

	game.mainLoop();

	sceKernelExitProcess( 0 );
	return 0;
}