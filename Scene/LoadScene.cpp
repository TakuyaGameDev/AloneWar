#include "LoadScene.h"
#include "../Loader/Loader.h"
#include "Title.h"

LoadScene::LoadScene()
{
	Init();
}

LoadScene::~LoadScene()
{
}

ScenePtr LoadScene::Update(ScenePtr own, const std::shared_ptr<Controller>& controller)
{
	if (lpLoader.LoadData())
	{
		return std::make_unique<Title>();
	}

	return std::move(own);
}

void LoadScene::Draw(void)
{
}

bool LoadScene::Init(void)
{
	// loaderの生成
	lpLoader.getInstance().CreateLoader();
	// loader専用のｽﾚｯﾄﾞの生成と切り離し
	lpLoader.getInstance().Initialize();
	return false;
}

void LoadScene::MakeScreen(void)
{
}
