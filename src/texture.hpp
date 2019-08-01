#pragma once

#include <math.h>

#include <vita2d.h>

#include "common.hpp"

namespace Texture
{
    void loadTextures();

    enum class Sprite
    {
        wall,
        floorBlank,
        floorPainted,
        ball,
        wallFill,
        stop,
        paintBlob,
        floorEmpty,
        conveyorBlank,
        conveyorPainted,

        restartButton,
        pauseButton,

        background1,
        background2,
        background3,
        
        star,
        messageBox,
        back,

        logo,
        startButton,
        startSelected,
        levelSelectButton,
        levelSelectSelected,
        optionsButton,
        optionsSelected,

        doorClosed,
        doorOpened,
        doorLocked,
        doorLockedOutline,
        doorPlatform,
        headerWorld,
        header1,
        header2,

        lf_levelComplete,
        lf_nextLevel,
        lf_nextLevelSelected,
        lf_restart,
        lf_restartSelected,
        lf_menu,
        lf_menuSelected,

        p_pausedText,
        p_return,
        p_returnSelected,
        p_restart,
        p_restartSelected,
        p_menu,
        p_menuSelected,

        o_header,
        o_music,
        o_musicOn,
        o_sfx,
        o_sfxOn,
        o_touch,
        o_touchOn,
        o_stats,
        o_checkboxOff,
        o_checkboxOn,
        o_sliderOff,
        o_sliderOn,

        underConstruction,

        curtain
    };

    vita2d_texture * getTexture( Sprite sprite );

    void drawTexture( Sprite sprite, Vec2 pos );
    void drawTexture( Sprite sprite, int x, int y );
    void drawTexture( Sprite sprite );
    void drawTexture_rotate( Sprite sprite, Vec2 pos, float rad );
    void drawTexture_tint( Sprite sprite, Vec2 pos, unsigned int color );
    void drawTexture_scale( Sprite sprite, Vec2 pos, float scale );
    void drawTexture_tint_scale( Sprite sprite, Vec2 pos, unsigned int color, float scale );
    void drawTexture_fillScreen( Sprite sprite );
    void drawWall( int x, int y, int face );

    void drawTexture_sliced( Sprite sprite, Vec2 pos, float slice );
    void drawTexture_rotate_sliced( Sprite sprite, Vec2 pos, float rad, float slice );

    void freeTextures();

    extern vita2d_texture *wallTexture;
    extern vita2d_texture *floorBlankTexture;
    extern vita2d_texture *floorPaintedTexture;
    extern vita2d_texture *ballTexture;
    extern vita2d_texture *wallFillTexture;
    extern vita2d_texture *stopTexture;
    extern vita2d_texture *paintBlobTexture;
    extern vita2d_texture *floorEmptyTexture;
    extern vita2d_texture *conveyorBlankTexture;
    extern vita2d_texture *conveyorPaintedTexture;

    extern vita2d_texture *restartButtonTexture;
    extern vita2d_texture *pauseButtonTexture;

    extern vita2d_texture *background1Texture;
    extern vita2d_texture *background2Texture;
    extern vita2d_texture *background3Texture;
    extern vita2d_texture *starTexture;
    extern vita2d_texture *messageBoxTexture;
    extern vita2d_texture *backTexture;

    extern vita2d_texture *logoTexture;
    extern vita2d_texture *startButtonTexture;
    extern vita2d_texture *startSelectedTexture;
    extern vita2d_texture *levelSelectButtonTexture;
    extern vita2d_texture *levelSelectSelectedTexture;
    extern vita2d_texture *optionsButtonTexture;
    extern vita2d_texture *optionsSelectedTexture;

    extern vita2d_texture *doorClosedTexture;
    extern vita2d_texture *doorOpenedTexture;
    extern vita2d_texture *doorLockedTexture;
    extern vita2d_texture *doorLockedOutlineTexture;
    extern vita2d_texture *doorPlatformTexture;
    extern vita2d_texture *headerWorldTexture;
    extern vita2d_texture *header1Texture;
    extern vita2d_texture *header2Texture;

    extern vita2d_texture *lf_levelCompleteTexture;
    extern vita2d_texture *lf_nextLevelTexture;
    extern vita2d_texture *lf_nextLevelSelectedTexture;
    extern vita2d_texture *lf_restartTexture;
    extern vita2d_texture *lf_restartSelectedTexture;
    extern vita2d_texture *lf_menuTexture;
    extern vita2d_texture *lf_menuSelectedTexture;

    extern vita2d_texture *p_pausedTextTexture;
    extern vita2d_texture *p_returnTexture;
    extern vita2d_texture *p_returnSelectedTexture;
    extern vita2d_texture *p_restartTexture;
    extern vita2d_texture *p_restartSelectedTexture;
    extern vita2d_texture *p_menuTexture;
    extern vita2d_texture *p_menuSelectedTexture;

    extern vita2d_texture *o_headerTexture;
    extern vita2d_texture *o_musicTexture;
    extern vita2d_texture *o_musicOnTexture;
    extern vita2d_texture *o_sfxTexture;
    extern vita2d_texture *o_sfxOnTexture;
    extern vita2d_texture *o_touchTexture;
    extern vita2d_texture *o_touchOnTexture;
    extern vita2d_texture *o_statsTexture;
    extern vita2d_texture *o_checkboxOffTexture;
    extern vita2d_texture *o_checkboxOnTexture;
    extern vita2d_texture *o_sliderOffTexture;
    extern vita2d_texture *o_sliderOnTexture;

    extern vita2d_texture *underConstructionTexture;

    extern vita2d_texture *curtainTexture;
};


class AnimatedBackground
{
    public:
        AnimatedBackground();

        void update();
        void draw();

    protected:
        float animationStep;
        float animationLength;
        float animationSpeed;

        int variant;
};

class Curtain
{
    public:
        Curtain();

        void update();
        void draw();

    protected:
        float animationStep;
        float animationSpeed;
        float waitTimer;
};