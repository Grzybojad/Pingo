#pragma once

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

        background1 = 4,
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
};