#pragma once

#include <string>
#include <vector>
#include <fstream>

#include "ball.hpp"
#include "timer.hpp"
#include "common.hpp"

#include "gui.hpp"

class Tile
{
    public:
        Tile();

        virtual void draw( Rect rect );

    protected:

};

class Level
{
    public:
        Level();

        void loadFromFile( std::string file );

        void update();
        void draw();

    protected:
        std::vector< std::vector<Tile*> > tiles;
        Timer levelTime;
        int tileSize;

        Ball ball;

        Tile* charToTile( char c );
        Vec2 getWorldPosFromTilePos( Vec2 tilePos );
        void initBall();

        // Check if rects collide
        bool checkCollision( Rect a, Rect b );

        // Is the ball hitting a wall?
        bool ballHittingWall();
};

class WallTile : public Tile
{
    public:
        using Tile::Tile;

        void draw( Rect rect ) override;

    protected:

};

class FloorTile : public Tile
{
    public:
        using Tile::Tile;

        void draw( Rect rect ) override;

    protected:
        enum class State
        {
            blank = 0,
            painted = 1
        };
        State state;

        void paint();
};

class StartTile : public FloorTile
{
    public:
        using FloorTile::FloorTile;
};