#include "SkillAttackAction.h"
#include "../../Actor/Enemy.h"

void SkillAttackAction::Run(Enemy* enemy)
{
	// ±ÆÒ°¼®Ýó‘Ô‚ðAttackó‘Ô‚É•ÏX
	enemy->SetAnimExcecuter(&Enemy::Attack);
}
