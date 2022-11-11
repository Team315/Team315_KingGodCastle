#pragma once
#include "SpriteObj.h"

class Character : public SpriteObj
{
protected:
	Character* target;

public:
	Character();
	virtual ~Character();

	void SetTarget(Character* target);
};