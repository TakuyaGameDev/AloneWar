#pragma once
#include "../Action/ActionBase.h"


class Enemy;
// 横移動のｱｸｼｮﾝ実行ｸﾗｽ
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

