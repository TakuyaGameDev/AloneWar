#pragma once
#include "ActionBase.h"

class Enemy;


// skillAttack‚ÌÀs¸×½
struct SkillAttackAction :
    public ActionBase
{
public:

    static SkillAttackAction& getInstance(void)
    {
        static SkillAttackAction sInstance_;
        return sInstance_;
    }

    void Run(Enemy* enemy);
};

