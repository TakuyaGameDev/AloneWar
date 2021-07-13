#pragma once
#include <DxLib.h>
#include <array>
#include <memory>
#include <string>
#include <map>
#include "../Geometory.h"
#include "../DataCache.h"

// 毎ﾌﾚｰﾑ加算する重力値
#define GRAVITY 0.1f

class Controller;

enum class Direction
{
	Right,
	Left,
	Max
};

// 当たり判定用ﾎﾞｯｸｽの情報を格納
// first : ﾎﾞｯｸｽのﾎﾟｼﾞｼｮﾝやｻｲｽﾞ情報
// second : ﾎﾞｯｸｽのﾀｲﾌﾟ(攻撃矩形かくらい矩形か)
using BoxData = std::pair<BoxRect, char>;

class Actor
{
public:
	Actor(int hp);
	virtual ~Actor();
	// 更新
	virtual void Update(void);
	virtual void Action(void) = 0;
	// 各ｸﾗｽの動き
	virtual void Move(void) = 0;
	virtual void Idle(void);
	// 共通しての初期化
	bool Initialize(std::string name);
	// 各初期化
	virtual bool Initialize(void) = 0;
	// ｱﾆﾒｰｼｮﾝの変更
	void ChangeAction(std::string action);
	// ｱﾆﾒｰｼｮﾝの更新
	virtual void UpdateAnimation(std::string action);

	virtual const BoxData& GetColliderBox(char typeNo)
	{
		return colData_[typeNo];
	}

	// 描画
	virtual void Draw(void);
	// ﾃﾞﾊﾞｯｸﾞ表示用
	virtual void DebugDraw(void) = 0;
	// ﾎﾟｼﾞｼｮﾝｾｯﾄ
	void SetPosition(Vector3F newPos);
	// ﾎﾟｼﾞｼｮﾝ取得
	virtual const Vector3F& GetPosition(void)
	{
		return pos_;
	}
	// 右向き、左向きに分けて反転ﾌﾗｸﾞを切り替える
	void SetFlip(void);
	// 生きている事のｾｯﾄ
	void SetAlive(bool aliveFlg);
	// 生きているかのﾌﾗｸﾞの取得
	const bool& GetAlive(void)
	{
		return isAlive_;
	}
	// 各ｺﾗｲﾀﾞｰﾎﾞｯｸｽのﾃﾞｰﾀのﾘｾｯﾄ
	void ResetColliderBoxData(void);
	// ｷｬﾗｸﾀｰのｻｲｽﾞｾｯﾄ
	void SetZSize(int zSize);

	void SetColliderBox(void);

	void SetHP(int hp);
	// 攻撃
	virtual void Attack(void) = 0;
	// ﾀﾞﾒｰｼﾞをくらったﾌﾗｸﾞのｾｯﾄ
	void SetOnDamaged(bool flg);
	// 攻撃が当たったﾌﾗｸﾞのｾｯﾄ
	void SetIsHit(bool flg);
	// 攻撃が当たったﾌﾗｸﾞの取得
	const bool& GetIsHit(void)
	{
		return isHit_;
	}

	void SetAttackFlag(bool flg);
	void SetSkillAttackFlag(bool flg);
	// 回避行動のﾌﾗｸﾞのｾｯﾄ
	void SetAvoidFlag(bool flg)
	{
		avoidFromAttackFlag_ = flg;
	}
	// 回避行動ﾌﾗｸﾞの取得
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
	// 当たり判定ﾎﾞｯｸｽの描画
	void DebugColliderDraw(void);

	// hit状態
	virtual void State_Hit(void);
	// death状態
	virtual void State_Death(void);
	// HPｵｰﾊﾞｰ判定
	bool IsHPPercentOver(int checkPercent);
private:
protected:
	Vector3F pos_;
	Vector3F speed_;
	Vector3I size_;
	// 状態の遷移をさせる関数ﾎﾟｲﾝﾀ
	void(Actor::* stateExcecuter_)(void);

	// 奥行のｻｲｽﾞ
	int zSize_;
	Direction direction_;

	std::string name_;
	std::string currentAction_;
	// 今現在の当たり判定を取る箱情報
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
	// 相手の攻撃からの回避行動のﾌﾗｸﾞ
	bool avoidFromAttackFlag_;

	bool onFloor_;

	float animCnt_;

	// hp
	int hp_;
	// 最大HP
	int maxHP_;
	// 重力速度変数
	float gravity_;
};

