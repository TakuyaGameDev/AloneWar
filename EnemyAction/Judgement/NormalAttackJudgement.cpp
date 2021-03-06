#include "NormalAttackJudgement.h"
#include "../../Actor/Enemy.h"

bool NormalAttackJudgement::Judgement(Enemy* enemy)
{
    // 通常攻撃のﾌﾗｸﾞがtrueの場合trueを返し、実行ﾉｰﾄﾞに渡す
    if (enemy->GetAttackFlag())
    {
        return true;
    }
    return false;
}
