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
	// ¶¬
	void CreateLoader(void);

	// ‰Šú‰»
	bool Initialize(void);
	// ŠeíÛ°ÄŞ
	bool LoadData(void);

private:
	Loader() = default;
	~Loader();
	void operator=(const Loader&) = delete;
	static Loader* sInstance_;
	// Ø‚è—£‚·‚½‚ß‚Ì½Ú¯ÄŞ
	std::thread thisThread_;
	std::mutex loadMtx_;
};

