#include "Player.h"
#include "../Application.h"
#include "../Controller/Controller.h"
#include "../Loader/SoundLoader.h"

Player::Player(Vector3F pos,int hp):
	Actor(hp)
{
	pos_ = pos;
	// ���s���ނ̾��
	SetZSize(10);
	updater_ = &Player::Idle;
	Initialize();
}

Player::~Player()
{
}

void Player::Action(void)
{
	// ��߰�ނ�0�ɂ��Ă���
	speed_ = { 0.0f,0.0f,0.0f };
	// ���M�̌����Ă�������ɂ���Ď��g�̔w����߼޼�݂̕ύX
	// Assassin��SkillAttack�̍ۂ̔w��ɏu�Ԉړ�����ۂɎg�p����
	if (direction_ == Direction::Right)
	{
		behindPos_ = Vector3F(pos_.x - 10.0f, pos_.y, pos_.z);
	}
	else
	{
		behindPos_ = Vector3F(pos_.x + 10.0f, pos_.y, pos_.z);
	}

	// ���۰װ����
	auto input = lpApp.GetController()->GetCntData();
	for (auto in : input)
	{
		// �ړ��֌W
		if (in.second[static_cast<int>(Trg::Now)])
		{
			if (in.first == InputID::Right)
			{
				// �������E������
				direction_ = Direction::Right;
				speed_.x = 2.0f;
				// ��Ԋ֐��߲����Move�ɕύX
				updater_ = &Player::Move;
			}
			if (in.first == InputID::Left)
			{
				// ��������������
				direction_ = Direction::Left;
				speed_.x = -2.0f;
				// ��Ԋ֐��߲����Move�ɕύX
				updater_ = &Player::Move;
			}
			// Z�������Ɉړ�
			if (in.first == InputID::Up)
			{
				speed_.z = 1.0f;
				// ��Ԋ֐��߲����Move�ɕύX
				updater_ = &Player::Move;
			}
			if (in.first == InputID::Down)
			{
				speed_.z = -1.0f;
				// ��Ԋ֐��߲����Move�ɕύX
				updater_ = &Player::Move;
			}
		}
		// �U���֌W
		if (in.second[static_cast<int>(Trg::Now)] && !in.second[static_cast<int>(Trg::Old)])
		{
			// lightAttack
			if (in.first == InputID::Button1)
			{
				if (!attackFlag_)
				{
					// �U���񐔂�1���Z
					attackCnt_++;
					// lightAttack��true��
					lightAttackFlag_ = true;
					// heavyAttack��false��
					heavyAttackFlag_ = false;
					// �A�����\�Ȑ������Ԃ�0������
					attackLimTime_ = 0.0f;
					// �U���񐔂��ő��3�𒴂�����ŏ��̍U���i�K��1�ɖ߂�
					if (attackCnt_ > 3)
					{
						attackCnt_ = 1;
					}
					// ��Ԋ֐��߲����Attack�ɕύX
					updater_ = &Player::Attack;
				}
			}
			// heavyAttack
			else if (in.first == InputID::Button2)
			{
				if (!attackFlag_)
				{
					// �U���񐔂�1���Z
					attackCnt_++;
					// lightAttack��false��
					lightAttackFlag_ = false;
					// heavyAttack��true��
					heavyAttackFlag_ = true;
					// �A�����\�Ȑ������Ԃ�0������
					attackLimTime_ = 0.0f;
					// �U���񐔂��ő��3�𒴂�����ŏ��̍U���i�K��1�ɖ߂�
					if (attackCnt_ > 3)
					{
						attackCnt_ = 1;
					}
					// ��Ԋ֐��߲����Attack�ɕύX
					updater_ = &Player::Attack;
				}
			}
		}
	}

	// ���ɂ��������Ă��Ȃ���΂��������
	if (!isHit_)
	{
		// Move���Attack���̍s���̑J��
		(this->*updater_)();
		// ��Ұ��݂̍X�V
		UpdateAnimation(currentAction_);
		// �U�����Ă��Ȃ���
		if (!lightAttackFlag_ && !heavyAttackFlag_)
		{
			// �ړ������Ă��Ȃ����
			if (speed_.x == 0.0f && speed_.y == 0.0f && speed_.z == 0.0f)
			{
				// Idle��Ԃɖ߂�
				updater_ = &Player::Idle;
			}
		}
	}
	else
	{
		lightAttackFlag_ = false;
		heavyAttackFlag_ = false;
		// �����ɓ������Ă��鎞��Hit���Death���̏�ԑJ��
		(this->*stateExcecuter_)();
		// ��Ұ��݂̍X�V
		UpdateAnimation(currentAction_);
		// ��Ұ��݂��I����Ă����Idle�ɖ߂�
		if (isAnimEnd_)
		{
			updater_ = &Player::Idle;
		}
	}
}

void Player::Move(void)
{
	// run��Ұ��݂ɕύX
	ChangeAction("Run");
	// �ړ��ɐ؂�ւ������attackCnt��0��
	AttackCntReseter();
	// �U���׸ނ�false�ɂ���
	attackFlag_ = false;
	// lightAttack��heavyAttack��false�ɂ���---
	lightAttackFlag_ = false;
	heavyAttackFlag_ = false;
	//-----------------------------------------

	// �ړ�
	pos_ += speed_;

	// ��ʊO�ɏo�Ȃ��悤�ɐ���----------------
	// �E�[
	if (pos_.x >= lpApp.GetViewport().x)
	{
		pos_.x = lpApp.GetViewport().x;
	}
	// ���[
	if (pos_.x <= 0.0f)
	{
		pos_.x = 0.0f;
	}
	// ��
	if (pos_.z <= 110.0f)
	{
		pos_.z = 110.0f;
	}
	// ��O
	if (pos_.z >= 230.0f)
	{
		pos_.z = 230.0f;
	}
	//-----------------------------------------
}

void Player::Attack(void)
{
	// �U���׸ނ�true��
	attackFlag_ = true;
	// lightAttack�����Ă���Ƃ��̕�����i�[
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
	// heavyAttack�����Ă���Ƃ��̕�����i�[
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
	//lightAttack�AheavyAttack�ֱ�Ұ��݂̕ύX
	ChangeAction(attackStr_ + std::to_string(attackCnt_));
	// ��Ұ��݂̏I����
	if (isAnimEnd_)
	{
		// �U���׸ނ�false��
		attackFlag_ = false;
		// �A���\�Ȑ������Ԃ����Z
		attackLimTime_ += 0.2f;
	}
	// �A���\�Ȏ��Ԃ��ő吧�����Ԃ��߂�����
	if (attackLimTime_ >= DefAttackLimTime)
	{
		// Idle�ɖ߂�
		updater_ = &Player::Idle;
		// �A���\���Ԃ�0�ɂ���
		attackLimTime_ = 0.0f;
		// �U���׸ނ�false�ɂ���
		attackFlag_ = false;
		// lightAttack�AheavyAttack��false�ɂ���---------
		lightAttackFlag_ = false;
		heavyAttackFlag_ = false;
		//-----------------------------------------------
		// �U�����Ă�ؾ��
		AttackCntReseter();
	}
}

bool Player::Initialize(void)
{
	// �擾�����ް��𕶎���Ŏ擾���A
	// ���̕�����ɑΉ������ް��ŏ�����
	Actor::Initialize("player");
	// �U���񐔂̏�����
	attackCnt_ = 0;
	// �A���������Ԃ̏�����
	attackLimTime_ = 0.0f;
	// �U���׸ނ̏�����
	attacking_ = false;
	// lightAttack�AheavyAttack�̏�����
	lightAttackFlag_ = false;
	heavyAttackFlag_ = false;
	// �����Ă����׸ނ̏�����
	isAlive_ = true;
	// ���݂̱���݂�Idle�ɏ�����
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
