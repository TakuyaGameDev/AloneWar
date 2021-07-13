#pragma once

class Enemy;
// ”»’è¸×½‚Ìe¸×½
struct JudgementBase
{
public:

	bool operator()(Enemy* enemy)
	{
		return Judgement(enemy);
	}
private:
	virtual bool Judgement(Enemy* enemy) = 0;

};

