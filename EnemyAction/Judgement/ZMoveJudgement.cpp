#include "ZMoveJudgement.h"
#include "../../Actor/Enemy.h"

bool ZMoveJudgement::Judgement(Enemy* enemy)
{
	// ‰œˆÚ“®‰Â”\‚Å‚ ‚èAUŒ‚‚µ‚Ä‚¢‚È‚¯‚ê‚Îtrue‚ð•Ô‚µ‚ÄAŽÀsÉ°ÄÞ‚ÉŽó‚¯“n‚·
	if (enemy->GetMoveType() == MoveType::MoveZ)
	{
		return true;
	}
	return false;
}
