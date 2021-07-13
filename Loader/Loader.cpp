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
    // �گ�ލ쐬
    thisThread_ = std::thread(&Loader::LoadData, this);
    // �گ�ނ������(�؂藣��)
    thisThread_.detach();
    return false;
}

bool Loader::LoadData(void)
{
    // �S��۰�ނ��I���܂ň����Ăق����Ȃ�
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
