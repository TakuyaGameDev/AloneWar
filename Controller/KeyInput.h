#pragma once
#include <array>
#include "../Controller/Controller.h"

// ｷｰﾎﾞｰﾄﾞ入力ｸﾗｽ
struct KeyInput :
	public Controller
{

	// keyInput独自の変数はprivateにもっていけば見やすくなる
	// overrideと書いていれば、継承のオーバーライドしているということが見て取れる。
	ContType GetType(void) override;
	bool Setup(int playerNo) override;
	void Update(void) override;

private:
	std::array<char, 256> _keyData;
	std::map<InputID,int> _inputTable;
};

