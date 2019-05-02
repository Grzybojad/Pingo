#pragma once

#include <string>
#include <vector>
#include <fstream>

#include <psp2/io/stat.h> 

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
        Timer levelTime;
        int tileSize;
        int floorTileCount;
        int paintedTiles;
        int steps;
        bool shouldPlaySound;

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
        void saveProgress();
        void loadProgress();

    private:
        std::vector< LevelListElement > levels;
        int currentLevel;
};
