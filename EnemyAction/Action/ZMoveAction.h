#pragma once
#include "../Action/ActionBase.h"

class Enemy;


// 奥行歩行のｱｸｼｮﾝ実行ｸﾗｽ
struct ZMoveAction :
    public ActionBase
{
public:

    static ZMoveAction& getInstance(void)
    {
        static ZMoveAction sInstance_;
        return sInstance_;
    }

    void Run(Enemy* enemy);
};

