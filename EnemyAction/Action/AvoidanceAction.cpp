#include "AvoidanceAction.h"
#include "../../Actor/Enemy.h"

void AvoidanceAction::Run(Enemy* enemy)
{
	// ｱﾆﾒｰｼｮﾝ状態を攻撃回避行動状態に変更
	enemy->SetAnimExcecuter(&Enemy::Avoidance);
}
