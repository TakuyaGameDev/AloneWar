#pragma once
#include <array>
#include "ObjectPool.h"
#include "../ENEMYTYPE.h"
#include "../EnemyAction/BehaviorTree.h"

class Actor;
class Enemy;
class Player;

// 敵のﾀｲﾌﾟ数の思考ﾙｰﾁﾝ配列
using Behavior = std::array<BehaviorTree, static_cast<int>(ENEMYTYPE::Max)>;
// 敵の箱を保管しておくﾊﾞｯﾌｧ(ObjectPooling法)
class EnemyPool :
    public ObjectPool
{
public:
    EnemyPool();
    ~EnemyPool();
    // poolの生成
    void Create(int size,std::shared_ptr<Player>& player);
    // poolの中から死んでいるやつの拾い上げ
    std::shared_ptr<Enemy>& Pickup(int spawnCnt);
    // poolの破棄(Gameの終了時に使用)
    void Destroy(void);
    // poolの中身のﾒﾝﾊﾞｰの更新(生きているやつのみ)
    void Update(void);
    // poolの中身のﾒﾝﾊﾞｰの描画(生きているやつのみ)
    void Draw(void);
    // ColliderBoxの描画(debug表示)
    void DrawCollider(void);

    // ﾀｲﾌﾟに合わせたﾋﾞﾍｲﾋﾞｱﾂﾘｰの作成
    void BehaviorRegistrator(ENEMYTYPE type);

private:
    // poolに溜まっている敵たち
    std::vector<std::shared_ptr<Enemy>> poolMembers_;
    // poolから拾い上げる敵に与えるﾋﾞﾍｲﾋﾞｱﾃﾞｰﾀ
    // ﾀｲﾌﾟ毎に異なる
    Behavior behaviors_;
};

