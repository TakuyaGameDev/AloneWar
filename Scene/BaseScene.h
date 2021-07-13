#pragma once
#include <memory>

class BaseScene;
class Controller;

using ScenePtr = std::unique_ptr<BaseScene>;

class BaseScene
{
public:
	BaseScene();
	virtual ~BaseScene();
	// �X�V
	virtual ScenePtr Update(ScenePtr own,const std::shared_ptr<Controller>& controller) = 0;
	// �`��
	virtual void Draw(void) = 0;
	// ������
	virtual bool Init(void) = 0;

private:

protected:
};

