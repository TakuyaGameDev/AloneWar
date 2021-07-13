#pragma once
#include <type_traits>
// ���݂̎��
enum class InputID
{
	Down,
	Left,
	Right,
	Up,
	Button1,
	Button2,
	Debug1,
	Debug2,
	Debug3,
	Decide,
	Reset,
	Max
};
// InputID��begin�̒�`
static InputID begin(InputID)
{
	return InputID::Down;
}
// InputID��end�̒�`
static InputID end(InputID)
{
	return InputID::Max;
}
// InputID++�̒�`
static InputID operator++(InputID& id)
{
	return (id = InputID(std::underlying_type<InputID>::type(id) + 1));
}
// �������g��Ԃ��֐�
static InputID operator*(InputID id)
{
	return id;
}