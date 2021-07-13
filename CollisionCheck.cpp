#include <math.h>
#include "Geometory.h"
#include "CollisionCheck.h"

bool CollisionCheck::operator()(const BoxRect& box1,const BoxRect& box2)
{
    // �ޯ����2�_�Ԃ̋���
    auto distance = box2.pos_ - box1.pos_;
    // 2���ޯ���̻��ނ̔����̍��v
    // distance�������菬������Γ������Ă���Ƃ�������ɂȂ�
    auto sizediff = Vector3I((box1.size_.x / 2) + (box2.size_.x / 2),
                             (box1.size_.y / 2) + (box2.size_.y / 2),
                             (box1.size_.z / 2) + (box2.size_.z / 2));
    // �����蔻��J�n
    if ((abs((int)distance.x) <= sizediff.x) &&
        (abs((int)distance.y) <= sizediff.y) &&
        (abs((int)distance.z) <= sizediff.z))
    {
        // �������Ă���
        return true;
    }
    // �������Ă��Ȃ�
    return false;
}
