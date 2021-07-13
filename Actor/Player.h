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
    // ©•ª‚Ì”wŒã‚ÌÎß¼Ş¼®İ‚Ìæ“¾
    const Vector3F& GetBehindPos(void)
    {
        return behindPos_;
    }
    void DebugDraw(void);
private:

    // LightAttackCombo HeavyAttackCombo ‚Ì‰ñ”‚ÌØ¾¯Ä
    void AttackCntReseter(void);
    // lightAttack‚ğ‚µ‚Ä‚¢‚éÌ×¸Ş
    // ‚±‚ê‚ªtrue‚Ìê‡‚ÍheavyAttackFlag‚Ífalse‚Æ‚È‚é
    bool lightAttackFlag_;
    // heavyAttack‚ğ‚µ‚Ä‚¢‚éÌ×¸Ş
    // ‚±‚ê‚ªtrue‚Ìê‡‚ÍlightAttackFlag‚Ífalse‚Æ‚È‚é
    bool heavyAttackFlag_;
    // heavyAttack‚ğ‚µ‚Ä‚¢‚éê‡:"HeavyAttackCombo"
    // lightAttack‚ğ‚µ‚Ä‚¢‚éê‡:"LightAttackCombo"
    std::string attackStr_;
    // ©M‚Ìs“®‚ÌÀsŠÖ”Îß²İÀ
    void(Player::* updater_)(void);

    // ©•ª‚Ì”wŒã‚ÌÎß¼Ş¼®İ
    Vector3F behindPos_;

    // UŒ‚‚ğ‚µ‚Ä‚¢‚é‰ñ”
    // Å‘å3
    int attackCnt_;
    // UŒ‚Ó°¼®İ’†‚©‚Ç‚¤‚©
    bool attacking_;
    // UŒ‚’†‚Ì§ŒÀ¶³İÄ‚ğ’´‚¦‚½‚çtrue‚É‚È‚è‰Šú±ÆÒ°¼®İ(Idle)‚É–ß‚éÌ×¸Ş
    bool attackResetFlag_;
    // idleó‘Ô‚É‚È‚Á‚Ä‚¢‚é‚©‚ÌÌ×¸Ş
    bool idleFlag_;
    // UŒ‚Ó°¼®İ‚Ìó•tŠÔ
    // ˆê’èˆÈã‚¾‚Æidle‚É–ß‚é
    float attackLimTime_;
};

