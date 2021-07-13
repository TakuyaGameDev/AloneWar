#pragma once
#include <array>

#include "../Controller/Controller.h"
struct PadInput :
	public Controller
{
	ContType GetType(void) override;
	bool Setup(int playerNo) override;
	void Update(void) override;

private:
	// 現在のﾊﾟｯﾄﾞ情報
	int playerPad = 0;
	// 今現在自分が操作するﾊﾟｯﾄﾞ番号
	int inputPadNo_;
	// 上記のﾊﾟｯﾄﾞ番号に順番に格納していくためのカウンター変数
	// ｹﾞｰﾑﾊﾟｯﾄﾞのｾｯﾄｱｯﾌﾟがなされる度に加算されていく
	static int num_;
	// ﾊﾟｯﾄﾞｗｐｺﾝﾄﾛｰﾙしているﾌﾟﾚｲﾔｰ
	int controlledPlayer;
	std::map<InputID,int> inputTable;
};

