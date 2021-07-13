#include "AvoidanceAction.h"
#include "../../Actor/Enemy.h"

void AvoidanceAction::Run(Enemy* enemy)
{
	// ±ÆÒ°¼®Ýó‘Ô‚ðUŒ‚‰ñ”ðs“®ó‘Ô‚É•ÏX
	enemy->SetAnimExcecuter(&Enemy::Avoidance);
}
