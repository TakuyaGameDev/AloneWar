#pragma once
#include <list>
#include <memory>
#include <array>
#include <string>
#include <vector>
#include <map>
#include "BaseScene.h"

enum class Layer
{
    Back,
    GameObjects,
    Max
};

using Layers = std::array<int, static_cast<int>(Layer::Max)>;

class Obj;
class EnemyPool;
class Player;
struct ColliderBoxData;
struct AtlusData;

class Game :
    public BaseScene
{
public:
    Game();
    ~Game();

    ScenePtr Update(ScenePtr own, const std::shared_ptr<Controller>& controller);
    void Draw(void);
    bool Init(void);
    void MakeScreen(Layer layerType);

private:

    std::list<std::unique_ptr<Obj>> gameObjects_;
    std::shared_ptr<Player> player_;
    std::unique_ptr<EnemyPool> enemyPool_;

    Layers layers_;

    int frame_;
    // “–‚½‚è”»’èÎÞ¯¸½‚Ì•`‰æÌ×¸Þ
    bool drawColliderFlag_;
};

