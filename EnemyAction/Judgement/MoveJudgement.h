#pragma once
#include "JudgementBase.h"


class Enemy;

// 移動の判定ｸﾗｽ
// これの子供がMoveLRとMoveZとなる
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

