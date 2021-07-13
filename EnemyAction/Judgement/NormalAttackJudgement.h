#pragma once
#include "JudgementBase.h"

class Enemy;

// ’ÊíUŒ‚‚Ì”»’è¸×½
struct NormalAttackJudgement :
    public JudgementBase
{
public:

    static NormalAttackJudgement& getInstance(void)
    {
        static NormalAttackJudgement sInstance_;
        return sInstance_;
    }

    bool Judgement(Enemy* enemy);
};

