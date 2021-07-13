#include "MoveLRJudgement.h"
#include "../../Actor/Enemy.h"

bool MoveLRJudgement::Judgement(Enemy* enemy)
{
	// ‰¡ˆÚ“®‰Â”\‚Å‚ ‚èAUŒ‚‚µ‚Ä‚¢‚È‚¯‚ê‚Îtrue‚ð•Ô‚µ‚ÄAŽÀsÉ°ÄÞ‚ÉŽó‚¯“n‚·
	if (enemy->GetMoveType() == MoveType::MoveLR)
	{
		return true;
	}
	return false;
}
