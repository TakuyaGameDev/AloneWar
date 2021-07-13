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
	// loader‚Ì¶¬
	lpLoader.getInstance().CreateLoader();
	// loaderê—p‚Ì½Ú¯ÄŞ‚Ì¶¬‚ÆØ‚è—£‚µ
	lpLoader.getInstance().Initialize();
	return false;
}

void LoadScene::MakeScreen(void)
{
}
