#pragma once
#include "../Geometory.h"

class Obj
{
public:
	Obj();
	virtual ~Obj();

	virtual void Draw(void) = 0;
	virtual void SetVertex(void) = 0;
private:

protected:
	Vector3F pos_;
	Vector3F size_;
};

