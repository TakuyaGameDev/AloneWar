#pragma once

struct BoxRect;

// 当たり判定用関数ｵﾌﾞｼﾞｪｸﾄ
struct CollisionCheck
{
	bool operator()(const BoxRect& box1,const BoxRect& box2);
};

