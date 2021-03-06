#pragma once
#include "Actor.h"

#define DefAttackLimTime 15.0f

class Player :
    public Actor
{
public:
    Player(Vector3F pos,int hp);
    ~Player();

    void Action(void);
    void Move(void);
    void Attack(void);

    bool Initialize(void);
    // 自分の背後のﾎﾟｼﾞｼｮﾝの取得
    const Vector3F& GetBehindPos(void)
    {
        return behindPos_;
    }
    void DebugDraw(void);
private:

    // LightAttackCombo HeavyAttackCombo の回数のﾘｾｯﾄ
    void AttackCntReseter(void);
    // lightAttackをしているﾌﾗｸﾞ
    // これがtrueの場合はheavyAttackFlagはfalseとなる
    bool lightAttackFlag_;
    // heavyAttackをしているﾌﾗｸﾞ
    // これがtrueの場合はlightAttackFlagはfalseとなる
    bool heavyAttackFlag_;
    // heavyAttackをしている場合:"HeavyAttackCombo"
    // lightAttackをしている場合:"LightAttackCombo"
    std::string attackStr_;
    // 自信の行動の実行関数ﾎﾟｲﾝﾀ
    void(Player::* updater_)(void);

    // 自分の背後のﾎﾟｼﾞｼｮﾝ
    Vector3F behindPos_;

    // 攻撃をしている回数
    // 最大3
    int attackCnt_;
    // 攻撃ﾓｰｼｮﾝ中かどうか
    bool attacking_;
    // 攻撃中の制限ｶｳﾝﾄを超えたらtrueになり初期ｱﾆﾒｰｼｮﾝ(Idle)に戻るﾌﾗｸﾞ
    bool attackResetFlag_;
    // idle状態になっているかのﾌﾗｸﾞ
    bool idleFlag_;
    // 攻撃ﾓｰｼｮﾝの受付時間
    // 一定以上だとidleに戻る
    float attackLimTime_;
};

