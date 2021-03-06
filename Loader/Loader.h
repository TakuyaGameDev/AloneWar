#pragma once
#include <thread>
#include <mutex>

#define lpLoader Loader::getInstance()

class Loader
{
public:
	static Loader& getInstance(void)
	{
		return *sInstance_;
	}
	// 生成
	void CreateLoader(void);

	// 初期化
	bool Initialize(void);
	// 各種ﾛｰﾄﾞ
	bool LoadData(void);

private:
	Loader() = default;
	~Loader();
	void operator=(const Loader&) = delete;
	static Loader* sInstance_;
	// 切り離すためのｽﾚｯﾄﾞ
	std::thread thisThread_;
	std::mutex loadMtx_;
};

