#include <DxLib.h>
#include "../Controller/KeyInput.h"

ContType KeyInput::GetType(void)
{
	return ContType::Keyboard;
}

bool KeyInput::Setup(int playerNo)
{
	if (playerNo == 1)
	{
		_inputTable =
		{
			{InputID::Down,KEY_INPUT_S},
			{InputID::Left,KEY_INPUT_A},
			{InputID::Right,KEY_INPUT_D},
			{InputID::Up,KEY_INPUT_W},
			{InputID::Button1,KEY_INPUT_1},
			{InputID::Button2,KEY_INPUT_2},
			{InputID::Debug1,KEY_INPUT_F1},
			{InputID::Debug2,KEY_INPUT_F2},
			{InputID::Debug3,KEY_INPUT_F3},

			{InputID::Decide,KEY_INPUT_RETURN},
			{InputID::Reset,KEY_INPUT_3}
		};
	}
	else
	{
		_inputTable =
		{
			{InputID::Down,KEY_INPUT_DOWN},
			{InputID::Left,KEY_INPUT_LEFT},
			{InputID::Right,KEY_INPUT_RIGHT},
			{InputID::Up,KEY_INPUT_UP},
			{InputID::Button1,KEY_INPUT_NUMPAD1},
			{InputID::Button2,KEY_INPUT_NUMPAD2},
			{InputID::Debug1,KEY_INPUT_F1},
			{InputID::Debug2,KEY_INPUT_F2},
			{InputID::Debug3,KEY_INPUT_F3},
			{InputID::Decide,KEY_INPUT_END},
			{InputID::Reset,KEY_INPUT_DELETE}
		};
	}
	return true;
}

void KeyInput::Update(void)
{
	GetHitKeyStateAll(&_keyData[0]);

	for (auto id : InputID())
	{
		_data[id][static_cast<int>(Trg::Old)]
			= _data[id][static_cast<int>(Trg::Now)];
		_data[id][static_cast<int>(Trg::Now)]
			= _keyData[_inputTable[id]];
	}
}
