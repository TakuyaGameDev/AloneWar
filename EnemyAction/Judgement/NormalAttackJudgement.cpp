#include "NormalAttackJudgement.h"
#include "../../Actor/Enemy.h"

bool NormalAttackJudgement::Judgement(Enemy* enemy)
{
    // ’ÊíUŒ‚‚ÌÌ×¸Ş‚ªtrue‚Ìê‡true‚ğ•Ô‚µAÀsÉ°ÄŞ‚É“n‚·
    if (enemy->GetAttackFlag())
    {
        return true;
    }
    return false;
}
