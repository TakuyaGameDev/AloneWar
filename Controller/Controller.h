#pragma once
#include <array>
#include <map>

#include "../Controller/InputID.h"

// 入力装置の種類
enum class ContType
{
	Keyboard,
	Mouse,
	GamePad,
	Max
};

// ContTypeのbeginの定義
static ContType begin(ContType)
{
	return ContType::Keyboard;
}
// ContTypeのendの定義
static ContType end(ContType)
{
	return ContType::Max;
}
// ContType++の定義
static ContType operator++(ContType& type)
{
	return (type = ContType(std::underlying_type<ContType>::type(type) + 1));
}
// ContType++の定義
static ContType operator--(ContType& type)
{
	return (type = ContType(std::underlying_type<ContType>::type(type) - 1));
}
static ContType operator+(ContType type, int i)
{
	return static_cast<ContType>(static_cast<int> (type) + i);
}
static ContType operator-(ContType type, int i)
{
	return static_cast<ContType>(static_cast<int>(type) - i);
}
// 自分自身を返す関数
static ContType operator*(ContType type)
{
	return type;
}


// トリガー情報
enum class Trg
{
	// 現在
	Now,
	// 1ﾌﾚｰﾑ前
	Old,
	Max
};

// 1ﾌﾚｰﾑ前の情報と現在の情報のtrg情報
using TrgBool = 
std::array<bool, static_cast<size_t>(Trg::Max)>;
using CntData = std::map<InputID, TrgBool>;

// 関数ｵﾌﾞｼﾞｪｸﾄ
struct Controller
{
	// 関数呼び出しのオーバーライド
	void operator()()
	{
		Update();
	}
	// 自分の入力情報の取得
	const CntData& GetCntData(void)
	{
		return _data;
	}
	// 自分の入力装置のﾀｲﾌﾟの取得
	virtual ContType GetType(void) = 0;

	virtual bool Setup(int playerNo) = 0;

private:
	virtual void Update(void) = 0;


protected:
	CntData _data;

};

