#pragma once
#include <type_traits>
// ﾎﾞﾀﾝの種類
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
// InputIDのbeginの定義
static InputID begin(InputID)
{
	return InputID::Down;
}
// InputIDのendの定義
static InputID end(InputID)
{
	return InputID::Max;
}
// InputID++の定義
static InputID operator++(InputID& id)
{
	return (id = InputID(std::underlying_type<InputID>::type(id) + 1));
}
// 自分自身を返す関数
static InputID operator*(InputID id)
{
	return id;
}