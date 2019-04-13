#include "common.hpp"

SceUInt64 prevFrameClock = 0;
SceUInt64 frameTime = 0;
float timestep = 0;

void calcFrameTime()
{	
	frameTime = ( sceKernelGetProcessTimeWide() - prevFrameClock );
	timestep = frameTime / 16666.6666;

	prevFrameClock = sceKernelGetProcessTimeWide();
}