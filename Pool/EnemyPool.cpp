#include "../Pool/EnemyPool.h"
#include "../Actor/Enemy.h"
#include "../Actor/Player.h"

// ﾋﾞﾍｲﾋﾞｱﾃﾞｰﾀを構成するためのｲﾝｸﾙｰﾄﾞ-------------------
#include "../EnemyAction/BehaviorTree.h"
#include "../EnemyAction/Judgement/AttackJudgement.h"
#include "../EnemyAction/Judgement/MoveJudgement.h"
#include "../EnemyAction/Action/MoveLRAction.h"
#include "../EnemyAction/Judgement/MoveLRJudgement.h"
#include "../EnemyAction/Action/NormalAttackAction.h"
#include "../EnemyAction/Judgement/NormalAttackJudgement.h"
#include "../EnemyAction/Action/SkillAttackAction.h"
#include "../EnemyAction/Judgement/SkillAttackJudgement.h"
#include "../EnemyAction/Action/ZMoveAction.h"
#include "../EnemyAction/Judgement/ZMoveJudgement.h"
#include "../EnemyAction/Action/AvoidanceAction.h"
#include "../EnemyAction/Judgement/AvoidanceJudgement.h"
//------------------------------------------------------

EnemyPool::EnemyPool()
{

}

EnemyPool::~EnemyPool()
{
}

void EnemyPool::Create(int size, std::shared_ptr<Player>& player)
{
	// sizeに応じてpoolの大きさが決まる
	for (int s = 0; s < size; s++)
	{
		// まずとにかく敵の箱を用意
		poolMembers_.push_back(std::make_shared<Enemy>(10,player));
	}
	// poolのｻｲｽﾞ
	poolSize_ = size;
}

std::shared_ptr<Enemy>& EnemyPool::Pickup(int spawnCnt)
{
	for (int s = 0; s < spawnCnt; s++)
	{
		// poolのｻｲｽﾞで回す
		for (int i = 0; i < poolSize_; i++) 
		{
			// 死んでいるやつがいればpoolから拾い上げる
			if (!poolMembers_[i]->GetAlive()) 
			{
				// 生き返らせる
				poolMembers_[i]->SetAlive(true);
				// HPの初期化
				poolMembers_[i]->SetHP(10);
				// ﾋﾞﾍｲﾋﾞｱﾃﾞｰﾀのｱﾀｯﾁ
				poolMembers_[i]->SetBehavior(&behaviors_[static_cast<int>(ENEMYTYPE::Cultist)]);
				// 敵のｾｯﾄ
				poolMembers_[i]->SetEnemy(ENEMYTYPE::Cultist, Vector3F(300.0f, 100.0f, 100.0f));
				// 未使用なので再利用可能
				return poolMembers_[i];
			}
		}
	}
}

void EnemyPool::Destroy(void)
{
	for (auto itr = poolMembers_.begin(); itr != poolMembers_.end(); itr++)
	{
		poolMembers_.erase(itr);
	}
}

void EnemyPool::Update(void)
{
	for (int i = 0; i < poolSize_; i++) 
	{
		// 生きていれば
		if (poolMembers_[i]->GetAlive())
		{
			// 更新
			poolMembers_[i]->Update();
		}
	}
}

void EnemyPool::Draw(void)
{
	for (auto member : poolMembers_)
	{
		// 生きていれば
		if (member->GetAlive())
		{
			// 描画
			member->Draw();
		}
	}
}

void EnemyPool::DrawCollider(void)
{
	for (auto member : poolMembers_)
	{
		// 生きていれば
		if (member->GetAlive())
		{
			// ｺﾗｲﾀﾞｰﾎﾞｯｸｽの描画
			member->DebugColliderDraw();
		}
	}
}

void EnemyPool::BehaviorRegistrator(ENEMYTYPE type)
{
	// まずﾙｰﾄの生成
	behaviors_[static_cast<int>(type)].AddNode("", "root", 0,BehaviorTree::SelectRule::Priority, nullptr, nullptr);
	switch (type)
	{
	case ENEMYTYPE::CultistAssassin:
		// 移動の判定ｸﾗｽと実行ｸﾗｽの格納(root -> moveﾉｰﾄﾞに繋げる)
		behaviors_[static_cast<int>(type)].AddNode("root", "move", 3,
													BehaviorTree::SelectRule::Random,
													&MoveJudgement::getInstance(), 
													nullptr);
		// 攻撃の判定ｸﾗｽと実行ｸﾗｽの格納(root -> attackﾉｰﾄﾞに繋げる)
		behaviors_[static_cast<int>(type)].AddNode("root", "attack", 2,
													BehaviorTree::SelectRule::Sequence,
													&AttackJudgement::getInstance(), 
													nullptr);
		// 回避行動の判定ｸﾗｽと実行ｸﾗｽの格納(root -> avoidanceと繋げる)
		behaviors_[static_cast<int>(type)].AddNode("root", "avoidance", 1,
													BehaviorTree::SelectRule::Non, 
													&AvoidanceJudgement::getInstance(),
													&AvoidanceAction::getInstance());
		// 横移動行動の判定ｸﾗｽと実行ｸﾗｽの格納(root -> move -> moveLRと繋げる)
		behaviors_[static_cast<int>(type)].AddNode("move", "moveLR", 1,
													BehaviorTree::SelectRule::Non,
													&MoveLRJudgement::getInstance(), 
													&MoveLRAction::getInstance());
		// 奥移動行動の判定ｸﾗｽと実行ｸﾗｽの格納(root -> move -> moveZと繋げる)
		behaviors_[static_cast<int>(type)].AddNode("move", "moveZ", 2,
													BehaviorTree::SelectRule::Non,
													&ZMoveJudgement::getInstance(), 
													&ZMoveAction::getInstance());
		// 普通の攻撃行動の判定ｸﾗｽと実行ｸﾗｽの格納(root -> attack -> normalAttackと繋げる)
		behaviors_[static_cast<int>(type)].AddNode("attack", "normalAttack", 1,
													BehaviorTree::SelectRule::Non,
													&NormalAttackJudgement::getInstance(), 
													&NormalAttackAction::getInstance());
		// skillAttack行動の判定ｸﾗｽと実行ｸﾗｽの格納(root -> attack -> skilAttackと繋げる)
		behaviors_[static_cast<int>(type)].AddNode("attack", "skillAttack", 2,
													BehaviorTree::SelectRule::Non, 
													&SkillAttackJudgement::getInstance(), 
													&SkillAttackAction::getInstance());
		
		break;
	case ENEMYTYPE::Cultist:
		// 移動の判定ｸﾗｽと実行ｸﾗｽの格納(root -> moveﾉｰﾄﾞに繋げる)
		behaviors_[static_cast<int>(type)].AddNode("root", "move", 3,
													BehaviorTree::SelectRule::Random,
											        &MoveJudgement::getInstance(),
													nullptr);
		// 攻撃の判定ｸﾗｽと実行ｸﾗｽの格納(root -> attackﾉｰﾄﾞに繋げる)
		behaviors_[static_cast<int>(type)].AddNode("root", "attack", 2,
													BehaviorTree::SelectRule::Sequence,
												    &AttackJudgement::getInstance(),
													nullptr);
		// 回避行動の判定ｸﾗｽと実行ｸﾗｽの格納(root -> avoidanceと繋げる)
		behaviors_[static_cast<int>(type)].AddNode("root", "avoidance", 1, 
													BehaviorTree::SelectRule::Non,
												    &AvoidanceJudgement::getInstance(), 
												    &AvoidanceAction::getInstance());
		// 横移動行動の判定ｸﾗｽと実行ｸﾗｽの格納(root -> move -> moveLRと繋げる)
		behaviors_[static_cast<int>(type)].AddNode("move", "moveLR", 1, 
													BehaviorTree::SelectRule::Non,
												    &MoveLRJudgement::getInstance(),
												    &MoveLRAction::getInstance());
		// 奥移動行動の判定ｸﾗｽと実行ｸﾗｽの格納(root -> move -> moveZと繋げる)
		behaviors_[static_cast<int>(type)].AddNode("move", "moveZ", 2,
													BehaviorTree::SelectRule::Non,
												    &ZMoveJudgement::getInstance(),
													&ZMoveAction::getInstance());
		// 普通の攻撃行動の判定ｸﾗｽと実行ｸﾗｽの格納(root -> attack -> normalAttackと繋げる)
		behaviors_[static_cast<int>(type)].AddNode("attack", "normalAttack", 1, 
													BehaviorTree::SelectRule::Non,
												    &NormalAttackJudgement::getInstance(),
												    &NormalAttackAction::getInstance());
		break;
	case ENEMYTYPE::TwistedCultist:
		break;
	case ENEMYTYPE::Max:
		break;
	default:
		break;
	}
}
