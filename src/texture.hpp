#pragma once

#include <math.h>

#include <vita2d.h>

#include "common.hpp"

namespace Texture
{
    void loadTextures();

    enum class Sprite
    {
        wall = 0,
        floorBlank = 1,
        floorPainted = 2,
        ball = 3,
        wallFill = 4,
        stop = 5,
        paintBlob = 6,
        floorEmpty = 7,

        background1 = 11,
        background2 = 12,
        background3 = 13,
        
        star = 14,
        messageBox = 15,

        logo = 21,
        startButton = 22,
        startSelected = 23,
        levelSelectButton = 24,
        levelSelectSelected = 25,
        optionsButton = 26,
        optionsSelected = 27,

        doorClosed = 28,
        doorOpened = 29,
        doorLocked = 30,
        doorLockedOutline = 31,
        doorPlatform = 35,

        lf_levelComplete = 41,
        lf_nextLevel = 42,
        lf_nextLevelSelected = 43,
        lf_restart = 44,
        lf_restartSelected = 45,
        lf_menu = 46,
        lf_menuSelected = 47,

        p_pausedText = 51,
        p_return = 52,
        p_returnSelected = 53,
        p_restart = 54,
        p_restartSelected = 55,
        p_menu = 56,
        p_menuSelected = 57,

        underConstruction = 60,

        curtain = 100
    };

    vita2d_texture * getTexture( Sprite sprite );

    void drawTexture( Sprite sprite, Vec2 pos );
    void drawTexture_scale( Sprite sprite, Vec2 pos, float scale );
    void drawTexture_fillScreen( Sprite sprite );
    void drawWall( int x, int y, int face );

    void freeTextures();

    extern vita2d_texture *wallTexture;
    extern vita2d_texture *floorBlankTexture;
    extern vita2d_texture *floorPaintedTexture;
    extern vita2d_texture *ballTexture;
    extern vita2d_texture *wallFillTexture;
    extern vita2d_texture *stopTexture;
    extern vita2d_texture *paintBlobTexture;
    extern vita2d_texture *floorEmptyTexture;

    extern vita2d_texture *background1Texture;
    extern vita2d_texture *background2Texture;
    extern vita2d_texture *background3Texture;
    extern vita2d_texture *starTexture;
    extern vita2d_texture *messageBoxTexture;

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