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

// ‹éŒ`ÃŞ°À
struct ColliderBoxRect
{
	char rectType_;
	Vector3I beginPos_;
	Vector3I endPos_;
	Vector3I size_;
};

// ·¬×¸À°‚Ì1±¸¼®İ‚Ì‹éŒ`ÃŞ°À
// 1ÌÚ°Ñ‚Ì’†‚É‹éŒ`‚ª‰½ŒÂ“ü‚Á‚Ä‚¢‚é‚©‚É‚æ‚Á‚ÄŒÂ”‚ª•Ï‚í‚é‚Ì‚Å‰Â•Ï’·‚É‚È‚Á‚Ä‚¢‚é
struct ColliderBoxData
{
	std::vector<ColliderBoxRect> colRect_;
};

// ·¬×¸À°‚Ì1±¸¼®İ‚ÌÃŞ°À
struct ActionData
{
	std::string actionName_;
	int frame_;
	std::vector<ColliderBoxData> colliderBox_;
	float duration_;
};

// ·¬×¸À°‚Ì±Ä×½‰æ‘œ‚ÌÃŞ°À
struct AtlusData
{
	std::string actorName_;
	Vector2I divSize_;
	Vector2I divCnt_;
	std::string name_;
	int actionNum_;
	std::vector<ActionData> actionSet_;
};

// Ï¯Ìß‚Ì1Ú²Ô°‚É‘¶İ‚·‚éÁ¯ÌßÃŞ°À
struct LayerData
{
	std::vector<int> tileSet_;
};

// TMX‚Ì’†‚ğŒ©‚é‚½‚ß‚ÌÃŞ°À(TSX)
struct TSX
{
	std::string sourceName_;
	int imageTileCount_;
	Vector2I imageSize_;
};

// Ï¯Ìß‚ÌÃŞ°À(TMX)
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

	// Ï¯ÌßÃŞ°À‚Ì¾¯Ä
	void SetMapData(std::string mapName, Vector2I layerSize, Vector2I tileSize,int layerNum);
	void SetTSX(std::string mapName,std::string sourceName,int tileCount,Vector2I imageSize);
	void AddTileSet(std::string mapName, std::string layerName,std::vector<int> tiles);

	void SetAtlusData(std::string fileName,std::string actorName);
	void SetAnimationData(std::string actorName, std::string animName,AnimationData animation);
	// ±ÆÒ°¼®İÃŞ°À‚Ìæ“¾
	const AnimationData& GetAnimationData(std::string actorName, std::string animName)
	{
		return animationData_[actorName][animName];
	}
	// ±Ä×½‰æ‘œ‚ÌÃŞ°À‚Ìæ“¾
	const AtlusData& GetAtlusData(std::string actorName)
	{
		return atlusData_[actorName];
	}

	// Ï¯ÌßÃŞ°À‚Ìæ“¾
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

