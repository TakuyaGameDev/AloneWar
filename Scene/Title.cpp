#include <DxLib.h>
#include "Title.h"
#include "Game.h"
#include "../Controller/Controller.h"


Title::Title()
{
	if (!Init())
	{
		return;
	}
}

Title::~Title()
{
}

ScenePtr Title::Update(ScenePtr own, const std::shared_ptr<Controller>& controller)
{
	
	for (auto cnt : controller->GetCntData())
	{
		if (cnt.second[static_cast<int>(Trg::Now)] & !cnt.second[static_cast<int>(Trg::Old)])
		{
			if (cnt.first == InputID::Decide)
			{
				return std::make_unique<Game>();
			}
		}
	}

	ClearDrawScreen();
	Draw();
	ScreenFlip();

	return std::move(own);
}

void Title::Draw(void)
{
	DrawFormatString(0, 0, 0xffffff, "ObjestPooling sample");
}

bool Title::Init(void)
{

	return true;
}

void Title::MakeScreen(void)
{
}
