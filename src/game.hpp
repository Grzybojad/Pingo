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
#include "sound.hpp"
#include "timer.hpp"
#include "stats.hpp"
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
        void initCustomLevelList();
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
            paused = 4,
            optionsMenu = 5
        };
        GameState gameState;

        MainMenu mainMenu;
        std::vector<LevelSelect> levelMenus;
        PauseMenu pauseMenu;
        LevelFinish finishMenu;
        OptionsMenu optionsMenu;

        Level level;
        std::vector<LevelList> levelListList;
        int selectedLevelList;

        AnimatedBackground background;
        Curtain curtain;

        Timer gameTime;

        bool progressSaved;
        bool finishMessage; // All levels finished message box
        bool gameComplete;  // Game complete message box
};