#include "../../EnemyAction/Action/MoveLRAction.h"
#include "../../Actor/Enemy.h"

void MoveLRAction::Run(Enemy* enemy)
{
	// 既にMoveLR状態だと何もしない
	if (enemy->GetMoveType() != MoveType::MoveLR)
	{
		return;
	}
	// ｱﾆﾒｰｼｮﾝ状態をMove状態に変更
	enemy->SetAnimExcecuter(&Enemy::Move);
}
