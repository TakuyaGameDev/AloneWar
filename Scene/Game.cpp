#include <DxLib.h>
#include "Game.h"
#include "../Controller/Controller.h"
#include "../Application.h"
#include "../Objects/BackGround.h"
#include "../Loader/ImageLoader.h"
#include "../Loader/FileLoader.h"
#include "../DataCache.h"
#include "../Actor/Player.h"
#include "../Pool/EnemyPool.h"
#include "../Loader/SoundLoader.h"

Game::Game()
{
    if (!Init())
    {
        return;
    }
}

Game::~Game()
{
}

ScenePtr Game::Update(ScenePtr own, const std::shared_ptr<Controller>& controller)
{
    auto input = controller->GetCntData();
    for (auto in : input)
    {
        if (in.second[static_cast<int>(Trg::Now)] &&
            !in.second[static_cast<int>(Trg::Old)])
        {
            if (!drawColliderFlag_)
            {
                if (in.first == InputID::Debug1)
                {
                    drawColliderFlag_ = true;
                }
            }
            else
            {
                if (in.first == InputID::Debug1)
                {
                    drawColliderFlag_ = false;
                }
            }
        }
    }
    enemyPool_->Pickup(1);
    player_->Update();
    enemyPool_->Update();
    ClearDrawScreen();
    Draw();
    ScreenFlip();
    frame_++;

    return std::move(own);
}

void Game::Draw(void)
{
    DrawGraph(0, 0, layers_[static_cast<int>(Layer::Back)], true);
    DrawGraph(0, 0, layers_[static_cast<int>(Layer::GameObjects)], true);
    enemyPool_->Draw();
    player_->Draw();
    //player_->DebugDraw();

    auto str = "";

    if (drawColliderFlag_)
    {
        str = "TRUE";
    }
    else
    {
        str = "FALSE";
    }

    DrawFormatString(0, 0, 0x00ff00, "drawColliderMode:%s", str);

    if (drawColliderFlag_)
    {
        player_->DebugColliderDraw();
        enemyPool_->DrawCollider();
    }

    DrawFormatString(0, 400, 0xffffff, "draw call count:%d", GetDrawCallCount());
}

bool Game::Init(void)
{
    frame_ = 0;
    drawColliderFlag_ = false;
    // BGMÇó¨Ç∑
    lpSoundLoader.Play("Sounds/BGM.mp3");
    /*lpFileLoader.TMXLoader("DataFiles/tiledMap.tmx", "testMap");
    auto map = lpDataCache.GetMapData("testMap");
    lpImageLoader.Loader(map.tsx_.sourceName_,map.tileSize_,map.tsx_.imageSize_);*/

    gameObjects_.emplace_back(std::make_unique<BackGround>(Vector3F(lpApp.GetViewport().x / 2, lpApp.GetViewport().y, 250.0f),
                                                      Vector3F(lpApp.GetViewport().x, 0.0f, 150.0f), Wall::Ceiling));
    gameObjects_.emplace_back(std::make_unique<BackGround>(Vector3F(lpApp.GetViewport().x/2, lpApp.GetViewport().y,250.0f),
                                                      Vector3F(lpApp.GetViewport().x,0.0f, 150.0f),Wall::Floor));
    gameObjects_.emplace_back(std::make_unique<BackGround>(Vector3F(lpApp.GetViewport().x / 2, lpApp.GetViewport().y, 250.0f),
                                                      Vector3F(lpApp.GetViewport().x, 0.0f, 150.0f), Wall::Left));
    gameObjects_.emplace_back(std::make_unique<BackGround>(Vector3F(lpApp.GetViewport().x / 2, lpApp.GetViewport().y, 250.0f),
                                                      Vector3F(lpApp.GetViewport().x, 0.0f, 150.0f), Wall::Right));
    gameObjects_.emplace_back(std::make_unique<BackGround>(Vector3F(lpApp.GetViewport().x / 2, lpApp.GetViewport().y, 250.0f),
                                                      Vector3F(lpApp.GetViewport().x, 0.0f, 150.0f), Wall::Back));

    player_ = std::make_shared<Player>(Vector3F(100.0f, 300.0f, 100.0f),100);

    // ìG ﬁØÃßÇÃê∂ê¨
    enemyPool_ = std::make_unique<EnemyPool>();
    // ìG¿≤ÃﬂÇ…ëŒâûÇ∑ÇÈÀﬁÕ≤Àﬁ±¬ÿ∞√ﬁ∞¿ÇÃê∂ê¨
    enemyPool_->BehaviorRegistrator(ENEMYTYPE::Cultist);
    // ìG1ëÃ(à¯êîÇÃ"1"ÇïœçXÇ∑ÇÍÇŒâΩëÃÇ≈Ç‡ê∂ê¨â¬î\)ÇÃê∂ê¨
    enemyPool_->Create(1000, player_);
    // ê∂ê¨ÇµÇΩìGÇ™ ﬁØÃßÇÃíÜÇ≈âjÇ¢Ç≈Ç¢ÇÈÇÃÇ≈ÅA ﬁØÃßÇ©ÇÁèEÇ¢è„Ç∞ÇÈ
    // (Ç±ÇÍÇ‡à¯êîÇÃêîéöÇïœçXÇ∑ÇÈÇ±Ç∆Ç≈èEÇ¢Ç†Ç∞ÇÈìGêîïœçXâ¬î\)
    // ÇΩÇæÇµÅAèEÇ¢Ç†Ç∞ÇÈêîÇæÇØê∂ê¨Ç≥ÇÍÇƒÇ¢Ç»Ç¢Ç∆±ª∞ƒÇèoÇ∑
    enemyPool_->Pickup(1);
    // Ω∏ÿ∞›ÇÃê∂ê¨
    this->MakeScreen(Layer::Back);
    this->MakeScreen(Layer::GameObjects);
    return true;
}

void Game::MakeScreen(Layer layerType)
{
    layers_[static_cast<int>(layerType)] = DxLib::MakeScreen(lpApp.GetViewport().x, lpApp.GetViewport().y, true);
    SetDrawScreen(layers_[static_cast<int>(layerType)]);

    switch (layerType)
    {
    case Layer::Back:
        for (auto&& obj : gameObjects_)
        {
            obj->Draw();
        }
        break;
    case Layer::GameObjects:
        DrawBox(300, 400, 350, 450, 0xff0000, true);
        DrawBox(200, 400, 250, 450, 0x00ff00, true);
        DrawBox(100, 400, 150, 450, 0x0000ff, true);
        DrawBox(500, 400, 550, 450, 0xff0000, true);

        break;
    case Layer::Max:
        break;
    default:
        break;
    }

    //auto map = lpDataCache.GetMapData("testMap");

    //for (auto layer : map.layerData_)
    //{
    //    for (auto y = 0; y < map.layerSize_.y; y++)
    //    { 
    //        for (auto x = 0; x < map.layerSize_.x; x++)
    //        {
    //            if (layer.second.tileSet_[(x + y + ((map.layerSize_.x-1) * y))] != 0)
    //            {
    //                DrawGraph(x * map.tileSize_.x, y * map.tileSize_.y,
    //                    lpImageLoader.GetHandles(map.tsx_.sourceName_)[layer.second.tileSet_[(x + y + ((map.layerSize_.x-1)*y))]-1],
    //                    true);
    //            }
    //        }
    //    }
    //}
    SetDrawScreen(DX_SCREEN_BACK);
}
