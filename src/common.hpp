#pragma once

#include <cmath>
#include <string>

#include <psp2/kernel/processmgr.h>
#include <vita2d.h>

const int SCREEN_WIDTH = 960;
const int SCREEN_HEIGHT = 544;

// File paths
extern std::string pathData;
extern std::string pathTexture;
extern std::string pathSounds;
extern std::string pathFonts;
extern std::string pathLevels;
extern std::string pathCustomLevels;
// The "curtain" texture in texture.hpp/cpp is loaded from "app0:/sce_sys"

extern bool ENABLE_TOUCH;
extern bool alreadyShowedCompleteMessage;

extern unsigned int WALLCOLOR;
extern unsigned int BGCOLOR;

struct Rect
{
    public:
        float x;
        float y;
        float w;
        float h;

        Rect() { }
        Rect( float x, float y, float w, float h )
        {
            this->x = x;
            this->y = y;
            this->w = w;
            this->h = h;
        }
};

extern Rect operator +( const Rect& a, const Rect& b );

struct Vec2
{
    public:
        float x;
        float y;

        Vec2() { }
        Vec2( float x, float y )
        {
            this->x = x;
            this->y = y;
        }

        Vec2( Rect rect )
        {
            this->x = rect.x;
            this->y = rect.y;
        }

        Rect toRect( float w, float h )
        {
            return Rect( x, y, w, h );
        }

        static float distance( Vec2 a, Vec2 b )
        {
            return sqrt( pow( b.x - a.x, 2 ) + pow( b.y - a.y, 2 ) );
        }
};

// Framerate independance
extern SceUInt64 prevFrameClock;    // The time between the start of the program and the previous frame (in microseconds)
extern SceUInt64 frameTime;		    // Time between frames (in microseconds)
extern float timestep;              // The multiplier for time sensitive actions (1.0 for 60FPS)

// Calculate the frameTime and timestep (call after each frame!)
void calcFrameTime();

// Convert time in seconds to a HH:MM:SS string
std::string timeToString( int time );