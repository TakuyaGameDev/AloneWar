#pragma once
#include <array>
#include "../Controller/Controller.h"

// ���ް�ޓ��͸׽
struct KeyInput :
	public Controller
{

	// keyInput�Ǝ��̕ϐ���private�ɂ����Ă����Ό��₷���Ȃ�
	// override�Ə����Ă���΁A�p���̃I�[�o�[���C�h���Ă���Ƃ������Ƃ����Ď���B
	ContType GetType(void) override;
	bool Setup(int playerNo) override;
	void Update(void) override;

private:
	std::array<char, 256> _keyData;
	std::map<InputID,int> _inputTable;
};

