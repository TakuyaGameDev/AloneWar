#include "BehaviorData.h"
#include "BehaviorTree.h"
#include "ActionNode.h"

BehaviorData::BehaviorData()
{
	// ﾋﾞﾍｲﾋﾞｱﾃﾞｰﾀの初期化
	Init();
}

BehaviorData::~BehaviorData()
{
}

void BehaviorData::Init(void)
{
	runSequenceStepMap_.clear();
	while (sequenceStack_.size() > 0)
	{
		sequenceStack_.pop();
	}
}

void BehaviorData::PushSequenceNode(ActionNode* node)
{
	sequenceStack_.push(node);
}

ActionNode* BehaviorData::PopSequenceNode(void)
{
	// 中身がないならnullptrを返す
	if (sequenceStack_.empty())
	{
		return nullptr;
	}
	ActionNode* node = sequenceStack_.top();

	// 取り出したﾃﾞｰﾀがnullptrでなければ
	if (node != nullptr)
	{
		// 取り出したﾃﾞｰﾀを削除
		sequenceStack_.pop();
	}

	return node;
}

bool BehaviorData::IsUsedNode(std::string nodeName)
{
	// 使用していなかったらfalse
	if (usedNodeMap_.count(nodeName) == 0)
	{
		return false;
	}
	// 使用していたらそのﾉｰﾄﾞを返す
	return usedNodeMap_[nodeName];
}

void BehaviorData::EntryUsedNode(std::string nodeName)
{
	// 使用しているというﾌﾗｸﾞを立てる
	usedNodeMap_[nodeName] = true;
}

int BehaviorData::GetSequenceStep(std::string nodeName)
{
	// 今現在の行動ｽﾃｯﾌﾟの取得
	if (runSequenceStepMap_.count(nodeName) == 0)
	{
		// ｽﾃｯﾌﾟがﾂﾘｰの始点の場合0にｾｯﾄする
		runSequenceStepMap_[nodeName] = 0;
	}
	return runSequenceStepMap_[nodeName];
}

void BehaviorData::SetSequenceStep(std::string nodeName,int step)
{
	// 思考ｽﾃｯﾌﾟのｾｯﾄ
	runSequenceStepMap_[nodeName] = step;
}

void BehaviorData::ResetNodeUsed(std::vector<ActionNode*>* resetHieralchy)
{
	// ﾉｰﾄﾞを使用しているﾌﾗｸﾞのﾘｾｯﾄ
	for (auto itr = resetHieralchy->begin(); itr != resetHieralchy->end(); itr++)
	{
		usedNodeMap_[(*itr)->GetNodeName()] = false;
	}
}
