#pragma once

#include <fstream>

#include "common.hpp"

namespace Stats
{
    extern int timePlayed; // Recorded in seconds
    extern int totalSteps;
    extern int totalLevelFinished; // How many times the player has finished a level;

    void readStats();
    void saveStats();
}