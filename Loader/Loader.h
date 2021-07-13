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
	// ����
	void CreateLoader(void);

	// ������
	bool Initialize(void);
	// �e��۰��
	bool LoadData(void);

private:
	Loader() = default;
	~Loader();
	void operator=(const Loader&) = delete;
	static Loader* sInstance_;
	// �؂藣�����߂̽گ��
	std::thread thisThread_;
	std::mutex loadMtx_;
};

