#pragma once
#include <list>
#include <map>
#include <string>
#include <vector>

#include "Judgement/JudgementBase.h"
#include "Action/ActionBase.h"
#include "BehaviorTree.h"

// 優先度をとりあえず一番小さい数にしておく
#define DefPriority -100000

class Enemy;
class ActionNode;
class BehaviorData;

// ﾋﾞﾍｲﾋﾞｱﾉｰﾄﾞ(思考ﾉｰﾄﾞ)ｸﾗｽ
class ActionNode
{
public:
	// param@ nodeName:ｾｯﾄするﾉｰﾄﾞ名
	// param@ parent:親となるﾉｰﾄﾞ
	// param@ sibling:兄弟となるﾉｰﾄﾞ
	// param@ priority:優先度
	// param@ rule:ﾂﾘｰから思考ﾉｰﾄﾞが選択される際の選択基準となるﾙｰﾙ
	// param@ judgement:行動の判定
	// param@ action:行動実行
	ActionNode(std::string nodeName,ActionNode* parent,ActionNode* sibling,int priority,BehaviorTree::SelectRule rule,JudgementBase* judgement,ActionBase* action);
	// ﾉｰﾄﾞ推論
	ActionNode* Inference(Enemy* enemy,BehaviorData* data);
	// ﾉｰﾄﾞの捜索
	ActionNode* SearchActionNode(std::string nodeName);
	// 自分の子供に追加
	void AddChild(ActionNode* childNode);
	// 末尾を取得
	ActionNode* GetLastChild(void);
	// 判定
	bool Judgement(Enemy* enemy);
	// 優先度の取得
	const int& GetPriority(void)
	{
		return priority_;
	}
	// 実行ﾃﾞｰﾀをもっているか
	bool HasAction(void);
	// 実行
	void Run(Enemy* enemy);

	// ﾉｰﾄﾞﾈｰﾑの取得
	std::string GetNodeName(void)
	{
		return nodeName_;
	}

private:

protected:
	// ﾉｰﾄﾞの名前
	std::string nodeName_;
	// 自分の子ﾉｰﾄﾞ
	std::vector<ActionNode*> child_;
	// 自分の親ﾉｰﾄﾞ
	ActionNode* parent_;
	// 自分の兄弟ﾉｰﾄﾞ
	ActionNode* sibling_;
	// 実行ﾉｰﾄﾞ
	ActionBase* action_;
	// 判定ﾉｰﾄﾞ
	JudgementBase* judgement_;
	// 選択法
	BehaviorTree::SelectRule selectRule_;
	// 優先度
	int priority_;
};

