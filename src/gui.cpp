#include "gui.hpp"

namespace Gui
{
    float FONT_SCALE = 1.0;
    vita2d_font *mainFont[ 99 ];
    unsigned int MAIN_FONT_COLOR = RGBA8( 0, 0, 0, 255 );
    std::string debugText = "";


    void loadFont()
    {
        for( int i = 0; i <= 99; ++i )
            mainFont[ i ] = vita2d_load_font_file( "app0:/font/ConcertOne-Regular.ttf" );
    }

    void freeFont()
    {
        for( int i = 0; i <= 99; ++i )
            vita2d_free_font( mainFont[ i ] );
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

            case Position::centeredTop:
                return drawText( x - (w/2), y + h, size, text );

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

            case Position::centeredTop:
                return drawText_color( x - (w/2), y + h, size, color, text );

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


    void drawMessageBox( const char *header, const char *body )
    {
        Rect boxRect = Rect();
        boxRect.w = vita2d_texture_get_width( Texture::getTexture( Texture::Sprite::messageBox ) );
        boxRect.h = vita2d_texture_get_height( Texture::getTexture( Texture::Sprite::messageBox ) );
        boxRect.x = ( SCREEN_WIDTH - boxRect.w ) / 2;
        boxRect.y = ( SCREEN_HEIGHT - boxRect.h ) / 2;

        int headerSize = 40;
        int bodySize = 25;
        int footerSize = 20;

        //vita2d_draw_rectangle( boxRect.x, boxRect.y, boxRect.w, boxRect.h, RGBA8( 140, 140, 180, 255 ) );
        Texture::drawTexture( Texture::Sprite::messageBox, Vec2( boxRect.x, boxRect.y ) );

        drawText_color_position( Position::centered, SCREEN_WIDTH / 2, boxRect.y + 90, headerSize, RGBA8( 70, 70, 125, 255 ), header );

        int bodyHeight = vita2d_font_text_height( mainFont[ (int)(bodySize * FONT_SCALE) ], bodySize, body );
        drawText_color_position( Position::centeredX, SCREEN_WIDTH / 2, boxRect.y + ( ( boxRect.h - bodyHeight ) / 2 ) + 20, bodySize, RGBA8( 70, 70, 125, 255 ), body );

        drawText_color_position( Position::centered, SCREEN_WIDTH / 2, boxRect.y + boxRect.h - 100, footerSize, RGBA8( 70, 70, 125, 255 ), "Press X to close this message" );
    }


    int getTextWidth( unsigned int size, const char *text )
    {
        return vita2d_font_text_width( mainFont[ (int)(size * FONT_SCALE) ], size, text );
    }

    int getTextHeight( unsigned int size, const char *text )
    {
        return vita2d_font_text_height( mainFont[ (int)(size * FONT_SCALE) ], size, text );
    }


    void drawDebugText()
    {
        if( debugText != "" )
        {
            int textSize = 20;
            Rect box;
            int charWidth = vita2d_font_text_width( mainFont[ (int)(textSize * FONT_SCALE) ], (int)(textSize * FONT_SCALE), "A" );
            box.w = debugText.length() * charWidth + 20;
            box.h = textSize + 10;

            box.x = SCREEN_WIDTH - box.w;
            box.y = SCREEN_HEIGHT - box.h;

            vita2d_draw_rectangle( box.x, box.y, box.w, box.h, RGBA8( 0, 0, 0, 255 ) );

            drawText_color_position( Position::centered, box.x + ( box.w / 2 ), box.y + ( box.h / 2 ), textSize, RGBA8( 0, 255, 0, 255 ), debugText.c_str() );
        }
    }
}