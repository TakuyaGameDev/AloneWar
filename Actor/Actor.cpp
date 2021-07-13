#include "Actor.h"
#include "../Loader/ImageLoader.h"
#include "../Application.h"

Actor::Actor(int hp):maxHP_(hp)
{
	isAnimEnd_ = false;
	flipX_ = false;
	onDamaged_ = false;
	attackFlag_ = false;
	skillAttackFlag_ = false;
	isHit_ = false;
	onFloor_ = false;
	avoidFromAttackFlag_ = false;
	animCnt_ = 0.0f;
	gravity_ = 0.0f;
	stateExcecuter_ = &Actor::State_Hit;
}

Actor::~Actor()
{
}

void Actor::Update(void)
{
	// 重力をかける
	gravity_ += GRAVITY;
	pos_.y -= gravity_;
	if (pos_.y <= 0.0f)
	{
		onFloor_ = true;
		pos_.y = 0.0f;
	}
	// 当たり判定ﾎﾞｯｸｽのｾｯﾄ
	SetColliderBox();

	Action();
	SetFlip();
}

void Actor::Idle(void)
{
	ChangeAction("Idle");
}

bool Actor::Initialize(std::string name)
{
	auto data = lpDataCache.GetAtlusData(name);
	lpImageLoader.Loader(data);
	auto size = lpDataCache.GetAtlusData(name).divSize_;
	size_ = { size.x,size.y,zSize_ };
	// HPの初期化
	hp_ = maxHP_;
	name_ = name;
	return true;
}

void Actor::ChangeAction(std::string action)
{
	if (currentAction_ == action)
	{
		return;
	}
	currentAction_ = action;
	isAnimEnd_ = false;
	animCnt_ = 0.0f;
}

void Actor::UpdateAnimation(std::string action)
{
	// 各ｷｬﾗｸﾀｰのｱﾆﾒｰｼｮﾝﾃﾞｰﾀの取得
	auto animSet = lpDataCache.GetAnimationData(name_, action);
	// ｱﾆﾒｰｼｮﾝｶｳﾝﾄ加算
	animCnt_ += animSet.duration_;
	// ｱﾆﾒｰｼｮﾝｶｳﾝﾄが現在のｱﾆﾒｰｼｮﾝの最大ﾌﾚｰﾑより大きければ
	if (animCnt_ > animSet.frame_ - 1)
	{
		// ﾙｰﾌﾟﾌﾗｸﾞがtrueなら
		if (animSet.isLoop_)
		{
			// ｱﾆﾒｰｼｮﾝｶｳﾝﾄを0ｸﾘしてまた最初から再生
			animCnt_ = 0.0f;
		}
		else
		{
			if ((action.find("LightAttackCombo") != -1) ||
				(action.find("HeavyAttackCombo") != -1))
			{
				animCnt_ = animSet.frame_ - 1;
			}
			// ﾙｰﾌﾟﾌﾗｸﾞがfalseならｱﾆﾒｰｼｮﾝが終わった事を表すﾌﾗｸﾞをtrueに
			isAnimEnd_ = true;
		}
	}
}

void Actor::Draw(void)
{
	// 自身の描画
	DrawBillboard3D(VGet(pos_.x, pos_.y, pos_.z),0.5f,0.5f,size_.x, 0.0f, lpImageLoader.GetActorHandles(name_,currentAction_)[animCnt_], true,flipX_);
}

void Actor::SetPosition(Vector3F newPos)
{
	pos_ = newPos;
}

void Actor::SetFlip(void)
{
	switch (direction_)
	{
	case Direction::Right:
		flipX_ = true;
		break;
	case Direction::Left:
		flipX_ = false;
		break;
	case Direction::Max:
		break;
	default:
		break;
	}
}

void Actor::SetAlive(bool aliveFlg)
{
	isAlive_ = aliveFlg;
}

void Actor::ResetColliderBoxData(void)
{
	for (auto& col : colData_)
	{
		col.first.pos_ = { 0.0f,0.0f,0.0f };
		col.first.size_ = { 0,0,0 };
	}
}

void Actor::SetZSize(int zSize)
{
	zSize_ = zSize;
}

void Actor::SetColliderBox(void)
{
	// attackCol,damageColの0ｸﾘ
	ResetColliderBoxData();
	// ｺﾗｲﾀﾞｰﾎﾞｯｸｽﾃﾞｰﾀの取得
	currentColliderBox_ = lpDataCache.GetColliderData(name_, currentAction_, animCnt_);
	// 現在のｱﾆﾒｰｼｮﾝ、そのﾌﾚｰﾑでのｺﾗｲﾀﾞｰﾎﾞｯｸｽで回す
	for (auto&& col : currentColliderBox_.colRect_)
	{
		// 自分の矩形状態の格納
		colData_[col.rectType_].second = col.rectType_;
		// 攻撃矩形 : 0 当たり矩形 : 1
		colData_[col.rectType_].first.size_ = { col.size_.x,col.size_.y,10 };

		if (direction_ == Direction::Left)
		{
			colData_[col.rectType_].first.pos_
				= { pos_.x + col.beginPos_.x + (col.size_.x / 2),
					pos_.y + (-col.beginPos_.y) - (col.size_.y / 2),pos_.z - (colData_[col.rectType_].first.size_.z / 2) };
		}
		else
		{
			colData_[col.rectType_].first.pos_ 
				= { pos_.x - col.beginPos_.x - (col.size_.x / 2),
					pos_.y + (-col.beginPos_.y) - (col.size_.y / 2),pos_.z - (colData_[col.rectType_].first.size_.z / 2) };
		}
	}
}

void Actor::SetHP(int hp)
{
	maxHP_ = hp;
}

void Actor::SetOnDamaged(bool flg)
{
	onDamaged_ = flg;
}

void Actor::SetIsHit(bool flg)
{
	isHit_ = flg;
}

void Actor::SetAttackFlag(bool flg)
{
	attackFlag_ = flg;
}

void Actor::SetSkillAttackFlag(bool flg)
{
	skillAttackFlag_ = flg;
}

void Actor::DebugColliderDraw(void)
{
	for (auto col : colData_)
	{
		// 攻撃矩形の描画
		DrawCube3D(VGet(col.first.pos_.x + (col.first.size_.x / 2),
			col.first.pos_.y - (col.first.size_.y / 2),
			col.first.pos_.z - (col.first.size_.z / 2)),
			VGet(col.first.pos_.x - (col.first.size_.x / 2),
				col.first.pos_.y + (col.first.size_.y / 2),
				col.first.pos_.z + (col.first.size_.z / 2)),
			(col.second == 0 ? 0xff0000 : 0x0000ff),
			0xffffff, false);
	}
}

void Actor::State_Hit(void)
{
	ChangeAction("Hit");

	if (!onDamaged_)
	{
		hp_--;
		onDamaged_ = true;
	}
	if (hp_ <= 0)
	{
		stateExcecuter_ = &Actor::State_Death;
	}

	if (isAnimEnd_)
	{
		isHit_ = false;
		attackFlag_ = false;
		// 回避ﾌﾗｸﾞをfalseに
		avoidFromAttackFlag_ = false;
		onDamaged_ = false;
	}
}

void Actor::State_Death(void)
{
	ChangeAction("Death");

	if (isAnimEnd_)
	{
		isHit_ = false;
		animCnt_ = 0.0f;
		gravity_ = 0.0f;
		stateExcecuter_ = &Actor::State_Hit;
		SetAlive(false);
	}
}

bool Actor::IsHPPercentOver(int checkPercent)
{
	int percent = hp_ / maxHP_;

	if ((percent * 100) >= checkPercent)
	{
		return true;
	}

	return false;
}
