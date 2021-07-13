#include "AttackJudgement.h"
#include "../../Actor/Enemy.h"

bool AttackJudgement::Judgement(Enemy* enemy)
{
    // UŒ‚‚µ‚Ä‚¢‚ê‚ÎˆÚ“®‚Í‚³‚¹‚È‚¢
    if (enemy->GetAttackFlag() || enemy->GetSkillAttackFlag())
    {
        return true;
    }
    // ÌßÚ²Ô°‚Æ‚Ì‹——£‚ğ‘ª‚é
    auto distance = enemy->GetDistance();

    // ’ÊíUŒ‚
    if ((abs(distance.x) <= enemy->GetVisionRange().attackRange_) && (abs(distance.z) <= 5.0f))
    {
        // ’ÊíUŒ‚‚ğtrue‚É‚·‚é
        enemy->SetAttackFlag(true);
        // skillAttack‚ğfalse‚É‚·‚é
        enemy->SetSkillAttackFlag(false);
        return true;
    }

    // skillAttackUŒ‚
    // ½·Ù‚ğ‚Á‚Ä‚¢‚ê‚Î
    if (enemy->HasSkill())
    {
        if ((abs(distance.x) <= enemy->GetVisionRange().attackRange_ + 50.0f) && (abs(distance.z) <= 5.0f))
        {
            // skillAttack‚ğtrue‚É
            enemy->SetSkillAttackFlag(true);
            // ’Êí‚ÌUŒ‚‚ğfalse‚É
            enemy->SetAttackFlag(false);
            return true;
        }
    }

    // ‰½‚É‚à“–‚Ä‚Í‚Ü‚ç‚È‚¯‚ê‚Î‚Ç‚¿‚ç‚àfalse‚É‚·‚é
    enemy->SetAttackFlag(false);
    enemy->SetSkillAttackFlag(false);

    return false;
}
