#include "texture.hpp"

namespace Texture {
    vita2d_texture *wallTexture;
    vita2d_texture *floorBlankTexture;
    vita2d_texture *floorPaintedTexture;
    vita2d_texture *ballTexture;
    vita2d_texture *background1Texture;
    vita2d_texture *background2Texture;
    vita2d_texture *background3Texture;
    vita2d_texture *starTexture;
    vita2d_texture *logoTexture;
    vita2d_texture *startButtonTexture;
    vita2d_texture *startSelectedTexture;
    vita2d_texture *levelSelectButtonTexture;
    vita2d_texture *levelSelectSelectedTexture;
    vita2d_texture *optionsButtonTexture;
    vita2d_texture *optionsSelectedTexture;
    vita2d_texture *doorClosedTexture;
    vita2d_texture *doorOpenedTexture;
    vita2d_texture *doorLockedTexture;
    vita2d_texture *doorLockedOutlineTexture;
    vita2d_texture *doorStar1Texture;
    vita2d_texture *doorStar2Texture;
    vita2d_texture *doorStar3Texture;
    vita2d_texture *doorPlatformTexture;
    vita2d_texture *lf_levelCompleteTexture;
    vita2d_texture *lf_nextLevelTexture;
    vita2d_texture *lf_nextLevelSelectedTexture;
    vita2d_texture *lf_restartTexture;
    vita2d_texture *lf_restartSelectedTexture;
    vita2d_texture *lf_menuTexture;
    vita2d_texture *lf_menuSelectedTexture;
    vita2d_texture *p_pausedTextTexture;
    vita2d_texture *p_returnTexture;
    vita2d_texture *p_returnSelectedTexture;
    vita2d_texture *p_restartTexture;
    vita2d_texture *p_restartSelectedTexture;
    vita2d_texture *p_menuTexture;
    vita2d_texture *p_menuSelectedTexture;

    void loadTextures()
    {
        wallTexture         = vita2d_load_PNG_file( "app0:/img/level/wall.png" );
        floorBlankTexture   = vita2d_load_PNG_file( "app0:/img/level/floorBlank.png" );
        floorPaintedTexture = vita2d_load_PNG_file( "app0:/img/level/floorPainted.png" );
        ballTexture         = vita2d_load_PNG_file( "app0:/img/level/ball.png" );

        background1Texture  = vita2d_load_PNG_file( "app0:/img/common/background1.png" );
        background2Texture  = vita2d_load_PNG_file( "app0:/img/common/background2.png" );
        background3Texture  = vita2d_load_PNG_file( "app0:/img/common/background3.png" );

        starTexture         = vita2d_load_PNG_file( "app0:/img/common/star.png" );

        logoTexture                 = vita2d_load_PNG_file( "app0:/img/menu/logo.png" );
        startButtonTexture          = vita2d_load_PNG_file( "app0:/img/menu/startButton.png" );
        startSelectedTexture        = vita2d_load_PNG_file( "app0:/img/menu/startSelected.png" );
        levelSelectButtonTexture    = vita2d_load_PNG_file( "app0:/img/menu/levelSelectButton.png" );
        levelSelectSelectedTexture  = vita2d_load_PNG_file( "app0:/img/menu/levelSelectSelected.png" );
        optionsButtonTexture        = vita2d_load_PNG_file( "app0:/img/menu/optionsButton.png" );
        optionsSelectedTexture      = vita2d_load_PNG_file( "app0:/img/menu/optionsSelected.png" );

        doorClosedTexture           = vita2d_load_PNG_file( "app0:/img/menu/doorClosed.png" );
        doorOpenedTexture           = vita2d_load_PNG_file( "app0:/img/menu/doorOpened.png" );
        doorLockedTexture           = vita2d_load_PNG_file( "app0:/img/menu/doorLocked.png" );
        doorLockedOutlineTexture    = vita2d_load_PNG_file( "app0:/img/menu/doorLockedOutline.png" );
        doorStar1Texture            = vita2d_load_PNG_file( "app0:/img/menu/doorStar1.png" );
        doorStar2Texture            = vita2d_load_PNG_file( "app0:/img/menu/doorStar2.png" );
        doorStar3Texture            = vita2d_load_PNG_file( "app0:/img/menu/doorStar3.png" );
        doorPlatformTexture         = vita2d_load_PNG_file( "app0:/img/menu/doorPlatform.png" );

        lf_levelCompleteTexture     = vita2d_load_PNG_file( "app0:/img/menu/lf-levelComplete.png" );
        lf_nextLevelTexture         = vita2d_load_PNG_file( "app0:/img/menu/lf-nextLevel.png" );
        lf_nextLevelSelectedTexture = vita2d_load_PNG_file( "app0:/img/menu/lf-nextLevelSelected.png" );
        lf_restartTexture           = vita2d_load_PNG_file( "app0:/img/menu/lf-restart.png" );
        lf_restartSelectedTexture   = vita2d_load_PNG_file( "app0:/img/menu/lf-restartSelected.png" );
        lf_menuTexture              = vita2d_load_PNG_file( "app0:/img/menu/lf-menu.png" );
        lf_menuSelectedTexture      = vita2d_load_PNG_file( "app0:/img/menu/lf-menuSelected.png" );

        p_pausedTextTexture         = vita2d_load_PNG_file( "app0:/img/menu/pause/pausedText.png" );
        p_returnTexture             = vita2d_load_PNG_file( "app0:/img/menu/pause/return.png" );
        p_returnSelectedTexture     = vita2d_load_PNG_file( "app0:/img/menu/pause/returnSelected.png" );
        p_restartTexture            = vita2d_load_PNG_file( "app0:/img/menu/pause/restart.png" );
        p_restartSelectedTexture    = vita2d_load_PNG_file( "app0:/img/menu/pause/restartSelected.png" );
        p_menuTexture               = vita2d_load_PNG_file( "app0:/img/menu/pause/menu.png" );
        p_menuSelectedTexture       = vita2d_load_PNG_file( "app0:/img/menu/pause/menuSelected.png" );
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

            case Sprite::ball:
                return ballTexture;

            case Sprite::background1:
                return background1Texture;

            case Sprite::background2:
                return background2Texture;

            case Sprite::background3:
                return background3Texture;

            case Sprite::star:
                return starTexture;

            case Sprite::logo:
                return logoTexture;

            case Sprite::startButton:
                return startButtonTexture;

            case Sprite::startSelected:
                return startSelectedTexture;

            case Sprite::levelSelectButton:
                return levelSelectButtonTexture;

            case Sprite::levelSelectSelected:
                return levelSelectSelectedTexture;

            case Sprite::optionsButton:
                return optionsButtonTexture;

            case Sprite::optionsSelected:
                return optionsSelectedTexture;

            case Sprite::doorClosed:
                return doorClosedTexture;

            case Sprite::doorOpened:
                return doorOpenedTexture;

            case Sprite::doorLocked:
                return doorLockedTexture;

            case Sprite::doorLockedOutline:
                return doorLockedOutlineTexture;

            case Sprite::doorStar1:
                return doorStar1Texture;

            case Sprite::doorStar2:
                return doorStar2Texture;

            case Sprite::doorStar3:
                return doorStar3Texture;

            case Sprite::doorPlatform:
                return doorPlatformTexture;

            case Sprite::lf_levelComplete:
                return lf_levelCompleteTexture;
                
            case Sprite::lf_nextLevel:
                return lf_nextLevelTexture;
            
            case Sprite::lf_nextLevelSelected:
                return lf_nextLevelSelectedTexture;
            
            case Sprite::lf_restart:
                return lf_restartTexture;
            
            case Sprite::lf_restartSelected:
                return lf_restartSelectedTexture;

            case Sprite::lf_menu:
                return lf_menuTexture;
            
            case Sprite::lf_menuSelected:
                return lf_menuSelectedTexture;

            case Sprite::p_pausedText:
                return p_pausedTextTexture;

            case Sprite::p_return:
                return p_returnTexture;

            case Sprite::p_returnSelected:
                return p_returnSelectedTexture;

            case Sprite::p_restart:
                return p_restartTexture;

            case Sprite::p_restartSelected:
                return p_restartSelectedTexture;

            case Sprite::p_menu:
                return p_menuTexture;

            case Sprite::p_menuSelected:
                return p_menuSelectedTexture;

            default:
                break;
        }

        return NULL;
    }

    void drawTexture( Sprite sprite, Vec2 pos )
    {
        vita2d_draw_texture( getTexture( sprite ), pos.x, pos.y );
    }

    void drawTexture_scale( Sprite sprite, Vec2 pos, float scale )
    {
        vita2d_draw_texture_scale( getTexture( sprite ), pos.x, pos.y, scale, scale );
    }

    void drawTexture_fillScreen( Sprite sprite )
    {
        int textureHeight = vita2d_texture_get_height( getTexture( sprite ) );
        int textureWidth = vita2d_texture_get_height( getTexture( sprite ) );
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

    void freeTextures()
    {
        vita2d_free_texture( wallTexture );
        vita2d_free_texture( floorBlankTexture );
        vita2d_free_texture( floorPaintedTexture );
        vita2d_free_texture( ballTexture );
        vita2d_free_texture( background1Texture );
        vita2d_free_texture( background2Texture );
        vita2d_free_texture( background3Texture );
        vita2d_free_texture( logoTexture );
        vita2d_free_texture( startButtonTexture );
        vita2d_free_texture( startSelectedTexture );
        vita2d_free_texture( levelSelectButtonTexture );
        vita2d_free_texture( levelSelectSelectedTexture );
        vita2d_free_texture( optionsButtonTexture );
        vita2d_free_texture( optionsSelectedTexture );
        vita2d_free_texture( doorClosedTexture );
        vita2d_free_texture( doorOpenedTexture );
        vita2d_free_texture( doorLockedTexture );
        vita2d_free_texture( doorLockedOutlineTexture );
        vita2d_free_texture( doorStar1Texture );
        vita2d_free_texture( doorStar2Texture );
        vita2d_free_texture( doorStar3Texture );
        vita2d_free_texture( lf_levelCompleteTexture );
        vita2d_free_texture( lf_nextLevelTexture );
        vita2d_free_texture( lf_nextLevelSelectedTexture );
        vita2d_free_texture( lf_restartTexture );
        vita2d_free_texture( lf_restartSelectedTexture );
        vita2d_free_texture( lf_menuTexture );
        vita2d_free_texture( lf_menuSelectedTexture );
    }
}


AnimatedBackground::AnimatedBackground()
{
    animationStep = 0;
    animationLength = -1;
    animationSpeed = 0.35f;

    variant = rand() % 3 + 1;
}

void AnimatedBackground::update()
{
    if( animationLength == -1 )
        animationLength = vita2d_texture_get_width( Texture::getTexture( Texture::Sprite::background1 ) );

    animationStep += animationSpeed * timestep;

    if( animationStep > animationLength )
        animationStep -= animationLength;
}

void AnimatedBackground::draw()
{
    int textureHeight = vita2d_texture_get_height( Texture::getTexture( Texture::Sprite::background1 ) );
    int textureWidth = vita2d_texture_get_height( Texture::getTexture( Texture::Sprite::background1 ) );
    int rows = ceil( SCREEN_HEIGHT / textureHeight );
    int columns = ceil( SCREEN_WIDTH / textureWidth );

    for( int i = -1; i <= columns; ++i )
    {
        for( int j = -1; j <= rows; ++j )
        {
            Texture::Sprite sprite;

            switch( variant )
            {
                case 1:
                    sprite = Texture::Sprite::background1;
                    break;
                case 2:
                    sprite = Texture::Sprite::background2;
                    break;
                case 3:
                    sprite = Texture::Sprite::background3;
                    break;
            }

            Texture::drawTexture( sprite, Vec2( i * textureWidth + animationStep, j * textureHeight + animationStep ) );
        }
    }
}