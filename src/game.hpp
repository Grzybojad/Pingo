#pragma once

#include <vector>
#include <string>

#include <psp2/ctrl.h>
#include <psp2/kernel/processmgr.h>
#include <psp2/io/dirent.h>
#include <vita2d.h>

#include "input.hpp"
#include "menu.hpp"
#include "level.hpp"
#include "ball.hpp"
#include "gui.hpp"
#include "debug.hpp"
#include "sound.hpp"
#include "common.hpp"

class Game
{
    public:
        Game();
        ~Game();

        void mainLoop();

    private:
        void inGame();
        void inMenu();
        
        void initLevelList();
        void initLevel();
        void initLevel( int levelIndex );
        void destroyLevel();

        void draw();

        void exit();

        enum class GameState
        {
            exiting = -1,
            initialized = 0,
            mainMenu = 1,
            levelMenu = 2,
            playing = 3,
            paused = 4
        };
        GameState gameState;

        MainMenu mainMenu;
        LevelSelect levelMenu;
        PauseMenu pauseMenu;
        LevelFinish finishMenu;

        Level level;

        LevelList levelList;

        AnimatedBackground background;

        Curtain curtain;

        bool progressSaved;

        // All levels finished message box
        bool finishMessage;

        // Game complete message box
        bool gameComplete;
        //bool alreadyShowedCompleteMessage;
};