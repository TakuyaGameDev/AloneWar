#include <DxLib.h>
#include "ImageLoader.h"
#include "../DataCache.h"

bool ImageLoader::Loader(std::string imageName)
{
    if (handles_.count(imageName) <= 0)
    {
        handles_[imageName].resize(1);
        handles_[imageName][0] = LoadGraph(imageName.c_str());
    }
    // ﾃﾞﾊﾞｯｸﾞ付き
    if (handles_[imageName][0] > -1)
    {
        return true;
    }
    return false;
}

void ImageLoader::Loader(std::string imageName, Vector2I divSize, Vector2I divCnt)
{
    if (handles_.count(imageName) <= 0)
    {
        handles_[imageName].resize(divCnt.x * divCnt.y);
        LoadDivGraph(imageName.c_str(),
            divCnt.x * divCnt.y,
            divCnt.x, divCnt.y,
            divSize.x, divSize.y,
            &handles_[imageName][0]);
    }
}

void ImageLoader::Loader(const AtlusData& atlusData)
{
	if (handles_.count(atlusData.actorName_) <= 0)
	{
		handles_[atlusData.actorName_].resize(1);
		// DerivationGraphの際に使用する画像をﾛｰﾄﾞする場所を決定するためのｶｰｿﾙ
		auto cursor = 0;
		// ｱﾄﾗｽ画像を1枚ﾛｰﾄﾞ
		handles_[atlusData.actorName_][0] = LoadGraph((atlusData.name_).c_str());
		// actionSetで回す
		for (auto data : atlusData.actionSet_)
		{
			// ｱｸｼｮﾝﾈｰﾑに対する画像ﾊﾝﾄﾞﾙがなければﾛｰﾄﾞする
			if (actorHandles_[atlusData.actorName_].count(data.actionName_) <= 0)
			{
				// まず、画像ﾊﾝﾄﾞﾙを格納する箱のresize
				actorHandles_[atlusData.actorName_][data.actionName_].resize(data.frame_);
				// DerivationGraph(): 一枚の大きい画像から
				// ﾛｰﾄﾞしたい画像を画像上の左上座標でﾛｰﾄﾞしていく画像を決定
				// ﾛｰﾄﾞする画像の左上座標を変えて行くためのfor文
				for (auto cur = cursor, i = 0; cur <= (cursor + (data.frame_ - 1)); cur++, i++)
				{
					// 1枚1枚ﾛｰﾄﾞして画像ﾊﾝﾄﾞﾙの中身に入れていく
					actorHandles_[atlusData.actorName_][data.actionName_][i] =
						DerivationGraph((cur % (atlusData.divCnt_.x)) * atlusData.divSize_.x,
							(cur / (atlusData.divCnt_.x)) * atlusData.divSize_.y, atlusData.divSize_.x, atlusData.divSize_.y, handles_[atlusData.actorName_][0]);
				}
			}
			// 画像上の初期ﾎﾟｼﾞｼｮﾝを変更
			cursor += data.frame_;
		}
	}
}

ImageLoader::~ImageLoader()
{
}
