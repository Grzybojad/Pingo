#include "sound.hpp"

namespace Sound
{
    SoLoud::Soloud soloud;

    SoLoud::Wav menuMove;
    SoLoud::Wav ballHit;
    SoLoud::Wav levelFinish;

    void initSoloud()
    {
        soloud.init();
    }

    void loadSounds()
    {
        menuMove.load( "app0:/sounds/menuMove.wav" );
        ballHit.load( "app0:/sounds/ballHit.ogg" );
        levelFinish.load( "app0:/sounds/levelFinish.wav" );
    }
}
