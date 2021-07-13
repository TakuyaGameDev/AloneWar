#include "../../EnemyAction/Action/ZMoveAction.h"
#include "../../Actor/Enemy.h"

void ZMoveAction::Run(Enemy* enemy)
{
	// Šù‚ÉMoveZó‘Ô‚¾‚Æ‰½‚à‚µ‚È‚¢
	if (enemy->GetMoveType() != MoveType::MoveZ)
	{
		return;
	}
	// ±ÆÒ°¼®Ýó‘Ô‚ðZMove‚É•ÏX
	enemy->SetAnimExcecuter(&Enemy::ZMove);
}
