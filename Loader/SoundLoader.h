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
	// ‰¹ÃŞ°À‚ÌÛ°ÄŞ
	bool Load(std::string soundName,bool loop);
	// ‰¹ÃŞ°À‚ÌÄ¶
	void Play(std::string soundName);

private:
	SoundLoader() = default;
	~SoundLoader();

	void operator=(const SoundLoader&) = delete;

	// Ù°ÌßÌ×¸Ş‚ÆÊİÄŞÙ’l‚ÌŠi”[
	std::map<std::string, std::pair<int,bool>> handles_;

};

