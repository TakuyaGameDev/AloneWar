#pragma once

struct BoxRect;

// �����蔻��p�֐���޼ު��
struct CollisionCheck
{
	bool operator()(const BoxRect& box1,const BoxRect& box2);
};

