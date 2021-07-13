#pragma once
#include <memory>
#include <vector>

// ﾊﾞｯﾌｧ親ｸﾗｽ
class ObjectPool
{
public:
	ObjectPool() {};
	virtual ~ObjectPool() {};
	// poolの破棄
	virtual void Destroy(void) = 0;
	// poolの更新
	virtual void Update(void) = 0;
	// poolの中身の人たちの描画
	virtual void Draw(void) = 0;
private:

protected:
	// poolのｻｲｽﾞ
	int poolSize_;
};