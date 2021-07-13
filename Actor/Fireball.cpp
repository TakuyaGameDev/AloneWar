#include "Fireball.h"

Fireball::Fireball(Vector3F pos) :
    Actor(0)
{
    pos_ = pos;
    name_ = "Fireball";
    Initialize();
}

Fireball::~Fireball()
{
}

void Fireball::Action(void)
{
}

void Fireball::Move(void)
{
}

bool Fireball::Initialize(void)
{
    return true;
}

void Fireball::DebugDraw(void)
{
}
