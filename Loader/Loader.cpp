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
    // ½Ú¯ÄŞì¬
    thisThread_ = std::thread(&Loader::LoadData, this);
    // ½Ú¯ÄŞ‚ÌÃŞÀ¯Á(Ø‚è—£‚µ)
    thisThread_.detach();
    return false;
}

bool Loader::LoadData(void)
{
    // ‘S‚ÄÛ°ÄŞ‚µI‚í‚é‚Ü‚Åˆµ‚Á‚Ä‚Ù‚µ‚­‚È‚¢
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
