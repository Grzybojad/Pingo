#include "common.hpp"

SceUInt64 prevFrameClock = 0;
SceUInt64 frameTime = 0;
float timestep = 0;

bool alreadyShowedCompleteMessage = false;

void calcFrameTime()
{	
	frameTime = ( sceKernelGetProcessTimeWide() - prevFrameClock );
	timestep = frameTime / 16666.6666;

	prevFrameClock = sceKernelGetProcessTimeWide();
}

std::string timeToString( int time )
{
	std::string clock = "";

	int second = 1;

	int hours = time / ( second * 60 * 60 );
	int minutes = ( time % ( second * 60 * 60 ) / ( second * 60 ) );
	int seconds = ( time % ( second * 60 ) ) / second;

	if( hours > 0 )
	{
		clock.append( std::to_string( hours ) );
		clock.append( ":" );
	}

	clock.append( std::to_string( minutes / 10 ) );
	clock.append( std::to_string( minutes % 10 ) );

	clock.append( ":" );

	clock.append( std::to_string( seconds / 10 ) );
	clock.append( std::to_string( seconds % 10 ) );
	
	return clock;
}