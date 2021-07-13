#include <DxLib.h>
#include "BackGround.h"
#include "../Application.h"

BackGround::BackGround(Vector3F pos, Vector3F size,Wall wallType)
{
	pos_ = pos;
	size_ = size;
	type_ = wallType;
	SetVertex();
}

BackGround::~BackGround()
{
}

void BackGround::Draw(void)
{
	auto& app = Application::getInstance();
	DrawPolygon3D(vertexes_.data(), 2, DX_NONE_GRAPH, true);
	if (type_ == Wall::Right)
	{
		DrawLine3D(VGet(app.GetViewport().x, 0.0f, 0.0f), VGet(app.GetViewport().x, 0.0f, size_.z), 0x000000);
		DrawLine3D(VGet(app.GetViewport().x, app.GetViewport().y, 0.0f), VGet(app.GetViewport().x, app.GetViewport().y, size_.z), 0x000000);
	}
	else if(type_ == Wall::Left)
	{
		DrawLine3D(VGet(0.0f, 0.0f, 0.0f), VGet(0.0f, 0.0f, size_.z), 0x000000);
		DrawLine3D(VGet(0.0f, app.GetViewport().y, 0.0f), VGet(0.0f, app.GetViewport().y, size_.z), 0x000000);
	}
	else if (type_ == Wall::Back)
	{
		DrawLine3D(VGet(0.0f, 0.0f, size_.z), VGet(0.0f, app.GetViewport().y, size_.z), 0x000000);
		DrawLine3D(VGet(0.0f, app.GetViewport().y, size_.z), VGet(app.GetViewport().x, app.GetViewport().y, size_.z), 0x000000);

		DrawLine3D(VGet(app.GetViewport().x, app.GetViewport().y, size_.z), VGet(app.GetViewport().x, 0.0f, size_.z), 0x000000);
		DrawLine3D(VGet(app.GetViewport().x, 0.0f, size_.z), VGet(0.0f, 0.0f, size_.z), 0x000000);
	}

	// è∞ÇÃŒﬂºﬁºÆ›Ç…ä€ÇÃï`âÊ
	DrawCircle(pos_.x, pos_.y,3.0f, 0xff0000, true);
}

void BackGround::SetVertex(void)
{
	auto& app = Application::getInstance();
	switch (type_)
	{
	case Wall::Right:
		vertexes_[0].pos.x = size_.x;
		vertexes_[0].pos.y = 0.0f;
		vertexes_[0].pos.z = 0.0f;

		vertexes_[1].pos.x = size_.x;
		vertexes_[1].pos.y = app.GetViewport().y;
		vertexes_[1].pos.z = 0.0f;

		vertexes_[2].pos.x = size_.x;
		vertexes_[2].pos.y = app.GetViewport().y;
		vertexes_[2].pos.z = size_.z;

		vertexes_[3] = vertexes_[2];

		vertexes_[4].pos.x = size_.x;
		vertexes_[4].pos.y = 0.0f;
		vertexes_[4].pos.z = size_.z;

		vertexes_[5] = vertexes_[0];
		vertexes_[0].r = vertexes_[1].r = vertexes_[2].r = vertexes_[3].r = vertexes_[4].r = vertexes_[5].r = 0xf0f0f0;
		vertexes_[0].g = vertexes_[1].g = vertexes_[2].g = vertexes_[3].g = vertexes_[4].g = vertexes_[5].g = 0xf0f0f0;
		vertexes_[0].b = vertexes_[1].b = vertexes_[2].b = vertexes_[3].b = vertexes_[4].b = vertexes_[5].b = 0xf0f0f0;
		break;
	case Wall::Left:
		vertexes_[0].pos.x = 0.0f;
		vertexes_[0].pos.y = 0.0f;
		vertexes_[0].pos.z = 0.0f;

		vertexes_[1].pos.x = 0.0f;
		vertexes_[1].pos.y = app.GetViewport().y;
		vertexes_[1].pos.z = 0.0f;

		vertexes_[2].pos.x = 0.0f;
		vertexes_[2].pos.y = app.GetViewport().y;
		vertexes_[2].pos.z = size_.z;

		vertexes_[3] = vertexes_[2];

		vertexes_[4].pos.x = 0.0f;
		vertexes_[4].pos.y = 0.0f;
		vertexes_[4].pos.z = size_.z;

		vertexes_[5] = vertexes_[0];
		vertexes_[0].r = vertexes_[1].r = vertexes_[2].r = vertexes_[3].r = vertexes_[4].r = vertexes_[5].r = 0xf0f0f0;
		vertexes_[0].g = vertexes_[1].g = vertexes_[2].g = vertexes_[3].g = vertexes_[4].g = vertexes_[5].g = 0xf0f0f0;
		vertexes_[0].b = vertexes_[1].b = vertexes_[2].b = vertexes_[3].b = vertexes_[4].b = vertexes_[5].b = 0xf0f0f0;
		break;
	case Wall::Floor:
		vertexes_[0].pos.x = 0.0f;
		vertexes_[0].pos.y = 0.0f;
		vertexes_[0].pos.z = 0.0f;

		vertexes_[1].pos.x = 0.0f;
		vertexes_[1].pos.y = 0.0f;
		vertexes_[1].pos.z = size_.z;

		vertexes_[2].pos.x = size_.x;
		vertexes_[2].pos.y = 0.0f;
		vertexes_[2].pos.z = size_.z;

		vertexes_[3] = vertexes_[2];

		vertexes_[4].pos.x = size_.x;
		vertexes_[4].pos.y = 0.0f;
		vertexes_[4].pos.z = 0.0f;

		vertexes_[5] = vertexes_[0];
		vertexes_[0].r = vertexes_[1].r = vertexes_[2].r = vertexes_[3].r = vertexes_[4].r = vertexes_[5].r = 0xf0f0f0;
		vertexes_[0].g = vertexes_[1].g = vertexes_[2].g = vertexes_[3].g = vertexes_[4].g = vertexes_[5].g = 0xf0f0f0;
		vertexes_[0].b = vertexes_[1].b = vertexes_[2].b = vertexes_[3].b = vertexes_[4].b = vertexes_[5].b = 0xf0f0f0;
		break;
	case Wall::Ceiling:
		vertexes_[0].pos.x = 0.0f;
		vertexes_[0].pos.y = app.GetViewport().y;
		vertexes_[0].pos.z = 0.0f;

		vertexes_[1].pos.x = 0.0f;
		vertexes_[1].pos.y = app.GetViewport().y;
		vertexes_[1].pos.z = size_.z;

		vertexes_[2].pos.x = size_.x;
		vertexes_[2].pos.y = app.GetViewport().y;
		vertexes_[2].pos.z = size_.z;

		vertexes_[3] = vertexes_[2];

		vertexes_[4].pos.x = size_.x;
		vertexes_[4].pos.y = app.GetViewport().y;
		vertexes_[4].pos.z = 0.0f;

		vertexes_[5] = vertexes_[0];

		vertexes_[0].r = vertexes_[1].r = vertexes_[2].r = vertexes_[3].r = vertexes_[4].r = vertexes_[5].r = 0xf0f0f0;
		vertexes_[0].g = vertexes_[1].g = vertexes_[2].g = vertexes_[3].g = vertexes_[4].g = vertexes_[5].g = 0xf0f0f0;
		vertexes_[0].b = vertexes_[1].b = vertexes_[2].b = vertexes_[3].b = vertexes_[4].b = vertexes_[5].b = 0xf0f0f0;
		break;
	case Wall::Back:
		vertexes_[0].pos.x = 0.0f;
		vertexes_[0].pos.y = 0.0f;
		vertexes_[0].pos.z = size_.z;

		vertexes_[1].pos.x = 0.0f;
		vertexes_[1].pos.y = app.GetViewport().y;
		vertexes_[1].pos.z = size_.z;

		vertexes_[2].pos.x = size_.x;
		vertexes_[2].pos.y = app.GetViewport().y;
		vertexes_[2].pos.z = size_.z;

		vertexes_[3] = vertexes_[2];

		vertexes_[4].pos.x = size_.x;
		vertexes_[4].pos.y = 0.0f;
		vertexes_[4].pos.z = size_.z;

		vertexes_[5] = vertexes_[0];
		vertexes_[0].r = vertexes_[1].r = vertexes_[2].r = vertexes_[3].r = vertexes_[4].r = vertexes_[5].r = 0xffffff;
		vertexes_[0].g = vertexes_[1].g = vertexes_[2].g = vertexes_[3].g = vertexes_[4].g = vertexes_[5].g = 0xffffff;
		vertexes_[0].b = vertexes_[1].b = vertexes_[2].b = vertexes_[3].b = vertexes_[4].b = vertexes_[5].b = 0xffffff;
	case Wall::Max:
		break;
	default:
		break;
	}
	
}
