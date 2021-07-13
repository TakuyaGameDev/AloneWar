#pragma once

struct BoxRect;

// “–‚½‚è”»’è—pŠÖ”µÌŞ¼Şª¸Ä
struct CollisionCheck
{
	bool operator()(const BoxRect& box1,const BoxRect& box2);
};

