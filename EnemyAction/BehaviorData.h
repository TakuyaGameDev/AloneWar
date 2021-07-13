#pragma once

#include <vector>
#include <stack>
#include <map>
#include <string>

class ActionNode;
class Enemy;

// ﾋﾞﾍｲﾋﾞｱﾂﾘｰﾃﾞｰﾀ
class BehaviorData
{
public:
	BehaviorData();
	~BehaviorData();
	// ﾋﾞﾍｲﾋﾞｱﾃﾞｰﾀの初期化
	void Init(void);
	// ｼｰｹﾝｽﾉｰﾄﾞのﾌﾟｯｼｭ
	void PushSequenceNode(ActionNode* node);
	// ｼｰｹﾝｽﾉｰﾄﾞのﾎﾟｯﾌﾟ
	// 中身の取り出し
	ActionNode* PopSequenceNode(void);
	// ﾉｰﾄﾞの使用判定
	bool IsUsedNode(std::string nodeName);
	// 使用済みﾉｰﾄﾞに登録
	void EntryUsedNode(std::string nodeName);
	// ｼｰｹﾝｽｽﾃｯﾌﾟの取得
	int GetSequenceStep(std::string nodeName);
	// ｼｰｹﾝｽｽﾃｯﾌﾟのｾｯﾄ
	void SetSequenceStep(std::string nodeName, int step);
	// 使用済みﾉｰﾄﾞのﾘｾｯﾄ
	void ResetNodeUsed(std::vector<ActionNode*>* resetHieralchy);
private:
	// ｼｰｹﾝｽﾉｰﾄﾞｽﾀｯｸ
	std::stack<ActionNode*> sequenceStack_;
	// 実行ｼｰｹﾝｽのｽﾃｯﾌﾟﾏｯﾌﾟ
	std::map<std::string, int> runSequenceStepMap_;
	// ﾉｰﾄﾞの使用判定ﾏｯﾌﾟ
	std::map<std::string, bool> usedNodeMap_;
};

