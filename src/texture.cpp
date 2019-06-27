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
    vita2d_texture *messageBoxTexture;
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
    vita2d_texture *underConstructionTexture;
    vita2d_texture *curtainTexture;

    void loadTextures()
    {
        wallTexture         = vita2d_load_PNG_file( ( pathTexture + "level/wall.png" ).c_str() );
        floorBlankTexture   = vita2d_load_PNG_file( ( pathTexture + "level/floorBlank.png" ).c_str() );
        floorPaintedTexture = vita2d_load_PNG_file( ( pathTexture + "level/floorPainted.png" ).c_str() );
        ballTexture         = vita2d_load_PNG_file( ( pathTexture + "level/ball.png" ).c_str() );

        background1Texture  = vita2d_load_PNG_file( ( pathTexture + "common/background1.png" ).c_str() );
        background2Texture  = vita2d_load_PNG_file( ( pathTexture + "common/background2.png" ).c_str() );
        background3Texture  = vita2d_load_PNG_file( ( pathTexture + "common/background3.png" ).c_str() );

        starTexture         = vita2d_load_PNG_file( ( pathTexture + "common/star.png" ).c_str() );
        messageBoxTexture   = vita2d_load_PNG_file( ( pathTexture + "common/messageBox.png" ).c_str() );

        logoTexture                 = vita2d_load_PNG_file( ( pathTexture + "menu/main/logo.png" ).c_str() );
        startButtonTexture          = vita2d_load_PNG_file( ( pathTexture + "menu/main/startButton.png" ).c_str() );
        startSelectedTexture        = vita2d_load_PNG_file( ( pathTexture + "menu/main/startSelected.png" ).c_str() );
        levelSelectButtonTexture    = vita2d_load_PNG_file( ( pathTexture + "menu/main/levelSelectButton.png" ).c_str() );
        levelSelectSelectedTexture  = vita2d_load_PNG_file( ( pathTexture + "menu/main/levelSelectSelected.png" ).c_str() );
        optionsButtonTexture        = vita2d_load_PNG_file( ( pathTexture + "menu/main/optionsButton.png" ).c_str() );
        optionsSelectedTexture      = vita2d_load_PNG_file( ( pathTexture + "menu/main/optionsSelected.png" ).c_str() );

        doorClosedTexture           = vita2d_load_PNG_file( ( pathTexture + "menu/levelSelect/doorClosed.png" ).c_str() );
        doorOpenedTexture           = vita2d_load_PNG_file( ( pathTexture + "menu/levelSelect/doorOpened.png" ).c_str() );
        doorLockedTexture           = vita2d_load_PNG_file( ( pathTexture + "menu/levelSelect/doorLocked.png" ).c_str() );
        doorLockedOutlineTexture    = vita2d_load_PNG_file( ( pathTexture + "menu/levelSelect/doorLockedOutline.png" ).c_str() );
        doorPlatformTexture         = vita2d_load_PNG_file( ( pathTexture + "menu/levelSelect/doorPlatform.png" ).c_str() );

        lf_levelCompleteTexture     = vita2d_load_PNG_file( ( pathTexture + "menu/levelFinish/lf-levelComplete.png" ).c_str() );
        lf_nextLevelTexture         = vita2d_load_PNG_file( ( pathTexture + "menu/levelFinish/lf-nextLevel.png" ).c_str() );
        lf_nextLevelSelectedTexture = vita2d_load_PNG_file( ( pathTexture + "menu/levelFinish/lf-nextLevelSelected.png" ).c_str() );
        lf_restartTexture           = vita2d_load_PNG_file( ( pathTexture + "menu/levelFinish/lf-restart.png" ).c_str() );
        lf_restartSelectedTexture   = vita2d_load_PNG_file( ( pathTexture + "menu/levelFinish/lf-restartSelected.png" ).c_str() );
        lf_menuTexture              = vita2d_load_PNG_file( ( pathTexture + "menu/levelFinish/lf-menu.png" ).c_str() );
        lf_menuSelectedTexture      = vita2d_load_PNG_file( ( pathTexture + "menu/levelFinish/lf-menuSelected.png" ).c_str() );

        p_pausedTextTexture         = vita2d_load_PNG_file( ( pathTexture + "menu/pause/pausedText.png" ).c_str() );
        p_returnTexture             = vita2d_load_PNG_file( ( pathTexture + "menu/pause/return.png" ).c_str() );
        p_returnSelectedTexture     = vita2d_load_PNG_file( ( pathTexture + "menu/pause/returnSelected.png" ).c_str() );
        p_restartTexture            = vita2d_load_PNG_file( ( pathTexture + "menu/pause/restart.png" ).c_str() );
        p_restartSelectedTexture    = vita2d_load_PNG_file( ( pathTexture + "menu/pause/restartSelected.png" ).c_str() );
        p_menuTexture               = vita2d_load_PNG_file( ( pathTexture + "menu/pause/menu.png" ).c_str() );
        p_menuSelectedTexture       = vita2d_load_PNG_file( ( pathTexture + "menu/pause/menuSelected.png" ).c_str() );

        underConstructionTexture    = vita2d_load_PNG_file( ( pathTexture + "menu/underConstruction.png" ).c_str() );

        curtainTexture              = vita2d_load_PNG_file( "app0:/sce_sys/pic0.png" );
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

            case Sprite::messageBox:
                return messageBoxTexture;

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

            case Sprite::underConstruction:
                return underConstructionTexture;

            case Sprite::curtain:
                return curtainTexture;

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
        vita2d_free_texture( starTexture );
        vita2d_free_texture( messageBoxTexture );
        vita2d_free_texture( doorPlatformTexture );
        vita2d_free_texture( lf_levelCompleteTexture );
        vita2d_free_texture( lf_nextLevelTexture );
        vita2d_free_texture( lf_nextLevelSelectedTexture );
        vita2d_free_texture( lf_restartTexture );
        vita2d_free_texture( lf_restartSelectedTexture );
        vita2d_free_texture( lf_menuTexture );
        vita2d_free_texture( lf_menuSelectedTexture );
        vita2d_free_texture( p_menuSelectedTexture );
        vita2d_free_texture( p_menuTexture );
        vita2d_free_texture( p_pausedTextTexture );
        vita2d_free_texture( p_restartSelectedTexture );
        vita2d_free_texture( p_restartTexture );
        vita2d_free_texture( p_returnSelectedTexture );
        vita2d_free_texture( p_returnTexture );
        vita2d_free_texture( underConstructionTexture );
        vita2d_free_texture( curtainTexture );
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

Curtain::Curtain()
{
    animationStep = 0;
    animationSpeed = 10.0f;
    waitTimer = 50;
}

void Curtain::update()
{
    if( waitTimer > 0)
        waitTimer -= timestep;
    else
        if( animationStep < vita2d_texture_get_height( Texture::getTexture( Texture::Sprite::curtain ) ) )
            animationStep += animationSpeed * timestep;
}

void Curtain::draw()
{
    Texture::drawTexture( Texture::Sprite::curtain, Vec2( 0, (int)-animationStep ) );
}