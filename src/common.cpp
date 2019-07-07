#include "common.hpp"

SceUInt64 prevFrameClock = 0;
SceUInt64 frameTime = 0;
float timestep = 0;

std::string pathData = "ux0:/data/Pingo/";
std::string pathTexture = "app0:/img/";
std::string pathSounds  = "app0:/sounds/";
std::string pathFonts   = "app0:/font/";
std::string pathLevels  = "app0:/levels/";
std::string pathCustomLevels = "ux0:/data/Pingo/levels/";

bool ENABLE_TOUCH = true;
bool alreadyShowedCompleteMessage = false;

unsigned int WALLCOLOR = RGBA8( 144, 145, 194, 255 );
unsigned int BGCOLOR = RGBA8( 97, 90, 160, 255 );

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