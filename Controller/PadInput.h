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
	// ���݂��߯�ޏ��
	int playerPad = 0;
	// �����ݎ��������삷���߯�ޔԍ�
	int inputPadNo_;
	// ��L���߯�ޔԍ��ɏ��ԂɊi�[���Ă������߂̃J�E���^�[�ϐ�
	// �ް��߯�ނ̾�ı��߂��Ȃ����x�ɉ��Z����Ă���
	static int num_;
	// �߯�ނ������۰ق��Ă�����ڲ԰
	int controlledPlayer;
	std::map<InputID,int> inputTable;
};

