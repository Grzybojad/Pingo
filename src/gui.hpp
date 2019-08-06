#pragma once

#include <stdio.h>
#include <stdarg.h>
#include <vector>
#include <string>

#include <vita2d.h>

#include "texture.hpp"
#include "common.hpp"

namespace Gui
{
    // Load font from file
    void loadFont();

    // Free the loaded font
    void freeFont();

    // Enum for positioning text
    enum class Position
    {
        normal,
        centered,
        centeredX,
        centeredY,
        centeredTop,
        alignRight,
        alignTop,
        alignTopRight
    };

    // Text drawing functions
    void drawText( int x, int y, unsigned int size, const char *text );
    void drawTextf( int x, int y, unsigned int size, const char *text, ... );
    void drawText_color( int x, int y, unsigned int size, unsigned int color, const char *text );
    void drawTextf_color( int x, int y, unsigned int size, unsigned int color, const char *text, ... );
    void drawText_position( Position p, int x, int y, unsigned int size, const char *text );
    void drawTextf_position( Position p, int x, int y, unsigned int size, const char *text, ... );
    void drawText_color_position( Position p, int x, int y, unsigned int size, unsigned int color, const char *text );
    void drawTextf_color_position( Position p, int x, int y, unsigned int size, unsigned int color, const char *text, ... );

    // Gui elements drawing
    void drawMessageBox( const char *header, const char *body );

    // Text measurements
    int getTextWidth( unsigned int size, const char *text );
    int getTextHeight( unsigned int size, const char *text );
    

    // Debug text
    extern std::string debugText;
    void drawDebugText();

    extern float FONT_SCALE;
    extern unsigned int MAIN_FONT_COLOR;

    // A separate font for sizes 1-99
    extern vita2d_font *mainFont[ 99 ];
}