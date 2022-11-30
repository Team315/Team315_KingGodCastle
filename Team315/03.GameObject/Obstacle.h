#pragma once
#include "GameObj.h"

class Obstacle : public GameObj
{
protected:

public:
	Obstacle(string path);
	virtual ~Obstacle();
};