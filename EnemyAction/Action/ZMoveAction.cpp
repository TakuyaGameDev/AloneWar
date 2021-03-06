#include "../../EnemyAction/Action/ZMoveAction.h"
#include "../../Actor/Enemy.h"

void ZMoveAction::Run(Enemy* enemy)
{
	// 既にMoveZ状態だと何もしない
	if (enemy->GetMoveType() != MoveType::MoveZ)
	{
		return;
	}
	// ｱﾆﾒｰｼｮﾝ状態をZMoveに変更
	enemy->SetAnimExcecuter(&Enemy::ZMove);
}
