#include <DxLib.h>
#include "SoundLoader.h"

bool SoundLoader::Load(std::string soundName,bool loop)
{
    if (handles_.count(soundName) <= 0)
    {
        handles_[soundName] = { LoadSoundMem(soundName.c_str()),loop };
    }

    if (handles_[soundName].first <= -1)
    {
        // error
        return false;
    }
    return true;
}

void SoundLoader::Play(std::string soundName)
{
    // Ù°ÌßÄ¶
    if (handles_[soundName].second)
    {
        PlaySoundMem(handles_[soundName].first, DX_PLAYTYPE_LOOP);
    }
    // ’PˆêÄ¶
    else
    {
        PlaySoundMem(handles_[soundName].first, DX_PLAYTYPE_BACK);
    }
}

SoundLoader::~SoundLoader()
{
}
