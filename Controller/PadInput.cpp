#include <DxLib.h>
#include "../Controller/PadInput.h"

int PadInput::num_ = 0;

ContType PadInput::GetType(void)
{
	return ContType::GamePad;
}

bool PadInput::Setup(int playerNo)
{
	controlledPlayer = playerNo;
	// 使用されているﾊﾟｯﾄﾞ番号は使用不可なので、
	// 次にｾｯﾄｱｯﾌﾟされたら次のﾊﾟｯﾄﾞ番号を付与するために加算
	num_++;
	// 自分が操作するﾊﾟｯﾄﾞ番号を格納
	inputPadNo_ = num_;

	if (playerNo == 1)
	{
		inputTable = 
		{
			{InputID::Up,PAD_INPUT_UP},
			{InputID::Down,PAD_INPUT_DOWN},
			{InputID::Left,PAD_INPUT_LEFT},
			{InputID::Right,PAD_INPUT_RIGHT},
			{InputID::Button1,PAD_INPUT_3},
			{InputID::Button2,PAD_INPUT_4},
			{InputID::Decide,PAD_INPUT_10}
		};
	}
	else
	{
		inputTable =
		{
			{InputID::Up,PAD_INPUT_UP},
			{InputID::Down,PAD_INPUT_DOWN},
			{InputID::Left,PAD_INPUT_LEFT},
			{InputID::Right,PAD_INPUT_RIGHT},
			{InputID::Button1,PAD_INPUT_3},
			{InputID::Button2,PAD_INPUT_4},
			{InputID::Decide,PAD_INPUT_10}
		};
	}

	return true;
}

void PadInput::Update(void)
{
	playerPad = GetJoypadInputState(inputPadNo_);

	for (auto id : InputID())
	{
		_data[id][static_cast<int>(Trg::Old)]
			= _data[id][static_cast<int>(Trg::Now)];

		if (playerPad & inputTable[id])
		{
			_data[id][static_cast<int>(Trg::Now)]
				= true;
		}
		else
		{
			_data[id][static_cast<int>(Trg::Now)]
				= false;
		}
	}
}
