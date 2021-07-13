#include "BehaviorTree.h"
#include "BehaviorData.h"
#include "ActionNode.h"
#include "Judgement/JudgementBase.h"
#include "Action/ActionBase.h"

BehaviorTree::BehaviorTree()
{
}

BehaviorTree::~BehaviorTree()
{
}

void BehaviorTree::AddNode(std::string searchName, std::string entryName,int priority, SelectRule selectRule, JudgementBase* judgement, ActionBase* action)
{
	// searchNameの文字列が空だと
	if (searchName.size() != 0)
	{
		// まず親ﾉｰﾄﾞを探す
		ActionNode* searchNode = root_->SearchActionNode(searchName);
		// 親がいれば
		if (searchNode != nullptr)
		{
			// 末尾の子供を探す
			ActionNode* sibling = searchNode->GetLastChild();
			// 追加するﾉｰﾄﾞの作成
			ActionNode* addNode = new ActionNode(entryName, searchNode, sibling,priority,selectRule, judgement, action);
			// ﾉｰﾄﾞの追加
			searchNode->AddChild(addNode);
		}
	}
	else
	{
		// そもそもﾙｰﾄがなければ
		if (root_ == nullptr)
		{
			// ﾙｰﾄの作成
			// childとsiblingは共にnullptr(自信が親なので)
			root_ = new ActionNode(entryName, nullptr, nullptr,priority,selectRule, judgement, action);
		}
		else
		{
			// ｱｻｰﾄをかける
			_ASSERT("root is already registered!!");
		}
	}
}

ActionNode* BehaviorTree::Inference(Enemy* enemy,BehaviorData* data)
{
	// ﾉｰﾄﾞ推論
	return root_->Inference(enemy,data);
}

ActionNode* BehaviorTree::SequenceInference(ActionNode* sequenceNode, Enemy* enemy, BehaviorData* data)
{
	// ﾉｰﾄﾞ推論をして推論した結果、行動可能なﾉｰﾄﾞを返す
	return sequenceNode->Inference(enemy,data);
}

void BehaviorTree::Run(Enemy* enemy, ActionNode* actionNode,BehaviorData* data)
{
	// ﾉｰﾄﾞの実行
	actionNode->Run(enemy);
}
