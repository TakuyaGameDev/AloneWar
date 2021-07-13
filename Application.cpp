#include <DxLib.h>
#include "Application.h"
#include "Scene/Title.h"
#include "Scene/LoadScene.h"
#include "Controller/KeyInput.h"

void Application::Run(void)
{
	if (!SystemInit())
	{
		return;
	}
	sptr_ = std::make_unique<LoadScene>();

	while ((ProcessMessage() == 0) &&
		   (CheckHitKey(KEY_INPUT_ESCAPE) == 0))
	{
		(*controller_)();
		sptr_ = sptr_->Update(std::move(sptr_),controller_);
	}
}

void Application::Exit(void)
{
	DxLib_End();
}

bool Application::SystemInit(void)
{
	// ¼½ÃÑˆ—
	//65536FÓ°ÄŞ‚Éİ’è
	SetGraphMode((int)screen_x, (int)screen_y, 16);	
	//true:window@false:ÌÙ½¸Ø°İ
	ChangeWindowMode(true);								
	SetWindowText("objectPool");
	//DX×²ÌŞ×Ø‰Šú‰»ˆ—
	if (DxLib_Init() == -1)
	{
		return false;
	}
	SetUse3DFlag(true);
	//‚Ğ‚Æ‚Ü‚¸ÊŞ¯¸ÊŞ¯Ì§‚É•`‰æ
	SetDrawScreen(DX_SCREEN_BACK);
	controller_ = std::make_shared<KeyInput>();
	controller_->Setup(1);
	return true;
}

Application::~Application()
{
}
