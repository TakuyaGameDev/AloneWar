#pragma once
#include <vector>
#include <string>
#include <map>

#include "../Geometory.h"

using VectorInt = std::vector<int>;

// using が重いと思ってdefineで定義した
// 既に上でusing使っているので
#define HandleMap std::map<std::string,VectorInt>

struct AtlusData;

#define lpImageLoader ImageLoader::getInstance()

class ImageLoader
{
public:
	static ImageLoader& getInstance(void)
	{
		static ImageLoader sInstance_;
		return sInstance_;
	}
	// 単発ﾛｰﾄﾞ
	bool Loader(std::string imageName);
	// 分割ﾛｰﾄﾞ
	void Loader(std::string imageName, Vector2I divSize, Vector2I divCnt);
	// ﾌｧｲﾙから読み取ったﾃﾞｰﾀを基に画像ﾛｰﾄﾞする関数
	// param@ atlusData: ﾌｧｲﾙより読み取ったﾃﾞｰﾀが入っている
	void Loader(const AtlusData& atlusData);
	// 画像ﾊﾝﾄﾞﾙ取得
	const VectorInt& GetHandles(std::string imageName)
	{
		return handles_[imageName];
	}
	// ｷｬﾗｸﾀｰ専用画像ﾊﾝﾄﾞﾙ取得
	const VectorInt& GetActorHandles(std::string actorName, std::string animName)
	{
		return actorHandles_[actorName][animName];
	}

private:
	ImageLoader() = default;
	~ImageLoader();

	// 単なる画像ﾊﾝﾄﾞﾙの取得
	std::map<std::string, VectorInt> handles_;
	// ｷｬﾗｸﾀｰ別専用ﾊﾝﾄﾞﾙの取得
	std::map<std::string, HandleMap> actorHandles_;
};

