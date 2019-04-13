#pragma once

#include "input.hpp"
#include "common.hpp"

//DEBUG
#include "gui.hpp"

#include <vita2d.h>

class Ball
{
    public:
        Ball();
        ~Ball();

        //void setTilePos( Vec2 spawnTile );
        void setWorldPos( Vec2 worldPos );
        Vec2 getWorldPos();
        void handleInput();
        void move();
        void moveBack();
        void draw();

        void stop();

        Rect getRect();

        enum class State
        {
            stationary = 0,
            movingUp = 1,
            movingRight = 2,
            movingDown = 3,
            movingLeft = 4
        };
        State state;

    protected:
        Vec2 worldPos;
        //Vec2 tilePos;
        Vec2 tilePosOffset;

        double ballSpeed;
        int tileSize;

        void moveUp();
        void moveRight();
        void moveDown();
        void moveLeft();
};