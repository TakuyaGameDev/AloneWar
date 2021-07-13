#include <math.h>
#include "Geometory.h"
#include "CollisionCheck.h"

bool CollisionCheck::operator()(const BoxRect& box1,const BoxRect& box2)
{
    // ﾎﾞｯｸｽの2点間の距離
    auto distance = box2.pos_ - box1.pos_;
    // 2つのﾎﾞｯｸｽのｻｲｽﾞの半分の合計
    // distanceがこれより小さければ当たっているという判定になる
    auto sizediff = Vector3I((box1.size_.x / 2) + (box2.size_.x / 2),
                             (box1.size_.y / 2) + (box2.size_.y / 2),
                             (box1.size_.z / 2) + (box2.size_.z / 2));
    // 当たり判定開始
    if ((abs((int)distance.x) <= sizediff.x) &&
        (abs((int)distance.y) <= sizediff.y) &&
        (abs((int)distance.z) <= sizediff.z))
    {
        // 当たっている
        return true;
    }
    // 当たっていない
    return false;
}
