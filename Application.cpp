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
	// ���я���
	//65536�FӰ�ނɐݒ�
	SetGraphMode((int)screen_x, (int)screen_y, 16);	
	//true:window�@false:�ٽ�ذ�
	ChangeWindowMode(true);								
	SetWindowText("objectPool");
	//DXײ���؏���������
	if (DxLib_Init() == -1)
	{
		return false;
	}
	SetUse3DFlag(true);
	//�ЂƂ܂��ޯ��ޯ̧�ɕ`��
	SetDrawScreen(DX_SCREEN_BACK);
	controller_ = std::make_shared<KeyInput>();
	controller_->Setup(1);
	return true;
}

Application::~Application()
{
}
