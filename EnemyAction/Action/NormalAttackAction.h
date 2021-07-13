#pragma once
#include "../Action/ActionBase.h"

// ’ÊíUŒ‚‚ÌÀs¸×½
struct NormalAttackAction :
    public ActionBase
{
public:
    static NormalAttackAction& getInstance(void)
    {
        static NormalAttackAction sInstance_;
        return sInstance_;
    }

    void Run(Enemy* enemy);
};

