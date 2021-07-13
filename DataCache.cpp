#include "DataCache.h"
#include "Loader/FileLoader.h"

void DataCache::SetMapData(std::string mapName,Vector2I layerSize, Vector2I tileSize,int layerNum)
{
	if (mapData_.count(mapName) <= 0)
	{
		mapData_[mapName].layerSize_ = layerSize;
		mapData_[mapName].tileSize_ = tileSize;
		mapData_[mapName].layerNum_ = layerNum;
	}
}

void DataCache::SetTSX(std::string mapName, std::string sourceName, int tileCount, Vector2I imageSize)
{
	mapData_[mapName].tsx_.sourceName_ = sourceName;
	mapData_[mapName].tsx_.imageTileCount_ = tileCount;
	mapData_[mapName].tsx_.imageSize_ = imageSize;
}
void DataCache::AddTileSet(std::string mapName, std::string layerName,std::vector<int> tiles)
{
	if (mapData_[mapName].layerData_.count(layerName) <= 0)
	{
		mapData_[mapName].layerData_[layerName].tileSet_ = tiles;
	}
}

void DataCache::SetAtlusData(std::string fileName,std::string actorName)
{
	lpFileLoader.CharacterFileLoader(fileName, atlusData_[actorName]);
}

void DataCache::SetAnimationData(std::string actorName, std::string animName,AnimationData animation)
{
	animationData_[actorName][animName] = animation;
}

void DataCache::SetColliderBoxData(std::string name)
{
	auto data = atlusData_[name].actionSet_;

	for (auto col : data)
	{
		colliderBox_[name][col.actionName_] = col.colliderBox_;
	}
}

DataCache::~DataCache()
{
}
