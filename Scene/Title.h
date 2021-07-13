#pragma once
#include "BaseScene.h"
class Title :
    public BaseScene
{
public:
    Title();
    ~Title();
    ScenePtr Update(ScenePtr own, const std::shared_ptr<Controller>& controller);

    void Draw(void);
    bool Init(void);

    void MakeScreen(void);
private:
    int layer_;
};

