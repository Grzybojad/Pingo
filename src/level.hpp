#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <cmath>

#include <psp2/io/stat.h> 
#include <vita2d.h>

#include "ball.hpp"
#include "timer.hpp"
#include "gui.hpp"
#include "texture.hpp"
#include "sound.hpp"
#include "stats.hpp"
#include "common.hpp"


// Farward class declarations
class LevelListElement;
class LevelList;

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

        void firstInit();
        void init();
        void loadFromFile( LevelListElement *levelListElement );
        void unload();

        void update();
        void draw();

        bool complete();

        // Return the number of stars the player got for completing the level
        int getStarRating();

    protected:
        enum class State
        {
            notStarted = 0,
            playing = 1,
            finished
        };
        State state;

        Vec2 levelPosition;
        Vec2 levelSize;
        std::vector< std::vector<Tile*> > tiles;
        LevelListElement *levelListElement;
        vita2d_texture* levelTexture;
        Timer levelTime;
        int tileSize;
        int floorTileCount;
        int paintedTiles;
        int steps;
        bool shouldPlaySound;

        Ball ball;
        Vec2 previousBallPos;


        // Initialize level texture from tiles
        void initLevelTexture();

        // Paint the specified tile on the level texture (i = row, j = column)
        void paintTileOnTexture( int i, int j );

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

        // Is the ball on a stop tile?
        bool ballOnStop();

        // Paint the tile the ball is on
        void paintTile();

        // Count how many floor tiles are in the level
        int countFloorTiles();

        // Check if the win condition was met
        bool checkWinCondition();

        // Calculate and save the number of stars the player got for completing the level
        void setStarRating();
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

class DoubleFloorTile : public FloorTile
{
    public:
        using FloorTile::FloorTile;

        void draw( Rect rect ) override;

    protected:
        enum class State
        {
            blank = 0,
            paintedHalfway = 1,
            painted = 2
        };
        State state;

        void paint() override;
        bool paintable() override;
};

class StopTile : public FloorTile
{
    public:
        using FloorTile::FloorTile;

        void draw( Rect rect ) override;
};

class StartTile : public FloorTile
{
    public:
        using FloorTile::FloorTile;
};


class LevelListElement
{
    public:
        LevelListElement( std::string filePath );

        void drawLevelMenuElement( Vec2 pos, bool selected );

        bool unlocked;
        bool completed;
        std::string filePath;

        int index;
        std::string name;
        int stepsForTwoStars;
        int stepsForThreeStars;

        int stars;

    protected:
        float animation;
};

class LevelList
{
    public:
        LevelList();

        void add( std::string filePath );

        std::string getLevelPath( int index );
        bool getCompletion( int index );
        int getCurrentLevel();
        int getNrOfLevels();

        bool nextLevel();
        void setCurrentLevel( int index );
        int lastUnlockedLevel();
        void compleateCurrentLevel();

        LevelListElement * accessElement( int index );

        // Save and load progress
        void saveProgress( int levelList );
        void loadProgress( int levelList );

    private:
        std::vector< LevelListElement > levels;
        int currentLevel;
};
