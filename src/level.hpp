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
        virtual void paint();

        // Can the tile be painted?
        virtual bool paintable();

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
        enum class State
        {
            notStarted = 0,
            playing = 1,
            finished
        };
        State state;

        std::vector< std::vector<Tile*> > tiles;
        Timer levelTime;
        int tileSize;
        int floorTileCount;
        int paintedTiles;

        Ball ball;

        // Converts the char that's loaded from the level map to the corresponding Tile type
        Tile* charToTile( char c );

        // Converts tile position in the level to the world (screen) position
        Vec2 getWorldPosFromTilePos( Vec2 tilePos );

        // Returns the tile the ball is on
        Vec2 getBallTile();

        // Returns the world (screen) position of the tile the ball is on
        Vec2 getBallTilePosition();

        // Initializes the ball starting position
        void initBall();

        // Check if rects collide
        bool checkCollision( Rect a, Rect b );

        // Is the ball hitting a wall?
        bool ballHittingWall();

        // Paint the tile the ball is on
        void paintTile();

        // Count how many floor tiles are in the level
        int countFloorTiles();

        // Check if the win condition was met
        bool checkWinCondition();
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

        void paint() override;
        bool paintable() override;
};

class StartTile : public FloorTile
{
    public:
        using FloorTile::FloorTile;
};