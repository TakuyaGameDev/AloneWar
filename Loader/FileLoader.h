#pragma once
#include <string>
#include <map>
#include <vector>

#define lpFileLoader FileLoader::getInstance()

struct AtlusData;

class FileLoader
{
public:
	static FileLoader& getInstance(void)
	{
		static FileLoader sInstance_;
		return sInstance_;
	}

	bool TMXLoader(std::string fileName,std::string mapName);
	bool TSXLoader(std::string fileName,std::string mapName);

	bool CharacterFileLoader(std::string fileName, AtlusData& atlusData);
private:
	FileLoader() = default;
	~FileLoader();

	void operator=(const FileLoader&) = delete;

};

