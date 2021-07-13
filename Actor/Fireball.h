#pragma once
#include "Actor.h"
class Fireball :
    public Actor
{
public:
    Fireball(Vector3F pos);
    ~Fireball();

    void Action(void);
    void Move(void);
    bool Initialize(void);

    void DebugDraw(void);

private:

};

