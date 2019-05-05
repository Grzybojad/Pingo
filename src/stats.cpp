#include "stats.hpp"

namespace Stats
{
    int timePlayed;
    int totalSteps;
    int totalLevelFinished;

    void readStats()
    {
        std::ifstream stats;
        stats.open( pathData + "stats.txt", std::ifstream::in );

        if( !stats.fail() )
        {
            stats >> timePlayed;
            stats >> totalSteps;
            stats >> totalLevelFinished;
        }
        else
        {
            timePlayed = 0;
            totalSteps = 0;
            totalLevelFinished = 0;
        }

        stats.close();
    }

    void saveStats()
    {
        std::ofstream stats;
        stats.open( pathData + "stats.txt" );

        stats << timePlayed << "\n";
        stats << totalSteps << "\n";
        stats << totalLevelFinished;

        stats.close();
    }
}