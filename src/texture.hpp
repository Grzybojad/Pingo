#pragma once

#include <math.h>

#include <vita2d.h>

#include "gui.hpp" // DEBUG
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

        background1 = 11,
        background2 = 12,
        background3 = 13,

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
        doorStar1 = 32,
        doorStar2 = 33,
        doorStar3 = 34
    };

    vita2d_texture * getTexture( Sprite sprite );

    void drawTexture( Sprite sprite, Vec2 pos );
    void drawTexture_fillScreen( Sprite sprite );

    void freeTextures();

    extern vita2d_texture *wallTexture;
    extern vita2d_texture *floorBlankTexture;
    extern vita2d_texture *floorPaintedTexture;
    extern vita2d_texture *ballTexture;

    extern vita2d_texture *background1Texture;
    extern vita2d_texture *background2Texture;
    extern vita2d_texture *background3Texture;

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
    extern vita2d_texture *doorStar1Texture;
    extern vita2d_texture *doorStar2Texture;
    extern vita2d_texture *doorStar3Texture;
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