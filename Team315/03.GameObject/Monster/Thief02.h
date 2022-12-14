#pragma once
#include "Character.h"

class Thief02 : public Character
{
protected:
public:
	Thief02(bool mode = false, bool useExtraUpgrade = false, int starGrade = 0);
	virtual ~Thief02();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
	virtual void SetPos(const Vector2f& pos) override;
};

