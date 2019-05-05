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
        menuMove.load( ( pathSounds + "menuMove.wav" ).c_str() );
        ballHit.load( ( pathSounds + "ballHit.ogg" ).c_str() );
        levelFinish.load( ( pathSounds + "levelFinish.wav" ).c_str()  );
        menuMusic.load( ( pathSounds + "Puzzle-Dreams-3.ogg" ).c_str()  );
        levelMusic.load( ( pathSounds + "Good-Morning-Doctor-Weird.ogg" ).c_str()  );

        // Set options
        menuMusic.setLooping( 1 );
        levelMusic.setLooping( 1 );
    }
}
