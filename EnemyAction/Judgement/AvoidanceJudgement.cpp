#include "AvoidanceJudgement.h"
#include "../../Actor/Enemy.h"
#include "../../Actor/Player.h"

bool AvoidanceJudgement::Judgement(Enemy* enemy)
{
    // 既にavoidance行動実行中ならば
    if (enemy->GetAnimExcecuter() == &Enemy::Avoidance)
    {
        return true;
    }
    // ﾌﾟﾚｲﾔｰとの距離を測る
    auto distance = enemy->GetDistance();
    auto pl = enemy->GetPlayer();
    // ﾌﾟﾚｲﾔｰが真正面にいるかどうかのﾌﾗｸﾞ
    bool plIsNear = false;

    if ((abs(distance.x) <= 50.0f) &&
        (abs(distance.y) <= 0.0f) &&
        (abs(distance.z) <= 5.0f))
    {
        plIsNear = true;
    }
    // ﾌﾟﾚｲﾔｰが真正面にいて
    if (plIsNear)
    {
        // ﾌﾟﾚｲﾔｰが攻撃していたら
        if (pl->GetAttackFlag() && !enemy->GetAvoidFlag())
        {
            int random = 0;
            // HPが80%以上の時
            if (enemy->IsHPPercentOver(80))
            {
                random = 20;
            }
            // HPが50%以上の時
            else if (enemy->IsHPPercentOver(50))
            {
                random = 50;
            }
            // HPが30%以上の時
            else if (enemy->IsHPPercentOver(30))
            {
                random = 65;
            }
            // HPが30%以下の時
            else
            {
                random = 70;
            }
            // 回避行動ﾌﾗｸﾞをtrueにする
            // 1回しか回ってほしくないため
            // 何回も回っていたら100%回避行動をしてしまう
            // ﾗﾝﾀﾞﾑ値を生成した後に回避ﾌﾗｸﾞをtrueにする
            enemy->SetAvoidFlag(true);
            // ﾗﾝﾀﾞﾑに回避行動をする
            if (rand() % 100 <= random)
            {
                return true;
            }
        }
    }
    else
    {
        return false;
    }

    return false;
}
