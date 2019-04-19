#include "texture.hpp"

namespace Texture {
    vita2d_texture *wallTexture;
    vita2d_texture *floorBlankTexture;
    vita2d_texture *floorPaintedTexture;
    vita2d_texture *ballTexture;
    vita2d_texture *background1Texture;

    void loadTextures()
    {
        wallTexture         = vita2d_load_PNG_file( "app0:/img/level/wall.png" );
        floorBlankTexture   = vita2d_load_PNG_file( "app0:/img/level/floorBlank.png" );
        floorPaintedTexture = vita2d_load_PNG_file( "app0:/img/level/floorPainted.png" );
        //ballTexture         = vita2d_load_PNG_file( "app0:/img/level/ball.png" );

        background1Texture  = vita2d_load_PNG_file( "app0:/img/common/background1.png" );
    }

    vita2d_texture * getTexture( Sprite sprite )
    {
        switch( sprite )
        {
            case Sprite::wall:
                return wallTexture;
        
            case Sprite::floorBlank:
                return floorBlankTexture;

            case Sprite::floorPainted:
                return floorPaintedTexture;

            case Sprite::background1:
                return background1Texture;

            default:
                break;
        }

        return NULL;
    }

    void drawTexture( Sprite sprite, Vec2 pos )
    {
        // TODO change this to just use getTexture()

        switch( sprite )
        {
            case Sprite::wall:
                vita2d_draw_texture_scale( wallTexture, pos.x, pos.y, 0.25, 0.25 );
                break;
        
            case Sprite::floorBlank:
                vita2d_draw_texture_scale( floorBlankTexture, pos.x, pos.y, 0.25, 0.25 );
                break;

            case Sprite::floorPainted:
                vita2d_draw_texture_scale( floorPaintedTexture, pos.x, pos.y, 0.5, 0.5 );
                break;

            case Sprite::background1:
                vita2d_draw_texture_scale( background1Texture, pos.x, pos.y, 1, 1 );
                break;

            default:
                break;
        }
    }

    void drawTexture_fillScreen( Sprite sprite )
    {
        int textureHeight = vita2d_texture_get_height(  getTexture( sprite ) );
        int textureWidth = vita2d_texture_get_height(  getTexture( sprite ) );
        int rows = ceil( SCREEN_HEIGHT / textureHeight );
        int columns = ceil( SCREEN_WIDTH / textureWidth );

        for( int i = 0; i <= columns; ++i )
        {
            for( int j = 0; j <= rows; ++j )
            {
                drawTexture( sprite, Vec2( i * textureWidth, j * textureHeight ) );
            }
        }
    }
}
