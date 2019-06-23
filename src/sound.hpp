#pragma once

#include <string>

#include <psp2/audioout.h>
#include "soloud.h"
#include "soloud_wav.h"
#include "soloud_wavstream.h"

#include "common.hpp"
#include "timer.hpp"

namespace Sound
{
    // SoLoud engine
    extern SoLoud::Soloud soloud;

    // Sounds
    extern SoLoud::Wav menuMove;
    extern SoLoud::Wav ballHit;
    extern SoLoud::Wav levelFinish;

    extern SoLoud::WavStream menuMusic;
    extern SoLoud::WavStream levelMusic;

    extern void initSoloud();
    extern void loadSounds();

    extern void setSFXVolume( float volume );
    extern void setMusicVolume( float volume );
}
