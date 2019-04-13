#include "gui.hpp"

namespace Gui
{
    float FONT_SCALE = 1.0;
    vita2d_font *mainFont[ 99 ];
    unsigned int MAIN_FONT_COLOR = RGBA8( 0, 0, 0, 255 );
    std::vector<const char*> debugText;
    

    void loadFont()
    {
        for( int i = 0; i <= 99; ++i )
            mainFont[ i ] = vita2d_load_font_file( "app0:/font/Ubuntu-Medium.ttf" );
    }

    void drawText( int x, int y, unsigned int size, const char *text )
    {
        vita2d_font_draw_text( mainFont[ (int)(size * FONT_SCALE) ], x, y, MAIN_FONT_COLOR, (int)(size * FONT_SCALE), text );
    }

    void drawTextf( int x, int y, unsigned int size, const char *text, ... )
    {
        char buf[1024];
        va_list argptr;

        va_start(argptr, text);
        vsnprintf(buf, sizeof(buf), text, argptr);
        va_end(argptr);

        return drawText( x, y, size, buf );
    }

    void drawText_color( int x, int y, unsigned int size, unsigned int color, const char *text )
    {
        vita2d_font_draw_text( mainFont[ (int)(size * FONT_SCALE) ], x, y, color, (int)(size * FONT_SCALE), text );
    }

    void drawTextf_color( int x, int y, unsigned int size, unsigned int color, const char *text, ... )
    {
        char buf[1024];
        va_list argptr;

        va_start( argptr, text );
        vsnprintf( buf, sizeof(buf), text, argptr );
        va_end( argptr );

        return drawText_color( x, y, size, color, buf );
    }

    void drawText_position( Position p, int x, int y, unsigned int size, const char *text )
    {
        int w = vita2d_font_text_width( mainFont[ (int)(size * FONT_SCALE) ], (int)(size * FONT_SCALE), text );
        int h = vita2d_font_text_height( mainFont[ (int)(size * FONT_SCALE) ], (int)(size * FONT_SCALE), text );

        switch( p )
        {
            case Position::normal:
            default:
                return drawText( x, y, size, text );

            case Position::centered:
                return drawText( x - (w/2), y + (h/2), size, text );

            case Position::centeredX:
                return drawText( x - (w/2), y, size, text );

            case Position::centeredY:
                return drawText( x, y + (h/2), size, text );

            case Position::alignRight:
                return drawText( x - w, y, size, text );

            case Position::alignTop:
                return drawText( x, y + h, size, text );

            case Position::alignTopRight:
                return drawText( x - w, y + h, size, text );
        }
    }

    void drawTextf_position( Position p, int x, int y, unsigned int size, const char *text, ... )
    {
        char buf[1024];
        va_list argptr;

        va_start( argptr, text );
        vsnprintf( buf, sizeof(buf), text, argptr );
        va_end( argptr );

        return drawText_position( p, x, y, size, buf );
    }

    void drawText_color_position( Position p, int x, int y, unsigned int size, unsigned int color, const char *text )
    {
        int w = vita2d_font_text_width( mainFont[ (int)(size * FONT_SCALE) ], (int)(size * FONT_SCALE), text );
        int h = vita2d_font_text_height( mainFont[ (int)(size * FONT_SCALE) ], (int)(size * FONT_SCALE), text );

        switch( p )
        {
            case Position::normal:
            default:
                return drawText_color( x, y, size, color, text );

            case Position::centered:
                return drawText_color( x - (w/2), y + (h/2), size, color, text );

            case Position::centeredX:
                return drawText_color( x - (w/2), y, size, color, text );

            case Position::centeredY:
                return drawText_color( x, y + (h/2), size, color, text );

            case Position::alignRight:
                return drawText_color( x - w, y, size, color, text );

            case Position::alignTop:
                return drawText_color( x, y + h, size, color, text );

            case Position::alignTopRight:
                return drawText_color( x - w, y + h, size, color, text );

            
        }
    }

    void drawTextf_color_position( Position p, int x, int y, unsigned int size, unsigned int color, const char *text, ... )
    {
        char buf[1024];
        va_list argptr;

        va_start( argptr, text );
        vsnprintf( buf, sizeof(buf), text, argptr );
        va_end( argptr );

        return drawText_color_position( p, x, y, size, color, buf );
    }
}


