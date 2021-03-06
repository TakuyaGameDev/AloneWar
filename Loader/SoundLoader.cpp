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
    // ﾙｰﾌﾟ再生
    if (handles_[soundName].second)
    {
        PlaySoundMem(handles_[soundName].first, DX_PLAYTYPE_LOOP);
    }
    // 単一再生
    else
    {
        PlaySoundMem(handles_[soundName].first, DX_PLAYTYPE_BACK);
    }
}

SoundLoader::~SoundLoader()
{
}
