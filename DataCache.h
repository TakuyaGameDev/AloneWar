#pragma once
#include <string>
#include <map>
#include <vector>
#include "Geometory.h"

struct AnimationData
{
	int frame_;
	float duration_;
	bool isLoop_;
};

// 矩形ﾃﾞｰﾀ
struct ColliderBoxRect
{
	char rectType_;
	Vector3I beginPos_;
	Vector3I endPos_;
	Vector3I size_;
};

// ｷｬﾗｸﾀｰの1ｱｸｼｮﾝの矩形ﾃﾞｰﾀ
// 1ﾌﾚｰﾑの中に矩形が何個入っているかによって個数が変わるので可変長になっている
struct ColliderBoxData
{
	std::vector<ColliderBoxRect> colRect_;
};

// ｷｬﾗｸﾀｰの1ｱｸｼｮﾝのﾃﾞｰﾀ
struct ActionData
{
	std::string actionName_;
	int frame_;
	std::vector<ColliderBoxData> colliderBox_;
	float duration_;
};

// ｷｬﾗｸﾀｰのｱﾄﾗｽ画像のﾃﾞｰﾀ
struct AtlusData
{
	std::string actorName_;
	Vector2I divSize_;
	Vector2I divCnt_;
	std::string name_;
	int actionNum_;
	std::vector<ActionData> actionSet_;
};

// ﾏｯﾌﾟの1ﾚｲﾔｰに存在するﾁｯﾌﾟﾃﾞｰﾀ
struct LayerData
{
	std::vector<int> tileSet_;
};

// TMXの中を見るためのﾃﾞｰﾀ(TSX)
struct TSX
{
	std::string sourceName_;
	int imageTileCount_;
	Vector2I imageSize_;
};

// ﾏｯﾌﾟのﾃﾞｰﾀ(TMX)
struct MapData
{
	std::map<std::string, LayerData> layerData_;
	int layerNum_;
	TSX tsx_;
	Vector2I layerSize_;
	Vector2I tileSize_;
};

#define ANIMATION std::map<std::string,AnimationData>

#define lpDataCache DataCache::getInstance()

using ColliderBox = std::map<std::string, std::vector<ColliderBoxData>>;


class DataCache
{
public:
	static DataCache& getInstance(void)
	{
		static DataCache sInstance_;
		return sInstance_;
	}

	// ﾏｯﾌﾟﾃﾞｰﾀのｾｯﾄ
	void SetMapData(std::string mapName, Vector2I layerSize, Vector2I tileSize,int layerNum);
	void SetTSX(std::string mapName,std::string sourceName,int tileCount,Vector2I imageSize);
	void AddTileSet(std::string mapName, std::string layerName,std::vector<int> tiles);

	void SetAtlusData(std::string fileName,std::string actorName);
	void SetAnimationData(std::string actorName, std::string animName,AnimationData animation);
	// ｱﾆﾒｰｼｮﾝﾃﾞｰﾀの取得
	const AnimationData& GetAnimationData(std::string actorName, std::string animName)
	{
		return animationData_[actorName][animName];
	}
	// ｱﾄﾗｽ画像のﾃﾞｰﾀの取得
	const AtlusData& GetAtlusData(std::string actorName)
	{
		return atlusData_[actorName];
	}

	// ﾏｯﾌﾟﾃﾞｰﾀの取得
	const MapData& GetMapData(std::string mapName)
	{
		return mapData_[mapName];
	}
	void SetColliderBoxData(std::string name);
	const ColliderBoxData& GetColliderData(std::string name,std::string animName,float frame)
	{
		return colliderBox_[name][animName][frame];
	}
private:
	DataCache() = default;
	~DataCache();

	void operator=(const DataCache&) = delete;

	std::map<std::string,MapData> mapData_;
	std::map<std::string, AtlusData> atlusData_;
	std::map<std::string, ANIMATION> animationData_;

	std::map<std::string, ColliderBox> colliderBox_;

};

