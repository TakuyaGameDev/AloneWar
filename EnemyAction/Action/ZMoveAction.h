#pragma once
#include "../Action/ActionBase.h"

class Enemy;


// âúçsï‡çsÇÃ±∏ºÆ›é¿çs∏◊Ω
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

