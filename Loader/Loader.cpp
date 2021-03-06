#include "Loader.h"
#include "../DataCache.h"
#include "SoundLoader.h"

Loader* Loader::sInstance_ = nullptr;

Loader::~Loader()
{
}

void Loader::CreateLoader(void)
{
    if (sInstance_ == nullptr)
    {
        sInstance_ = new Loader();
    }
}

bool Loader::Initialize(void)
{
    // ｽﾚｯﾄﾞ作成
    thisThread_ = std::thread(&Loader::LoadData, this);
    // ｽﾚｯﾄﾞのﾃﾞﾀｯﾁ(切り離し)
    thisThread_.detach();
    return false;
}

bool Loader::LoadData(void)
{
    // 全てﾛｰﾄﾞし終わるまで扱ってほしくない
    std::lock_guard<std::mutex> loack(loadMtx_);
    lpDataCache.SetAtlusData("DataFiles/player.dat", "player");
    lpDataCache.SetAtlusData("DataFiles/Assassin_Cultist.dat", "Assassin_Cultist");
    lpDataCache.SetAtlusData("DataFiles/Cultist.dat", "Cultist");
    lpDataCache.SetAtlusData("DataFiles/Fireball.dat", "Fireball");

    lpDataCache.SetColliderBoxData("player");
    lpDataCache.SetColliderBoxData("Assassin_Cultist");
    lpDataCache.SetColliderBoxData("Cultist");
    lpDataCache.SetColliderBoxData("Fireball");

    lpSoundLoader.Load("Sounds/BGM.mp3", true);
    lpSoundLoader.Load("Sounds/lightAttack.mp3", false);
    lpSoundLoader.Load("Sounds/heavyAttack.mp3", false);
    return true;
}
