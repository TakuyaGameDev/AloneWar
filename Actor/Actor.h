#pragma once
#include <DxLib.h>
#include <array>
#include <memory>
#include <string>
#include <map>
#include "../Geometory.h"
#include "../DataCache.h"

// ���ڰщ��Z����d�͒l
#define GRAVITY 0.1f

class Controller;

enum class Direction
{
	Right,
	Left,
	Max
};

// �����蔻��p�ޯ���̏����i�[
// first : �ޯ�����߼޼�݂⻲�ޏ��
// second : �ޯ��������(�U����`�����炢��`��)
using BoxData = std::pair<BoxRect, char>;

class Actor
{
public:
	Actor(int hp);
	virtual ~Actor();
	// �X�V
	virtual void Update(void);
	virtual void Action(void) = 0;
	// �e�׽�̓���
	virtual void Move(void) = 0;
	virtual void Idle(void);
	// ���ʂ��Ă̏�����
	bool Initialize(std::string name);
	// �e������
	virtual bool Initialize(void) = 0;
	// ��Ұ��݂̕ύX
	void ChangeAction(std::string action);
	// ��Ұ��݂̍X�V
	virtual void UpdateAnimation(std::string action);

	virtual const BoxData& GetColliderBox(char typeNo)
	{
		return colData_[typeNo];
	}

	// �`��
	virtual void Draw(void);
	// ���ޯ�ޕ\���p
	virtual void DebugDraw(void) = 0;
	// �߼޼�ݾ��
	void SetPosition(Vector3F newPos);
	// �߼޼�ݎ擾
	virtual const Vector3F& GetPosition(void)
	{
		return pos_;
	}
	// �E�����A�������ɕ����Ĕ��]�׸ނ�؂�ւ���
	void SetFlip(void);
	// �����Ă��鎖�̾��
	void SetAlive(bool aliveFlg);
	// �����Ă��邩���׸ނ̎擾
	const bool& GetAlive(void)
	{
		return isAlive_;
	}
	// �e�ײ�ް�ޯ�����ް���ؾ��
	void ResetColliderBoxData(void);
	// ��׸���̻��޾��
	void SetZSize(int zSize);

	void SetColliderBox(void);

	void SetHP(int hp);
	// �U��
	virtual void Attack(void) = 0;
	// ��Ұ�ނ���������׸ނ̾��
	void SetOnDamaged(bool flg);
	// �U�������������׸ނ̾��
	void SetIsHit(bool flg);
	// �U�������������׸ނ̎擾
	const bool& GetIsHit(void)
	{
		return isHit_;
	}

	void SetAttackFlag(bool flg);
	void SetSkillAttackFlag(bool flg);
	// ����s�����׸ނ̾��
	void SetAvoidFlag(bool flg)
	{
		avoidFromAttackFlag_ = flg;
	}
	// ����s���׸ނ̎擾
	const bool& GetAvoidFlag(void)
	{
		return avoidFromAttackFlag_;
	}

	const bool& GetAttackFlag(void)
	{
		return attackFlag_;
	}

	const bool& GetSkillAttackFlag(void)
	{
		return skillAttackFlag_;
	}
	// �����蔻���ޯ���̕`��
	void DebugColliderDraw(void);

	// hit���
	virtual void State_Hit(void);
	// death���
	virtual void State_Death(void);
	// HP���ް����
	bool IsHPPercentOver(int checkPercent);
private:
protected:
	Vector3F pos_;
	Vector3F speed_;
	Vector3I size_;
	// ��Ԃ̑J�ڂ�������֐��߲��
	void(Actor::* stateExcecuter_)(void);

	// ���s�̻���
	int zSize_;
	Direction direction_;

	std::string name_;
	std::string currentAction_;
	// �����݂̓����蔻�����锠���
	ColliderBoxData currentColliderBox_;

	BoxRect attackCol_;
	BoxRect damageCol_;

	std::array<BoxData, 2> colData_;

	bool flipX_;
	bool isAnimEnd_;
	bool isAlive_;
	bool isHit_;
	bool onDamaged_;
	bool attackFlag_;
	bool skillAttackFlag_;
	// ����̍U������̉���s�����׸�
	bool avoidFromAttackFlag_;

	bool onFloor_;

	float animCnt_;

	// hp
	int hp_;
	// �ő�HP
	int maxHP_;
	// �d�͑��x�ϐ�
	float gravity_;
};

