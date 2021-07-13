#pragma once
#include "JudgementBase.h"

class Enemy;

// UŒ‚‰ñ”ğs“®‚Ì”»’è¸×½
struct AvoidanceJudgement :
    public JudgementBase
{
    static AvoidanceJudgement& getInstance(void)
    {
        static AvoidanceJudgement sInstance_;
        return sInstance_;
    }

    bool Judgement(Enemy* enemy);
};

