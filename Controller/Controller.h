#pragma once
#include <array>
#include <map>

#include "../Controller/InputID.h"

// ���͑��u�̎��
enum class ContType
{
	Keyboard,
	Mouse,
	GamePad,
	Max
};

// ContType��begin�̒�`
static ContType begin(ContType)
{
	return ContType::Keyboard;
}
// ContType��end�̒�`
static ContType end(ContType)
{
	return ContType::Max;
}
// ContType++�̒�`
static ContType operator++(ContType& type)
{
	return (type = ContType(std::underlying_type<ContType>::type(type) + 1));
}
// ContType++�̒�`
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
// �������g��Ԃ��֐�
static ContType operator*(ContType type)
{
	return type;
}


// �g���K�[���
enum class Trg
{
	// ����
	Now,
	// 1�ڰёO
	Old,
	Max
};

// 1�ڰёO�̏��ƌ��݂̏���trg���
using TrgBool = 
std::array<bool, static_cast<size_t>(Trg::Max)>;
using CntData = std::map<InputID, TrgBool>;

// �֐���޼ު��
struct Controller
{
	// �֐��Ăяo���̃I�[�o�[���C�h
	void operator()()
	{
		Update();
	}
	// �����̓��͏��̎擾
	const CntData& GetCntData(void)
	{
		return _data;
	}
	// �����̓��͑��u�����߂̎擾
	virtual ContType GetType(void) = 0;

	virtual bool Setup(int playerNo) = 0;

private:
	virtual void Update(void) = 0;


protected:
	CntData _data;

};

