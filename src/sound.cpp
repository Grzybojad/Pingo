#include "sound.hpp"

namespace Sound
{
    SoLoud::Soloud soloud;

    SoLoud::Wav menuMove;
    SoLoud::Wav ballHit;
    SoLoud::Wav levelFinish;
    SoLoud::Wav airLock;
    SoLoud::WavStream menuMusic;
    SoLoud::WavStream levelMusic;
    SoLoud::WavStream levelMusic2;
    SoLoud::WavStream levelMusic3;
    SoLoud::WavStream levelMusic4;
    SoLoud::WavStream creditsMusic;

    void initSoloud()
    {
        soloud.init();
    }

    void loadSounds()
    {
        // Load files
        menuMove.load( ( pathSounds + "menuMove.wav" ).c_str() );
        ballHit.load( ( pathSounds + "ballHit.ogg" ).c_str() );
        levelFinish.load( ( pathSounds + "levelFinish.wav" ).c_str() );
        airLock.load( ( pathSounds + "Air-lock.ogg" ).c_str() );
        menuMusic.load( ( pathSounds + "Puzzle-Dreams-3.ogg" ).c_str() );
        levelMusic.load( ( pathSounds + "Good-Morning-Doctor-Weird.ogg" ).c_str() );
        levelMusic2.load( ( pathSounds + "Puzzle-Caves.ogg" ).c_str() );
        levelMusic3.load( ( pathSounds + "Hypnotic-Puzzle3.ogg" ).c_str() );
        levelMusic4.load( ( pathSounds + "Rubiks-Dodecahedron.ogg" ).c_str() );
        creditsMusic.load( ( pathSounds + "8-Bit-Puzzler.ogg" ).c_str() );

        // Set options
        menuMusic.setLooping( 1 );
        levelMusic.setLooping( 1 );
        levelMusic2.setLooping( 1 );
        levelMusic3.setLooping( 1 );
        levelMusic4.setLooping( 1 );
    }

    void setSFXVolume( float volume )
    {
        menuMove.setVolume( volume );
        ballHit.setVolume( volume );
        levelFinish.setVolume( volume );
    }

    void setMusicVolume( float volume )
    {
        menuMusic.stop();

        menuMusic.setVolume( volume );
        levelMusic.setVolume( volume );
        levelMusic2.setVolume( volume );
        levelMusic3.setVolume( volume );
        levelMusic4.setVolume( volume );

        soloud.play( menuMusic );
    }

    void playLevelMusic( int version )
    {
        switch( version )
        {
            case 1:
                soloud.play( levelMusic );
                break;
            case 2:
                soloud.play( levelMusic2 );
                break;
            case 3:
                soloud.play( levelMusic3 );
                break;
            case 4:
                soloud.play( levelMusic4 );
                break;
            default:
                break;
        }
    }

    void stopLevelMusic()
    {
        levelMusic.stop();
        levelMusic2.stop();
        levelMusic3.stop();
        levelMusic4.stop();
    }
}
