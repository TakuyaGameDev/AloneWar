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
    // ���ޯ�ޕt��
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
		// DerivationGraph�̍ۂɎg�p����摜��۰�ނ���ꏊ�����肷�邽�߂̶���
		auto cursor = 0;
		// ��׽�摜��1��۰��
		handles_[atlusData.actorName_][0] = LoadGraph((atlusData.name_).c_str());
		// actionSet�ŉ�
		for (auto data : atlusData.actionSet_)
		{
			// �����Ȱтɑ΂���摜����ق��Ȃ����۰�ނ���
			if (actorHandles_[atlusData.actorName_].count(data.actionName_) <= 0)
			{
				// �܂��A�摜����ق��i�[���锠��resize
				actorHandles_[atlusData.actorName_][data.actionName_].resize(data.frame_);
				// DerivationGraph(): �ꖇ�̑傫���摜����
				// ۰�ނ������摜���摜��̍�����W��۰�ނ��Ă����摜������
				// ۰�ނ���摜�̍�����W��ς��čs�����߂�for��
				for (auto cur = cursor, i = 0; cur <= (cursor + (data.frame_ - 1)); cur++, i++)
				{
					// 1��1��۰�ނ��ĉ摜����ق̒��g�ɓ���Ă���
					actorHandles_[atlusData.actorName_][data.actionName_][i] =
						DerivationGraph((cur % (atlusData.divCnt_.x)) * atlusData.divSize_.x,
							(cur / (atlusData.divCnt_.x)) * atlusData.divSize_.y, atlusData.divSize_.x, atlusData.divSize_.y, handles_[atlusData.actorName_][0]);
				}
			}
			// �摜��̏����߼޼�݂�ύX
			cursor += data.frame_;
		}
	}
}

ImageLoader::~ImageLoader()
{
}
