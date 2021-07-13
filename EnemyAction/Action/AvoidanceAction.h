#pragma once
#include "ActionBase.h"

class Enemy;

// UŒ‚‚ğ”ğ‚¯‚és“®¸×½
struct AvoidanceAction :
    public ActionBase
{
    static AvoidanceAction& getInstance(void)
    {
        static AvoidanceAction sInstance_;
        return sInstance_;
    }

    void Run(Enemy* enemy);
};

