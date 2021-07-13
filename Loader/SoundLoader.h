#pragma once
#include <map>
#include <string>

#define lpSoundLoader SoundLoader::getInstance()

class SoundLoader
{
public:

	static SoundLoader& getInstance(void)
	{
		static SoundLoader sInstance_;
		return sInstance_;
	}
	// ���ް���۰��
	bool Load(std::string soundName,bool loop);
	// ���ް��̍Đ�
	void Play(std::string soundName);

private:
	SoundLoader() = default;
	~SoundLoader();

	void operator=(const SoundLoader&) = delete;

	// ٰ���׸ނ�����ْl�̊i�[
	std::map<std::string, std::pair<int,bool>> handles_;

};

