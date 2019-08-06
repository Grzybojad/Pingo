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
#include "credits.hpp"
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
        void inCredits();
        
        void initLevelList();
        void initCustomLevelList();
        void initLevel();
        void initLevel( int levelIndex );
        void destroyLevel();

        void draw();

        void exit();

        void playLevelMusic();

        enum class GameState
        {
            exiting,
            initialized,
            mainMenu,
            levelMenu,
            playing,
            paused,
            optionsMenu,
            credits
        };
        GameState gameState;

        MainMenu mainMenu;
        std::vector<LevelSelect> levelMenus;
        PauseMenu pauseMenu;
        LevelFinish finishMenu;
        OptionsMenu optionsMenu;

        Level level;
        std::vector<LevelList> levelListList;
        const int nrOfWorlds = 2;
        int selectedLevelList;

        AnimatedBackground background;
        Curtain curtain;
        Credits credits;

        Timer gameTime;

        bool progressSaved;
};