#include "ActionNode.h"
#include "Judgement/JudgementBase.h"
#include "Action/ActionBase.h"
#include "BehaviorData.h"

ActionNode::ActionNode(std::string nodeName, ActionNode* parent, 
	ActionNode* sibling,int priority, BehaviorTree::SelectRule rule,
	JudgementBase* judgement, ActionBase* action):
	nodeName_(nodeName),parent_(parent),
	sibling_(sibling),priority_(priority),
	selectRule_(rule),judgement_(judgement),
	action_(action),child_(NULL)
{
}

ActionNode* ActionNode::Inference(Enemy* enemy,BehaviorData* data)
{
	// 実行ﾉｰﾄﾞ格納用
	ActionNode* result = nullptr;

	for (int i = 0; i < child_.size(); i++)
	{
		if (child_[i]->judgement_ != nullptr)
		{
			// 判定がtrueになったら実行ﾉｰﾄﾞ格納用変数に格納
			if (child_[i]->Judgement(enemy))
			{
				result = child_[i];
			}
		}
	}

	if (result != nullptr)
	{
		// 実行ﾃﾞｰﾀをもっていれば終了
		if (result->HasAction())
		{
			return result;
		}
		else
		{
			// もっていなければ推論続行
			result = result->Inference(enemy,data);
		}
	}

	return result;
}

ActionNode* ActionNode::SearchActionNode(std::string nodeName)
{
	if (nodeName_ == nodeName)
	{
		return this;
	}
	else
	{
		// 子ﾉｰﾄﾞで検索
		for (auto itr = child_.begin(); itr != child_.end(); itr++)
		{
			ActionNode* node = (*itr)->SearchActionNode(nodeName);
			if (node != nullptr)
			{
				return node;
			}
		}
	}
	return nullptr;
}

void ActionNode::AddChild(ActionNode* childNode)
{
	child_.push_back(childNode);
}

ActionNode* ActionNode::GetLastChild(void)
{
	if (child_.size() == 0)
	{
		return nullptr;
	}

	return child_[child_.size() - 1];
}

bool ActionNode::Judgement(Enemy* enemy)
{
	// 行動の判定
	if (judgement_ != nullptr)
	{
		return judgement_->operator()(enemy);
	}
	return true;
}

bool ActionNode::HasAction(void)
{
	// 実行ﾉｰﾄﾞをもっていればtrue
	return action_ != nullptr?true:false;
}

void ActionNode::Run(Enemy* enemy)
{
	// 行動の実行
	if (action_ != nullptr)
	{
		action_->operator()(enemy);
	}
}
