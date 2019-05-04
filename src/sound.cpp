#include "sound.hpp"

namespace Sound
{
    SoLoud::Soloud soloud;

    SoLoud::Wav menuMove;
    SoLoud::Wav ballHit;
    SoLoud::Wav levelFinish;
    SoLoud::WavStream menuMusic;
    SoLoud::WavStream levelMusic;

    void initSoloud()
    {
        soloud.init();
    }

    void loadSounds()
    {
        // Load files
        menuMove.load( "app0:/sounds/menuMove.wav" );
        ballHit.load( "app0:/sounds/ballHit.ogg" );
        levelFinish.load( "app0:/sounds/levelFinish.wav" );
        menuMusic.load( "app0:/sounds/Puzzle-Dreams-3.ogg" );
        levelMusic.load( "app0:/sounds/Good-Morning-Doctor-Weird.ogg" );

        // Set options
        menuMusic.setLooping( 1 );
        levelMusic.setLooping( 1 );
    }
}
