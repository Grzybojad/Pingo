#pragma once

#include <psp2/ctrl.h>
#include <psp2/kernel/processmgr.h>

#include <vita2d.h>

#include "input.hpp"
#include "menu.hpp"
#include "level.hpp"
#include "ball.hpp"
#include "gui.hpp"
#include "debug.hpp"
#include "common.hpp"

class Game
{
    public:
        Game();
        ~Game();

        void start();

    private:
        void loop();
        void draw();

        enum class GameState
        {
            exiting = -1,
            initialized = 0,
            mainMenu = 1,
            playing = 2,
            paused = 3
        };
        GameState gameState;

        Level level1;
};