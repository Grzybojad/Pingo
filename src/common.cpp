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


Rect operator +( const Rect& a, const Rect& b )
{
    return Rect( a.x + b.x, a.y + b.y, a.w + b.w, a.h + b.h );
}

Vec2 operator +( const Vec2& a, const Vec2& b )
{
	return Vec2( a.x + b.x, a.y + b.y );
}
Vec2 operator -( const Vec2& a, const Vec2& b )
{
	return Vec2( a.x - b.x, a.y - b.y );
}
bool operator ==( const Vec2& a, const Vec2& b )
{
	return ( a.x == b.x && a.y == b.y );
}
bool operator !=( const Vec2& a, const Vec2& b )
{
	return !( a == b );
}


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

std::string word_wrap( std::string text, unsigned per_line )
{
	// http://www.cplusplus.com/forum/beginner/132223/#msg714543
	unsigned line_begin = 0;
	while( line_begin < text.size() )
	{
		const unsigned ideal_end = line_begin + per_line ;
		unsigned line_end = ( ideal_end <= text.size() ? ideal_end : text.size() - 1 );

		if( line_end == text.size() - 1 )
		{
			++line_end;
		}
		else if( std::isspace( text[ line_end ] ) )
		{
			text[line_end] = '\n';
			++line_end;
		}
		else
		{   // backtrack
			unsigned end = line_end;
			while( end > line_begin && !std::isspace( text[ end ] ) )
			{
				--end;
			}
			if( end != line_begin )
			{
				line_end = end;
				text[ line_end++ ] = '\n';
			}
			else {
				text.insert( line_end++, 1, '\n' );
			}
		}
		line_begin = line_end;
	}
	return text;
}