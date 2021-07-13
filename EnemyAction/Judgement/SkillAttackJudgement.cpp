#include "SkillAttackJudgement.h"
#include "../../Actor/Enemy.h"

bool SkillAttackJudgement::Judgement(Enemy* enemy)
{
    // skillAttackFlag‚ªtrue‚Ìê‡AŽÀsÉ°ÄÞ‚É“n‚·
    if (enemy->GetSkillAttackFlag())
    {
        return true;
    }
    return false;
}
