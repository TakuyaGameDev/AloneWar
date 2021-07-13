#pragma once
#include "Actor.h"

#define DefAttackLimTime 15.0f

class Player :
    public Actor
{
public:
    Player(Vector3F pos,int hp);
    ~Player();

    void Action(void);
    void Move(void);
    void Attack(void);

    bool Initialize(void);
    // �����̔w����߼޼�݂̎擾
    const Vector3F& GetBehindPos(void)
    {
        return behindPos_;
    }
    void DebugDraw(void);
private:

    // LightAttackCombo HeavyAttackCombo �̉񐔂�ؾ��
    void AttackCntReseter(void);
    // lightAttack�����Ă����׸�
    // ���ꂪtrue�̏ꍇ��heavyAttackFlag��false�ƂȂ�
    bool lightAttackFlag_;
    // heavyAttack�����Ă����׸�
    // ���ꂪtrue�̏ꍇ��lightAttackFlag��false�ƂȂ�
    bool heavyAttackFlag_;
    // heavyAttack�����Ă���ꍇ:"HeavyAttackCombo"
    // lightAttack�����Ă���ꍇ:"LightAttackCombo"
    std::string attackStr_;
    // ���M�̍s���̎��s�֐��߲��
    void(Player::* updater_)(void);

    // �����̔w����߼޼��
    Vector3F behindPos_;

    // �U�������Ă����
    // �ő�3
    int attackCnt_;
    // �U��Ӱ��ݒ����ǂ���
    bool attacking_;
    // �U�����̐������Ă𒴂�����true�ɂȂ菉����Ұ���(Idle)�ɖ߂��׸�
    bool attackResetFlag_;
    // idle��ԂɂȂ��Ă��邩���׸�
    bool idleFlag_;
    // �U��Ӱ��݂̎�t����
    // ���ȏゾ��idle�ɖ߂�
    float attackLimTime_;
};

