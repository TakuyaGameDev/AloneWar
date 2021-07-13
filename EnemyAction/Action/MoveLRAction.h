#pragma once
#include "../Action/ActionBase.h"


class Enemy;
// ‰¡ˆÚ“®‚Ì±¸¼®İÀs¸×½
struct MoveLRAction :
    public ActionBase
{
public:
    static MoveLRAction& getInstance(void)
    {
        static MoveLRAction sInstance_;
        return sInstance_;
    }

    void Run(Enemy* enemy);
};

