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
	// 音ﾃﾞｰﾀのﾛｰﾄﾞ
	bool Load(std::string soundName,bool loop);
	// 音ﾃﾞｰﾀの再生
	void Play(std::string soundName);

private:
	SoundLoader() = default;
	~SoundLoader();

	void operator=(const SoundLoader&) = delete;

	// ﾙｰﾌﾟﾌﾗｸﾞとﾊﾝﾄﾞﾙ値の格納
	std::map<std::string, std::pair<int,bool>> handles_;

};

