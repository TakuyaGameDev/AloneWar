#include "../../EnemyAction/Action/NormalAttackAction.h"
#include "../../Actor/Enemy.h"

void NormalAttackAction::Run(Enemy* enemy)
{
	// ±ÆÒ°¼®Ýó‘Ô‚ðAttackó‘Ô‚É•ÏX
	enemy->SetAnimExcecuter(&Enemy::Attack);
}
