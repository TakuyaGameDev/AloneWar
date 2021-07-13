#include "../Actor/Enemy.h"
#include "../Actor/Player.h"

#include "../EnemyAction/Action/MoveLRAction.h"
#include "../EnemyAction/Judgement/MoveLRJudgement.h"
#include "../EnemyAction/Action/ZMoveAction.h"
#include "../EnemyAction/Judgement/ZMoveJudgement.h"
#include "../EnemyAction/Action/NormalAttackAction.h"
#include "../EnemyAction/Judgement/NormalAttackJudgement.h"
#include "../EnemyAction/Action/SkillAttackAction.h"
#include "../EnemyAction/Judgement/SkillAttackJudgement.h"

#include "../EnemyAction/BehaviorData.h"

#include "../CollisionCheck.h"
#include "../DataCache.h"

Enemy::Enemy(int hp, std::shared_ptr<Player>& player):
	Actor(hp),player_(player)
{
	// 生きているﾌﾗｸﾞの初期化
	isAlive_ = false;
	// 当たり判定ﾌﾗｸﾞの初期化
	isHit_ = false;
	// 当たり判定を受け付けないﾌﾗｸﾞの初期化
	noAcceptHitFlag_ = false;
	// 現在思考しているﾋﾞﾍｲﾋﾞｱﾂﾘｰのﾉｰﾄﾞ
	runningNode_ = nullptr;
	// ﾋﾞﾍｲﾋﾞｱﾃﾞｰﾀの作成
	behaviorData_ = new BehaviorData;
}

Enemy::~Enemy()
{
}

void Enemy::Action(void)
{
	// 床の上にいる時
	if (onFloor_)
	{
		// 当たり判定は何もない時
		if (!isHit_)
		{
			// 現在の行動にﾋﾞﾍｲﾋﾞｱﾂﾘｰのrootから推論した結果のﾉｰﾄﾞを格納
			runningNode_ = behaviorTree_->Inference(this,behaviorData_);
			// 格納する行動が有れば
			if (runningNode_ != nullptr)
			{
				// ﾋﾞﾍｲﾋﾞｱﾂﾘｰから、runningNode_に対応したﾉｰﾄﾞを走らせる
				behaviorTree_->Run(this, runningNode_, behaviorData_);
			}
			else
			{
				// 何も行動をしないときはIdleを設定
				SetAnimExcecuter(&Enemy::Idle);
			}
			// 行動に応じたｱﾆﾒｰｼｮﾝと動きを関数ﾎﾟｲﾝﾀで遷移させる
			(this->*animExcecuter_)();
		}
		else
		{
			// 何かに当たった時はこっちでHitやDeathが回る
			(this->*stateExcecuter_)();
		}
	}

	// 攻撃の当たり判定----------------------------------------------------------
	// player -> enemy
	if (!isHit_ && animExcecuter_ != &Enemy::Avoidance)
	{
		if (CollisionCheck()(colData_[1].first, player_->GetColliderBox(0).first))
		{
			isHit_ = true;
		}

	}

	// enemy -> player
	if (!player_->GetIsHit())
	{
		if (CollisionCheck()(colData_[0].first, player_->GetColliderBox(1).first))
		{
			player_->SetIsHit(true);
		}
	}
	//---------------------------------------------------------------------------

	// ｱﾆﾒｰｼｮﾝの更新-------------------------------
	UpdateAnimation(currentAction_);
}

void Enemy::Move(void)
{
	// 走るｱﾆﾒｰｼｮﾝに変更
	ChangeAction("Run");
	// 左向きであれば
	if (direction_ == Direction::Left)
	{
		speed_ = { -1.0f,0.0f,0.0f };
	}
	// 右向きであれば
	else
	{
		speed_ = { 1.0f,0.0f,0.0f };
	}
	// 移動処理
	pos_ += speed_;
}

void Enemy::ZMove(void)
{
	// 走るｱﾆﾒｰｼｮﾝに変更
	ChangeAction("Run");
	// 自分のZ軸ﾎﾟｼﾞｼｮﾝの状態(位置状態)
	switch (zPosStatus_)
	{
		// ﾌﾟﾚｲﾔｰよりも手前にいる場合
	case ZPosFromPlayer::Minus:
		speed_ = { 0.0f,0.0f,-0.5f };
		break;
		// ﾌﾟﾚｲﾔｰよりも奥にいる場合
	case ZPosFromPlayer::Plus:
		speed_ = { 0.0f,0.0f,0.5f };

		break;
		// 一致している場合
	case ZPosFromPlayer::Non:
		speed_ = { 0.0f,0.0f,0.0f };

		break;
	default:
		break;
	}
	// Z軸ﾎﾟｼﾞｼｮﾝの移動処理
	pos_.z += speed_.z;
}

void Enemy::Attack(void)
{
	// 通常の攻撃の場合
	if (attackFlag_)
	{
		// 通常攻撃のｱﾆﾒｰｼｮﾝに切り替え
		ChangeAction("Attack");
		// ｱﾆﾒｰｼｮﾝの終了
		if (isAnimEnd_)
		{
			// 攻撃ﾌﾗｸﾞをfalse
			attackFlag_ = false;
			// 回避ﾌﾗｸﾞをfalse
			avoidFromAttackFlag_ = false;
			// ｱﾆﾒｰｼｮﾝをidleに設定(defaultに)
			currentAction_ = "Idle";
		}
	}
	// ｽｷﾙ攻撃の場合
	if (skillAttackFlag_)
	{
		// ｽｷﾙ攻撃のアニメーションに設定
		ChangeAction("SkillAttack");
		
		// ﾀｲﾌﾟ毎のｽｷﾙ攻撃
		SkillAttack(myType_);
		// ｱﾆﾒｰｼｮﾝ終了時
		if (isAnimEnd_)
		{
			// ｽｷﾙ攻撃ﾌﾗｸﾞをfalse
			skillAttackFlag_ = false;
			// 回避ﾌﾗｸﾞをfalseに
			avoidFromAttackFlag_ = false;
			// ｱﾆﾒｰｼｮﾝをidleに(default)
			currentAction_ = "Idle";
		}
	}
}

void Enemy::SkillAttack(ENEMYTYPE type)
{
	// 敵ﾀｲﾌﾟで分岐
	switch (type)
	{
	case ENEMYTYPE::CultistAssassin:
		// ｽｷﾙ攻撃をする時のｱﾆﾒｰｼｮﾝ間隔
		if (animCnt_ >= 8.0f && animCnt_ <= 8.5f)
		{
			// 攻撃をくらわないﾌﾗｸﾞをtrueに
			noAcceptHitFlag_ = true;
			// ﾌﾟﾚｲﾔｰの後ろのﾎﾟｼﾞｼｮﾝの取得
			// ﾌﾟﾚｲﾔｰの後ろに回って攻撃させるので
			pos_ = player_->GetBehindPos();
		}
		break;
	case ENEMYTYPE::Cultist:
		break;
	case ENEMYTYPE::TwistedCultist:
		break;
	case ENEMYTYPE::Max:
		break;
	default:
		break;
	}
}

void Enemy::Avoidance(void)
{
	// 攻撃をかわすｱﾆﾒｰｼｮﾝに変更
	ChangeAction("Avoidance");
	// 回避行動を始めた際、skill、normalの攻撃ﾌﾗｸﾞは折る
	attackFlag_ = false;
	skillAttackFlag_ = false;
	// 回避行動で後ろに下がるﾀｲﾐﾝｸﾞ >> ｱﾆﾒｰｼｮﾝと同期させたいのでﾏｼﾞｯｸﾅﾝﾊﾞｰにしている
	if (animCnt_ >= 1.0f && animCnt_ <= 1.5f)
	{
		// 後ろに下がる予定のﾎﾟｼﾞｼｮﾝ
		auto backPos = pos_;
		// 自分が現在向いている方向
		switch (direction_)
		{
			// 右向きの場合
		case Direction::Right:
			backPos.x = backPos.x - 10.0f;
			break;
			// 左向きの場合
		case Direction::Left:
			backPos.x = backPos.x + 10.0f;
			break;
		case Direction::Max:
			break;
		default:
			break;
		}
		// ﾎﾟｼﾞｼｮﾝの変更
		SetPosition(backPos);
	}
	// ｱﾆﾒｰｼｮﾝ終了時
	if (isAnimEnd_)
	{
		// 回避行動の終了
		avoidFromAttackFlag_ = false;
		// 回避行動が終わればidleに戻す
		animExcecuter_ = &Enemy::Idle;
	}
}

void Enemy::SetEnemy(ENEMYTYPE type,Vector3F pos)
{
	// 敵ﾀｲﾌﾟｾｯﾄ
	myType_ = type;
	// ﾎﾟｼﾞｼｮﾝｾｯﾄ
	pos_ = pos;
	// 敵の生成
	Set(type);
}

void Enemy::SetBehavior(BehaviorTree* behaviorTree)
{
	// 敵ﾀｲﾌﾟに沿ったﾋﾞﾍｲﾋﾞｱﾂﾘｰのｾｯﾄ
	behaviorTree_ = behaviorTree;
}

void Enemy::Set(ENEMYTYPE type)
{
	switch (type)
	{
	case ENEMYTYPE::CultistAssassin:
		// 敵名の設定
		name_ = "Assassin_Cultist";
		// 敵の視界の設定
		visionRange_ = { 300.0f,50.0f };
		// Assassinの場合、ｽｷﾙを持っている
		hasSkill_ = true;
		break;
	case ENEMYTYPE::Cultist:
		// 敵名に設定
		name_ = "Cultist";
		// 敵の視界の設定
		visionRange_ = { 300.0f,150.0f };
		// Cultistの場合はｽｷﾙは持たない
		hasSkill_ = false;
		break;
	case ENEMYTYPE::Max:
		break;
	default:
		break;
	}
	// ｱﾆﾒｰｼｮﾝを初期状態にする
	currentAction_ = "Idle";
	// 奥行にｻｲｽﾞのｾｯﾄ(このｻｲｽﾞをｾｯﾄしないとﾌﾟﾚｲﾔｰの攻撃が当たらない事になってしまう)
	// いわゆる『ペラペラな敵』が出来てしまう
	SetZSize(10);
	// 各種初期化
	Actor::Initialize(name_);
}

const Vector3F& Enemy::GetDistance(void)
{
	// ﾌﾟﾚｲﾔｰのﾎﾟｼﾞｼｮﾝ
	auto plPos = player_->GetPosition();
	// ﾌﾟﾚｲﾔｰとの距離を測っている
	auto distance = plPos - pos_;

	// 同時に方向も変更
	if (distance.x < 0.0f)
	{
		direction_ = Direction::Left;
	}
	else
	{
		direction_ = Direction::Right;
	}

	return distance;
}

// ﾃﾞﾊﾞｯｸﾞを行う際に使用する
void Enemy::DebugDraw(void)
{
	DrawFormatString(0, 50, 0xffffff, "enPos:(%f,%f,%f)", pos_.x, pos_.y, pos_.z);
	DrawFormatString(0, 100, 0xff0000, "enHP:%d", hp_);
}

// Zﾎﾟｼﾞｼｮﾝの状態のｾｯﾄ
void Enemy::SetZPosStatus(ZPosFromPlayer zStatus)
{
	zPosStatus_ = zStatus;
}

void Enemy::SetAnimExcecuter(void(Enemy::* func)())
{
	// ｱﾆﾒｰｼｮﾝ状態管理関数ﾎﾟｲﾝﾀのｾｯﾄ
	animExcecuter_ = func;
}

void Enemy::SetMoveType(MoveType moveType)
{
	// 移動ﾀｲﾌﾟのｾｯﾄ
	// 奥行移動なのか横移動なのか
	moveType_ = moveType;
}
