#pragma once
#include "JudgementBase.h"


class Enemy;

// ˆÚ“®‚Ì”»’è¸×½
// ‚±‚ê‚ÌŽq‹Ÿ‚ªMoveLR‚ÆMoveZ‚Æ‚È‚é
struct MoveJudgement :
    public JudgementBase
{
    static MoveJudgement& getInstance(void)
    {
        static MoveJudgement sInstance_;
        return sInstance_;
    }

    bool Judgement(Enemy* enemy);
};

