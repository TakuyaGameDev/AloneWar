#include "Player.h"
#include "../Application.h"
#include "../Controller/Controller.h"
#include "../Loader/SoundLoader.h"

Player::Player(Vector3F pos,int hp):
	Actor(hp)
{
	pos_ = pos;
	// 奥行ｻｲｽﾞのｾｯﾄ
	SetZSize(10);
	updater_ = &Player::Idle;
	Initialize();
}

Player::~Player()
{
}

void Player::Action(void)
{
	// ｽﾋﾟｰﾄﾞを0にしておく
	speed_ = { 0.0f,0.0f,0.0f };
	// 自信の向いている方向によって自身の背後のﾎﾟｼﾞｼｮﾝの変更
	// AssassinのSkillAttackの際の背後に瞬間移動する際に使用する
	if (direction_ == Direction::Right)
	{
		behindPos_ = Vector3F(pos_.x - 10.0f, pos_.y, pos_.z);
	}
	else
	{
		behindPos_ = Vector3F(pos_.x + 10.0f, pos_.y, pos_.z);
	}

	// ｺﾝﾄﾛｰﾗｰ入力
	auto input = lpApp.GetController()->GetCntData();
	for (auto in : input)
	{
		// 移動関係
		if (in.second[static_cast<int>(Trg::Now)])
		{
			if (in.first == InputID::Right)
			{
				// 方向を右向きに
				direction_ = Direction::Right;
				speed_.x = 2.0f;
				// 状態関数ﾎﾟｲﾝﾀをMoveに変更
				updater_ = &Player::Move;
			}
			if (in.first == InputID::Left)
			{
				// 方向を左向きに
				direction_ = Direction::Left;
				speed_.x = -2.0f;
				// 状態関数ﾎﾟｲﾝﾀをMoveに変更
				updater_ = &Player::Move;
			}
			// Z軸方向に移動
			if (in.first == InputID::Up)
			{
				speed_.z = 1.0f;
				// 状態関数ﾎﾟｲﾝﾀをMoveに変更
				updater_ = &Player::Move;
			}
			if (in.first == InputID::Down)
			{
				speed_.z = -1.0f;
				// 状態関数ﾎﾟｲﾝﾀをMoveに変更
				updater_ = &Player::Move;
			}
		}
		// 攻撃関係
		if (in.second[static_cast<int>(Trg::Now)] && !in.second[static_cast<int>(Trg::Old)])
		{
			// lightAttack
			if (in.first == InputID::Button1)
			{
				if (!attackFlag_)
				{
					// 攻撃回数を1加算
					attackCnt_++;
					// lightAttackをtrueに
					lightAttackFlag_ = true;
					// heavyAttackをfalseに
					heavyAttackFlag_ = false;
					// 連撃が可能な制限時間を0初期化
					attackLimTime_ = 0.0f;
					// 攻撃回数が最大の3を超えたら最初の攻撃段階の1に戻す
					if (attackCnt_ > 3)
					{
						attackCnt_ = 1;
					}
					// 状態関数ﾎﾟｲﾝﾀをAttackに変更
					updater_ = &Player::Attack;
				}
			}
			// heavyAttack
			else if (in.first == InputID::Button2)
			{
				if (!attackFlag_)
				{
					// 攻撃回数を1加算
					attackCnt_++;
					// lightAttackをfalseに
					lightAttackFlag_ = false;
					// heavyAttackをtrueに
					heavyAttackFlag_ = true;
					// 連撃が可能な制限時間を0初期化
					attackLimTime_ = 0.0f;
					// 攻撃回数が最大の3を超えたら最初の攻撃段階の1に戻す
					if (attackCnt_ > 3)
					{
						attackCnt_ = 1;
					}
					// 状態関数ﾎﾟｲﾝﾀをAttackに変更
					updater_ = &Player::Attack;
				}
			}
		}
	}

	// 何にも当たっていなければこちらを回す
	if (!isHit_)
	{
		// MoveやらAttackやらの行動の遷移
		(this->*updater_)();
		// ｱﾆﾒｰｼｮﾝの更新
		UpdateAnimation(currentAction_);
		// 攻撃していなくて
		if (!lightAttackFlag_ && !heavyAttackFlag_)
		{
			// 移動もしていなければ
			if (speed_.x == 0.0f && speed_.y == 0.0f && speed_.z == 0.0f)
			{
				// Idle状態に戻す
				updater_ = &Player::Idle;
			}
		}
	}
	else
	{
		lightAttackFlag_ = false;
		heavyAttackFlag_ = false;
		// 何かに当たっている時はHitやらDeathやらの状態遷移
		(this->*stateExcecuter_)();
		// ｱﾆﾒｰｼｮﾝの更新
		UpdateAnimation(currentAction_);
		// ｱﾆﾒｰｼｮﾝが終わっていればIdleに戻す
		if (isAnimEnd_)
		{
			updater_ = &Player::Idle;
		}
	}
}

void Player::Move(void)
{
	// runｱﾆﾒｰｼｮﾝに変更
	ChangeAction("Run");
	// 移動に切り替わったらattackCntを0ｸﾘ
	AttackCntReseter();
	// 攻撃ﾌﾗｸﾞをfalseにする
	attackFlag_ = false;
	// lightAttackもheavyAttackもfalseにする---
	lightAttackFlag_ = false;
	heavyAttackFlag_ = false;
	//-----------------------------------------

	// 移動
	pos_ += speed_;

	// 画面外に出ないように制御----------------
	// 右端
	if (pos_.x >= lpApp.GetViewport().x)
	{
		pos_.x = lpApp.GetViewport().x;
	}
	// 左端
	if (pos_.x <= 0.0f)
	{
		pos_.x = 0.0f;
	}
	// 奥
	if (pos_.z <= 110.0f)
	{
		pos_.z = 110.0f;
	}
	// 手前
	if (pos_.z >= 230.0f)
	{
		pos_.z = 230.0f;
	}
	//-----------------------------------------
}

void Player::Attack(void)
{
	// 攻撃ﾌﾗｸﾞをtrueに
	attackFlag_ = true;
	// lightAttackをしているときの文字列格納
	if (lightAttackFlag_)
	{
		attackStr_ = "LightAttackCombo";
		if (attackCnt_ == 1)
		{
			if (animCnt_ >= 1.0f && animCnt_ <= 1.08f)
			{
				lpSoundLoader.Play("Sounds/lightAttack.mp3");
			}
		}
		else if (attackCnt_ == 2)
		{
			if (animCnt_ >= 1.0f && animCnt_ <= 1.08f)
			{
				lpSoundLoader.Play("Sounds/lightAttack.mp3");
			}
		}
		else if (attackCnt_ == 3)
		{
			if (animCnt_ >= 1.0f && animCnt_ <= 1.08f)
			{
				lpSoundLoader.Play("Sounds/lightAttack.mp3");
			}
		}
	}
	// heavyAttackをしているときの文字列格納
	if (heavyAttackFlag_)
	{
		attackStr_ = "HeavyAttackCombo";
		if (attackCnt_ == 1)
		{
			if (animCnt_ >= 1.0f && animCnt_ <= 1.08f)
			{
				lpSoundLoader.Play("Sounds/heavyAttack.mp3");
			}
		}
		else if (attackCnt_ == 2)
		{
			if (animCnt_ >= 3.0f && animCnt_ <= 3.08f)
			{
				lpSoundLoader.Play("Sounds/heavyAttack.mp3");
			}
		}
		else if (attackCnt_ == 3)
		{
			if (animCnt_ >= 4.5f && animCnt_ <= 4.6f)
			{
				lpSoundLoader.Play("Sounds/heavyAttack.mp3");
			}
		}
	}
	//lightAttack、heavyAttackへｱﾆﾒｰｼｮﾝの変更
	ChangeAction(attackStr_ + std::to_string(attackCnt_));
	// ｱﾆﾒｰｼｮﾝの終了時
	if (isAnimEnd_)
	{
		// 攻撃ﾌﾗｸﾞをfalseに
		attackFlag_ = false;
		// 連撃可能な制限時間を加算
		attackLimTime_ += 0.2f;
	}
	// 連撃可能な時間が最大制限時間を過ぎたら
	if (attackLimTime_ >= DefAttackLimTime)
	{
		// Idleに戻す
		updater_ = &Player::Idle;
		// 連撃可能時間を0にする
		attackLimTime_ = 0.0f;
		// 攻撃ﾌﾗｸﾞをfalseにする
		attackFlag_ = false;
		// lightAttack、heavyAttackをfalseにする---------
		lightAttackFlag_ = false;
		heavyAttackFlag_ = false;
		//-----------------------------------------------
		// 攻撃ｶｳﾝﾄのﾘｾｯﾄ
		AttackCntReseter();
	}
}

bool Player::Initialize(void)
{
	// 取得したﾃﾞｰﾀを文字列で取得し、
	// その文字列に対応したﾃﾞｰﾀで初期化
	Actor::Initialize("player");
	// 攻撃回数の初期化
	attackCnt_ = 0;
	// 連撃制限時間の初期化
	attackLimTime_ = 0.0f;
	// 攻撃ﾌﾗｸﾞの初期化
	attacking_ = false;
	// lightAttack、heavyAttackの初期化
	lightAttackFlag_ = false;
	heavyAttackFlag_ = false;
	// 生きているﾌﾗｸﾞの初期化
	isAlive_ = true;
	// 現在のｱｸｼｮﾝをIdleに初期化
	currentAction_ = "Idle";
	return true;
}

void Player::DebugDraw(void)
{
	DrawFormatString(0, 0, 0xffffff, "plPos:(%f,%f,%f)", pos_.x, pos_.y, pos_.z);
}

void Player::AttackCntReseter(void)
{
	attackCnt_ = 0;
}
