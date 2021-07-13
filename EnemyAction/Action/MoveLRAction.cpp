#include "../../EnemyAction/Action/MoveLRAction.h"
#include "../../Actor/Enemy.h"

void MoveLRAction::Run(Enemy* enemy)
{
	// Šù‚ÉMoveLRó‘Ô‚¾‚Æ‰½‚à‚µ‚È‚¢
	if (enemy->GetMoveType() != MoveType::MoveLR)
	{
		return;
	}
	// ±ÆÒ°¼®Ýó‘Ô‚ðMoveó‘Ô‚É•ÏX
	enemy->SetAnimExcecuter(&Enemy::Move);
}
