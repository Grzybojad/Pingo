#include <psp2/audioout.h>
#include "soloud.h"
#include "soloud_wav.h"

namespace Sound
{
    // SoLoud engine
    extern SoLoud::Soloud soloud;

    // Sounds
    extern SoLoud::Wav menuMove;
    extern SoLoud::Wav ballHit;
    extern SoLoud::Wav levelFinish;

    extern void initSoloud();
    extern void loadSounds();
}
