#pragma once
#include "BaseScene.h"
class LoadScene :
    public BaseScene
{
public:
    LoadScene();
    ~LoadScene();

    ScenePtr Update(ScenePtr own, const std::shared_ptr<Controller>& controller);

    void Draw(void);
    bool Init(void);

    void MakeScreen(void);
private:

};

