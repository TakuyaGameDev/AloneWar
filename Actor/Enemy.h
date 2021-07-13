#pragma once
#include "Actor.h"
#include "../ENEMYTYPE.h"
#include "../EnemyAction/BehaviorTree.h"

// Z軸方向のﾌﾟﾗｽﾏｲﾅｽどちらかに移動するかのﾀｲﾌﾟ
enum class ZPosFromPlayer
{
    // ﾌﾟﾚｲﾔｰのZ軸よりもﾏｲﾅｽにある場合
    Minus,
    // ﾌﾟﾚｲﾔｰのZ軸よりもﾌﾟﾗｽにある場合
    Plus,
    // ﾌﾟﾚｲﾔｰのZ軸との差が一定以下の場合
    Non,
    Max
};

// 動きのﾀｲﾌﾟ
enum class MoveType
{
    // 左右横に動く
    MoveLR,
    // 奥行に動く
    MoveZ,
    // 動かない
    Non,
    Max
};

// 自分の視界
struct VisionRange
{
    // runｱﾆﾒｰｼｮﾝを行う視界
    float runRange_;
    // attackｱﾆﾒｰｼｮﾝを行う視界
    float attackRange_;

    VisionRange() :runRange_(0.0f), attackRange_(0.0f) {};
    VisionRange(float runR, float atR) :runRange_(runR), attackRange_(atR) {};
};

// 各ｱﾆﾒｰｼｮﾝの実行関数ﾎﾟｲﾝﾀ
typedef void(Enemy::* AnimExcecuter)();

class BehaviorData;
class ActionNode;
class Player;

class Enemy :
    public Actor
{
public:
    Enemy(int hp, std::shared_ptr<Player>& player);
    ~Enemy();
    // 更新
    void Action(void);
    // 左右の動き
    void Move(void);
    // Z軸を合わせるｱｸｼｮﾝ
    void ZMove(void);
    // 攻撃(Actorからの継承)
    void Attack(void);
    // Attack関数に含めるためのｽｷﾙ攻撃関数(引数の敵のﾀｲﾌﾟ毎に分岐)
    void SkillAttack(ENEMYTYPE type);
    // 回避行動
    void Avoidance(void);
    // 初期化
    virtual bool Initialize(void) { return false; };
    // poolの中から死んでいるやつをpickUpするのでpickUpしたやつにﾀｲﾌﾟを与えてやったり
    // ﾎﾟｼﾞｼｮﾝをｾｯﾄしてやる関数
    void SetEnemy(ENEMYTYPE type,Vector3F pos);
    // ﾋﾞﾍｲﾋﾞｱﾂﾘｰのｾｯﾄ
    void SetBehavior(BehaviorTree* behaviorTree);
    // 敵ﾀｲﾌﾟのｾｯﾄ関数
    void Set(ENEMYTYPE type);
    // 視界の取得
    const VisionRange& GetVisionRange(void)
    {
        return visionRange_;
    }
    // あるﾎﾟｼﾞｼｮﾝとの距離を計算して取得
    const Vector3F& GetDistance(void);
    // ﾃﾞﾊﾞｯｸﾞ表示
    void DebugDraw(void);
    // Z軸方向のﾏｲﾅｽ方向に動かすのかﾌﾟﾗｽ方向に動かすのかのｾｯﾄ関数
    void SetZPosStatus(ZPosFromPlayer zStatus);
    // ｱﾆﾒｰｼｮﾝ実行関数に実行関数のｾｯﾄ
    void SetAnimExcecuter(void(Enemy::* func)());

    // ﾋﾞﾍｲﾋﾞｱﾂﾘｰの取得関数
    BehaviorTree* GetBehaviorTree(void)
    {
        return behaviorTree_;
    }
   
    // 動きのﾀｲﾌﾟの取得
    const MoveType& GetMoveType(void)
    {
        return moveType_;
    }
    // 動きのﾀｲﾌﾟのｾｯﾄ
    void SetMoveType(MoveType moveType);

    // 自分が見ているﾌﾟﾚｲﾔｰの取得
    const std::shared_ptr<Player>& GetPlayer(void)
    {
        return player_;
    }
    // 行動実行関数ﾎﾟｲﾝﾀ取得関数
    const AnimExcecuter& GetAnimExcecuter(void)
    {
        return animExcecuter_;
    }
    // ｽｷﾙを持っていればtrueを返す
    const bool& HasSkill(void)
    {
        return hasSkill_;
    }

private:

protected:
    // 行動の実行関数ﾎﾟｲﾝﾀ
    AnimExcecuter animExcecuter_;
    // 自分のﾀｲﾌﾟ変数
    ENEMYTYPE myType_;
    // 自信のﾋﾞﾍｲﾋﾞｱﾂﾘｰ(思考)
    BehaviorTree* behaviorTree_;
    // ﾋﾞﾍｲﾋﾞｱﾃﾞｰﾀ(sequence等のﾃﾞｰﾀ)
    BehaviorData* behaviorData_;
    // 実行ﾉｰﾄﾞ
    ActionNode* runningNode_;
    // 視界
    VisionRange visionRange_;
    // ﾌﾟﾚｲﾔｰの参照
    std::shared_ptr<Player>& player_;
    // ﾌﾟﾚｲﾔｰに対しての自分のZ軸の状態
    ZPosFromPlayer zPosStatus_;
    // 動きのﾀｲﾌﾟ変数
    MoveType moveType_;
    // 当たり判定を受け付けないﾌﾗｸﾞ
    bool noAcceptHitFlag_;
    // ｽｷﾙを持っているかのﾌﾗｸﾞ
    bool hasSkill_;
};

