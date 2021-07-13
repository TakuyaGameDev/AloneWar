#include <sstream>
#include <fstream>
#include "FileLoader.h"
#include "../DataCache.h"

bool FileLoader::TMXLoader(std::string fileName,std::string mapName)
{
    std::ifstream file(fileName, std::ios::in | std::ios::binary);
    std::stringstream stringStream;
    std::string str1;
    std::string layerName = "";

    int layerNum = 0;
    int layerCount = -1;
    Vector2I layerSize = { 0,0 };
    Vector2I tileSize = { 0,0 };

    int index = 0;

    std::vector<std::vector<int>> tileSets;

    while(!file.eof()) {
        std::getline(file, str1);
        
        if (str1.find("layer id=") != -1)
        {
            layerCount++;
            std::string str3;
            stringStream.seekg(0, std::ios::beg);
            stringStream.str(str1);
            do {
                std::getline(stringStream, str3, '"');

                if (str3.find("name=") != -1)
                {
                    std::getline(stringStream, str3, '"');
                    layerName = str3;
                }
            } while (!stringStream.eof());
        }

        if (str1.find("map version") != -1)
        {
            std::string str2;
            stringStream.str(str1);
            do {
                std::getline(stringStream, str2, '"');
                if ((str2.find("width=") != -1) && (layerSize.x == 0))
                {
                    std::getline(stringStream, str2, '"');
                    layerSize.x = std::stoi(str2);
                }
                if ((str2.find("height=") != -1) && (layerSize.y == 0))
                {
                    std::getline(stringStream, str2, '"');
                    layerSize.y = std::stoi(str2);
                }
                if ((str2.find("tilewidth=") != -1) && (tileSize.x == 0))
                {
                    std::getline(stringStream, str2, '"');
                    tileSize.x = std::stoi(str2);
                }
                if ((str2.find("tileheight=") != -1) && (tileSize.y == 0))
                {
                    std::getline(stringStream, str2, '"');
                    tileSize.y = std::stoi(str2);
                }
                if (str2.find("nextlayerid=") != -1)
                {
                    std::getline(stringStream, str2, '"');
                    layerNum = std::stoi(str2) - 1;
                    tileSets.resize(layerNum);
                    for (auto num = 0; num < layerNum; num++)
                    {
                        tileSets[num].resize(layerSize.x * layerSize.y);
                    }
                    lpDataCache.SetMapData(mapName, layerSize, tileSize, layerNum);
                }
            } while (!stringStream.eof());
        }

        if (str1.find("tileset") != -1)
        {
            std::string str4;
            stringStream.seekg(0, std::ios::beg);
            stringStream.str(str1);
            do {
                std::getline(stringStream, str4, '"');
                if (str4.find("source=") != -1)
                {
                    std::getline(stringStream, str4, '"');
                    TSXLoader("DataFile/" + str4,mapName);

                }

            } while (!stringStream.eof());
        }

        // csvデータになったら1行毎に読む
        if (str1.find_first_of("data encoding") == std::string::npos)
        {
            
            stringStream.str(str1);
            stringStream.seekg(0, std::ios::beg);

            do
            {
                std::string numStr = "";
                std::getline(stringStream, numStr, ',');
                // 数字データのstringをintにする
                if (numStr == "\r")
                {
                    continue;
                }
                if (numStr.size())
                {
                    tileSets[layerCount][index] = std::atoi(numStr.c_str());
                    index++;
                    if (index >= (layerSize.x * layerSize.y))
                    {
                        lpDataCache.AddTileSet(mapName, layerName, tileSets[layerCount]);
                        index = 0;
                    }
                }
            } while (!stringStream.eof());
        }
    };

    return true;
}

bool FileLoader::TSXLoader(std::string fileName, std::string mapName)
{
    std::ifstream file(fileName, std::ios::in | std::ios::binary);
    std::stringstream strStream;
    std::string str1 = "";

    std::string sourceName = "";
    int tileCnt = 0;
    Vector2I imageSize = { 0,0 };

    while (!file.eof()) {
        std::getline(file, str1);
        strStream.str(str1);
        if (str1.find("tileset") != -1)
        {
            strStream.str(str1);
            std::getline(strStream, str1, '"');
            do {
                std::getline(strStream, str1, '"');

                if (str1.find("tilecount=") != -1)
                {
                    std::getline(strStream, str1, '"');
                    tileCnt = std::atoi(str1.c_str());
                }
                if (str1.find("columns=") != -1)
                {
                    std::getline(strStream, str1, '"');
                    imageSize = Vector2I(std::atoi(str1.c_str()), tileCnt / std::atoi(str1.c_str()));
                }
            } while (!strStream.eof());
        }
        if (str1.find("image source=") != -1)
        {
            strStream.seekg(0, std::ios::beg);
            strStream.str(str1);
            std::getline(strStream, str1, '"');
            do {
                std::getline(strStream, str1, '"');
                if (!sourceName.size())
                {
                    sourceName = str1;
                }
                break;
            } while (!strStream.eof());
        }
    };
    lpDataCache.SetTSX(mapName, sourceName, tileCnt, imageSize);
    return true;
}

bool FileLoader::CharacterFileLoader(std::string fileName, AtlusData& atlusData)
{
    std::ifstream file(fileName, std::ios::in | std::ios::binary);
    std::stringstream strStream;
    std::string str = "";

    bool isFirstRead = false;
    int rectNum = 0;
    int frame = 0;
    int index = -1;
    AnimationData animData;
    ActionData actionData;
    ColliderBoxRect rectInfo;

    do
    {
        std::getline(file, str);
        if (str.find("<actorname") != -1)
        {
            strStream.str(str);
            std::getline(strStream, str, '$');
            std::getline(strStream, str, '$');
            atlusData.actorName_ = str;
            do {
                std::getline(strStream, str, '$');
                if (str.find("atlusfilename=") != -1)
                {
                    std::getline(strStream, str, '$');
                    atlusData.name_ = str;
                }
                if (str.find("imageDivSize=") != -1)
                {
                    std::getline(strStream, str, ',');
                    atlusData.divSize_.x = std::atoi(str.c_str());
                    std::getline(strStream, str, '$');
                    atlusData.divSize_.y = std::atoi(str.c_str());
                }
                if (str.find("imageDivCount=") != -1)
                {
                    std::getline(strStream, str, ',');
                    atlusData.divCnt_.x = std::atoi(str.c_str());
                    std::getline(strStream, str, '$');
                    atlusData.divCnt_.y = std::atoi(str.c_str());
                }
                if (str.find("actionTotalNum=") != -1)
                {
                    std::getline(strStream, str, '$');
                    atlusData.actionNum_ = std::atoi(str.c_str());
                    atlusData.actionSet_.resize(atlusData.actionNum_);
                }
            } while (!strStream.eof());
        }
        if (str.find("<actionname=") != -1)
        {
            if (isFirstRead)
            {
                lpDataCache.SetAnimationData(atlusData.actorName_, actionData.actionName_, animData);
            }
            actionData.actionName_.clear();
            index++;
            strStream.seekg(0, std::ios::beg);
            strStream.str(str);
            do {
                std::getline(strStream, str, '$');

                if (actionData.actionName_.size() <= 0)
                {
                    std::getline(strStream, str, '$');
                    actionData.actionName_ = str;
                }
                if (str.find("maxframe=") != -1)
                {
                    std::getline(strStream, str, '$');
                    actionData.frame_ = std::atoi(str.c_str());
                    animData.frame_ = std::atoi(str.c_str());
                }
                if (str.find("duration=") != -1)
                {
                    std::getline(strStream, str, '$');
                    actionData.duration_ = std::stof(str);
                    animData.duration_ = std::stof(str);
                    atlusData.actionSet_[index] = actionData;
                    atlusData.actionSet_[index].colliderBox_.resize(atlusData.actionSet_[index].frame_);
                }
                if (str.find("loop=") != -1)
                {
                    std::getline(strStream, str, '$');
                    if (str == "TRUE")
                    {
                        animData.isLoop_ = true;
                    }
                    if (str == "FALSE")
                    {
                        animData.isLoop_ = false;
                    }
                }
            } while (!strStream.eof());
        }
        if (str.find("<rectnum=") != -1)
        {
            strStream.seekg(0, std::ios::beg);
            strStream.str(str);

            std::getline(strStream, str, '$');
            std::getline(strStream, str, '$');
            rectNum = std::atoi(str.c_str());
        }
        if (str.find("<animationframe=") != -1)
        {
            strStream.seekg(0, std::ios::beg);
            strStream.str(str);
            std::getline(strStream, str, '$');
            std::getline(strStream, str, '$');
            frame = std::atoi(str.c_str());
            do {
                std::getline(strStream, str, '$');
                if (str.find("recttype=") != -1)
                {
                    std::getline(strStream, str, '$');
                    if (str == "ATTACK")
                    {
                        rectInfo.rectType_ = 0;
                    }
                    else if (str == "DAMAGE")
                    {
                        rectInfo.rectType_ = 1;
                    }
                }
                if (str.find("begin=") != -1)
                {
                    std::getline(strStream, str, ',');
                    rectInfo.beginPos_.x = std::atoi(str.c_str());
                    std::getline(strStream, str, '$');
                    rectInfo.beginPos_.y = std::atoi(str.c_str());
                    rectInfo.beginPos_.z = 0;
                }
                if (str.find("end=") != -1)
                {
                    std::getline(strStream, str, ',');
                    rectInfo.endPos_.x = std::atoi(str.c_str());
                    std::getline(strStream, str, '$');
                    rectInfo.endPos_.y = std::atoi(str.c_str());
                    rectInfo.endPos_.z = 0;
                }
                if (str.find("size=") != -1)
                {
                    std::getline(strStream, str, ',');
                    rectInfo.size_.x = std::atoi(str.c_str());
                    std::getline(strStream, str, '$');
                    rectInfo.size_.y = std::atoi(str.c_str());
                    atlusData.actionSet_[index].colliderBox_[frame].colRect_.push_back(rectInfo);
                    isFirstRead = true;
                }
            } while (!strStream.eof());
        }
    }while (!file.eof());

    return false;
}

FileLoader::~FileLoader()
{
}
