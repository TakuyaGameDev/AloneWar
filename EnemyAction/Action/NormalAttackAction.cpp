#include "../../EnemyAction/Action/NormalAttackAction.h"
#include "../../Actor/Enemy.h"

void NormalAttackAction::Run(Enemy* enemy)
{
	// ｱﾆﾒｰｼｮﾝ状態をAttack状態に変更
	enemy->SetAnimExcecuter(&Enemy::Attack);
}
