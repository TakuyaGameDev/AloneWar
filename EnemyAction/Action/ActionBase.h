#pragma once

class Enemy;

// 行動ｸﾗｽの親ｸﾗｽ
struct ActionBase
{
public:

	// 実行
	void operator()(Enemy* enemy)
	{
		Run(enemy);
	}
	// 純粋仮想でｵｰﾊﾞｰﾗｲﾄﾞ
	virtual void Run(Enemy* enemy) = 0;

protected:

};

