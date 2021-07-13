#include "MoveJudgement.h"
#include "../../Actor/Enemy.h"

bool MoveJudgement::Judgement(Enemy* enemy)
{
	// UŒ‚‚µ‚Ä‚¢‚é‚Í“®‚©‚³‚È‚¢
	if (enemy->GetAttackFlag() || enemy->GetSkillAttackFlag())
	{
		return false;
	}
	// ÌßÚ²Ô°‚Æ‚Ì‹——£‚ğ‘ª‚é
	auto dis = enemy->GetDistance();
	// ‰œsˆÚ“®
	if (abs(dis.x) > enemy->GetVisionRange().attackRange_)
	{
		enemy->SetMoveType(MoveType::MoveLR);
		return true;
	}
	// Z²‚Ìó‘Ô‚ğŒ©‚Ä‚¢‚é
	if (abs(dis.x) <= enemy->GetVisionRange().attackRange_)
	{
		// Z²‚Ìó‘Ô
		// ÌßÚ²Ô°‚æ‚è‚àè‘O‚É‚¢‚éê‡
		if (dis.z < 0.0f)
		{
			enemy->SetZPosStatus(ZPosFromPlayer::Minus);
			enemy->SetMoveType(MoveType::MoveZ);
			return true;
		}
		// Z²‚Ìó‘Ô
		// ÌßÚ²Ô°‚æ‚è‚à‰œ‚É‚¢‚éê‡
		if (dis.z > 0.0f)
		{
			enemy->SetZPosStatus(ZPosFromPlayer::Plus);
			enemy->SetMoveType(MoveType::MoveZ);
			return true;
		}
	}
	// ‰½‚É‚à“–‚Ä‚Í‚Ü‚ç‚È‚¢ê‡MoveType‚ğNon(“®‚¢‚Ä‚¢‚È‚¢ó‘Ô)‚É
	enemy->SetMoveType(MoveType::Non);

    return false;
}
