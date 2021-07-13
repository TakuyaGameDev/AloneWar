#pragma once

#include <string>

struct JudgementBase;
class BehaviorData;
struct ActionBase;
class Enemy;
class ActionNode;
// 思考ﾙｰﾁﾝの木ﾃﾞｰﾀｸﾗｽ
class BehaviorTree
{
public:
	// 選択ルール
	enum SelectRule
	{
		Non,
		// 優先順位
		Priority,			
		// ｼｰｹﾝｽ
		Sequence,			
		// ｼｰｹﾝｼｬﾙﾙｰﾋﾟﾝｸﾞ
		SequencialLooping,	
		// ﾗﾝﾀﾞﾑ
		Random,				
		// ｵﾝ・ｵﾌ
		On_Off,
	};

	BehaviorTree();
	~BehaviorTree();
	// behaiviorTreeへのﾉｰﾄﾞの追加
	void AddNode(std::string searchName, std::string entryName,int priority,SelectRule selectRule, JudgementBase* judgement, ActionBase* action);
	// ﾉｰﾄﾞの推論
	ActionNode* Inference(Enemy* enemy,BehaviorData* data);
	// ｼｰｹﾝｽﾉｰﾄﾞから推論
	ActionNode* SequenceInference(ActionNode* sequenceNode, Enemy* enemy, BehaviorData* data);
	// 実行
	void Run(Enemy* enemy,ActionNode* actionNode,BehaviorData* data);
private:
	// ﾙｰﾄ(ﾉｰﾄﾞの一番最初)
	ActionNode* root_;
};

