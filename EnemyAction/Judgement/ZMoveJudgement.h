#pragma once
#include "JudgementBase.h"

class Enemy;

// ‰œsˆÚ“®‚Ì”»’è¸×½
struct ZMoveJudgement :
    public JudgementBase
{
public:

    static ZMoveJudgement& getInstance(void)
    {
        static ZMoveJudgement sInstance_;
        return sInstance_;
    }

    bool Judgement(Enemy* enemy);
};

