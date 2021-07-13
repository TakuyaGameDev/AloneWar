#include "../Pool/EnemyPool.h"
#include "../Actor/Enemy.h"
#include "../Actor/Player.h"

// ËŞÍ²ËŞ±ÃŞ°À‚ğ\¬‚·‚é‚½‚ß‚Ì²İ¸Ù°ÄŞ-------------------
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
	// size‚É‰‚¶‚Äpool‚Ì‘å‚«‚³‚ªŒˆ‚Ü‚é
	for (int s = 0; s < size; s++)
	{
		// ‚Ü‚¸‚Æ‚É‚©‚­“G‚Ì” ‚ğ—pˆÓ
		poolMembers_.push_back(std::make_shared<Enemy>(10,player));
	}
	// pool‚Ì»²½Ş
	poolSize_ = size;
}

std::shared_ptr<Enemy>& EnemyPool::Pickup(int spawnCnt)
{
	for (int s = 0; s < spawnCnt; s++)
	{
		// pool‚Ì»²½Ş‚Å‰ñ‚·
		for (int i = 0; i < poolSize_; i++) 
		{
			// €‚ñ‚Å‚¢‚é‚â‚Â‚ª‚¢‚ê‚Îpool‚©‚çE‚¢ã‚°‚é
			if (!poolMembers_[i]->GetAlive()) 
			{
				// ¶‚«•Ô‚ç‚¹‚é
				poolMembers_[i]->SetAlive(true);
				// HP‚Ì‰Šú‰»
				poolMembers_[i]->SetHP(10);
				// ËŞÍ²ËŞ±ÃŞ°À‚Ì±À¯Á
				poolMembers_[i]->SetBehavior(&behaviors_[static_cast<int>(ENEMYTYPE::Cultist)]);
				// “G‚Ì¾¯Ä
				poolMembers_[i]->SetEnemy(ENEMYTYPE::Cultist, Vector3F(300.0f, 100.0f, 100.0f));
				// –¢g—p‚È‚Ì‚ÅÄ—˜—p‰Â”\
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
		// ¶‚«‚Ä‚¢‚ê‚Î
		if (poolMembers_[i]->GetAlive())
		{
			// XV
			poolMembers_[i]->Update();
		}
	}
}

void EnemyPool::Draw(void)
{
	for (auto member : poolMembers_)
	{
		// ¶‚«‚Ä‚¢‚ê‚Î
		if (member->GetAlive())
		{
			// •`‰æ
			member->Draw();
		}
	}
}

void EnemyPool::DrawCollider(void)
{
	for (auto member : poolMembers_)
	{
		// ¶‚«‚Ä‚¢‚ê‚Î
		if (member->GetAlive())
		{
			// º×²ÀŞ°ÎŞ¯¸½‚Ì•`‰æ
			member->DebugColliderDraw();
		}
	}
}

void EnemyPool::BehaviorRegistrator(ENEMYTYPE type)
{
	// ‚Ü‚¸Ù°Ä‚Ì¶¬
	behaviors_[static_cast<int>(type)].AddNode("", "root", 0,BehaviorTree::SelectRule::Priority, nullptr, nullptr);
	switch (type)
	{
	case ENEMYTYPE::CultistAssassin:
		// ˆÚ“®‚Ì”»’è¸×½‚ÆÀs¸×½‚ÌŠi”[(root -> moveÉ°ÄŞ‚ÉŒq‚°‚é)
		behaviors_[static_cast<int>(type)].AddNode("root", "move", 3,
													BehaviorTree::SelectRule::Random,
													&MoveJudgement::getInstance(), 
													nullptr);
		// UŒ‚‚Ì”»’è¸×½‚ÆÀs¸×½‚ÌŠi”[(root -> attackÉ°ÄŞ‚ÉŒq‚°‚é)
		behaviors_[static_cast<int>(type)].AddNode("root", "attack", 2,
													BehaviorTree::SelectRule::Sequence,
													&AttackJudgement::getInstance(), 
													nullptr);
		// ‰ñ”ğs“®‚Ì”»’è¸×½‚ÆÀs¸×½‚ÌŠi”[(root -> avoidance‚ÆŒq‚°‚é)
		behaviors_[static_cast<int>(type)].AddNode("root", "avoidance", 1,
													BehaviorTree::SelectRule::Non, 
													&AvoidanceJudgement::getInstance(),
													&AvoidanceAction::getInstance());
		// ‰¡ˆÚ“®s“®‚Ì”»’è¸×½‚ÆÀs¸×½‚ÌŠi”[(root -> move -> moveLR‚ÆŒq‚°‚é)
		behaviors_[static_cast<int>(type)].AddNode("move", "moveLR", 1,
													BehaviorTree::SelectRule::Non,
													&MoveLRJudgement::getInstance(), 
													&MoveLRAction::getInstance());
		// ‰œˆÚ“®s“®‚Ì”»’è¸×½‚ÆÀs¸×½‚ÌŠi”[(root -> move -> moveZ‚ÆŒq‚°‚é)
		behaviors_[static_cast<int>(type)].AddNode("move", "moveZ", 2,
													BehaviorTree::SelectRule::Non,
													&ZMoveJudgement::getInstance(), 
													&ZMoveAction::getInstance());
		// •’Ê‚ÌUŒ‚s“®‚Ì”»’è¸×½‚ÆÀs¸×½‚ÌŠi”[(root -> attack -> normalAttack‚ÆŒq‚°‚é)
		behaviors_[static_cast<int>(type)].AddNode("attack", "normalAttack", 1,
													BehaviorTree::SelectRule::Non,
													&NormalAttackJudgement::getInstance(), 
													&NormalAttackAction::getInstance());
		// skillAttacks“®‚Ì”»’è¸×½‚ÆÀs¸×½‚ÌŠi”[(root -> attack -> skilAttack‚ÆŒq‚°‚é)
		behaviors_[static_cast<int>(type)].AddNode("attack", "skillAttack", 2,
													BehaviorTree::SelectRule::Non, 
													&SkillAttackJudgement::getInstance(), 
													&SkillAttackAction::getInstance());
		
		break;
	case ENEMYTYPE::Cultist:
		// ˆÚ“®‚Ì”»’è¸×½‚ÆÀs¸×½‚ÌŠi”[(root -> moveÉ°ÄŞ‚ÉŒq‚°‚é)
		behaviors_[static_cast<int>(type)].AddNode("root", "move", 3,
													BehaviorTree::SelectRule::Random,
											        &MoveJudgement::getInstance(),
													nullptr);
		// UŒ‚‚Ì”»’è¸×½‚ÆÀs¸×½‚ÌŠi”[(root -> attackÉ°ÄŞ‚ÉŒq‚°‚é)
		behaviors_[static_cast<int>(type)].AddNode("root", "attack", 2,
													BehaviorTree::SelectRule::Sequence,
												    &AttackJudgement::getInstance(),
													nullptr);
		// ‰ñ”ğs“®‚Ì”»’è¸×½‚ÆÀs¸×½‚ÌŠi”[(root -> avoidance‚ÆŒq‚°‚é)
		behaviors_[static_cast<int>(type)].AddNode("root", "avoidance", 1, 
													BehaviorTree::SelectRule::Non,
												    &AvoidanceJudgement::getInstance(), 
												    &AvoidanceAction::getInstance());
		// ‰¡ˆÚ“®s“®‚Ì”»’è¸×½‚ÆÀs¸×½‚ÌŠi”[(root -> move -> moveLR‚ÆŒq‚°‚é)
		behaviors_[static_cast<int>(type)].AddNode("move", "moveLR", 1, 
													BehaviorTree::SelectRule::Non,
												    &MoveLRJudgement::getInstance(),
												    &MoveLRAction::getInstance());
		// ‰œˆÚ“®s“®‚Ì”»’è¸×½‚ÆÀs¸×½‚ÌŠi”[(root -> move -> moveZ‚ÆŒq‚°‚é)
		behaviors_[static_cast<int>(type)].AddNode("move", "moveZ", 2,
													BehaviorTree::SelectRule::Non,
												    &ZMoveJudgement::getInstance(),
													&ZMoveAction::getInstance());
		// •’Ê‚ÌUŒ‚s“®‚Ì”»’è¸×½‚ÆÀs¸×½‚ÌŠi”[(root -> attack -> normalAttack‚ÆŒq‚°‚é)
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
