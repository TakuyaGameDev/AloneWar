#pragma once
#include <vector>
#include <string>
#include <map>

#include "../Geometory.h"

using VectorInt = std::vector<int>;

// using ���d���Ǝv����define�Œ�`����
// ���ɏ��using�g���Ă���̂�
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
	// �P��۰��
	bool Loader(std::string imageName);
	// ����۰��
	void Loader(std::string imageName, Vector2I divSize, Vector2I divCnt);
	// ̧�ق���ǂݎ�����ް�����ɉ摜۰�ނ���֐�
	// param@ atlusData: ̧�ق��ǂݎ�����ް��������Ă���
	void Loader(const AtlusData& atlusData);
	// �摜����َ擾
	const VectorInt& GetHandles(std::string imageName)
	{
		return handles_[imageName];
	}
	// ��׸����p�摜����َ擾
	const VectorInt& GetActorHandles(std::string actorName, std::string animName)
	{
		return actorHandles_[actorName][animName];
	}

private:
	ImageLoader() = default;
	~ImageLoader();

	// �P�Ȃ�摜����ق̎擾
	std::map<std::string, VectorInt> handles_;
	// ��׸���ʐ�p����ق̎擾
	std::map<std::string, HandleMap> actorHandles_;
};

