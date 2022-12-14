#pragma once
#include "Character.h"

class Slime04 : public Character
{
protected:
public:
	Slime04(bool mode = false, bool useExtraUpgrade = false, int starGrade = 0);
	virtual ~Slime04();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
	virtual void SetPos(const Vector2f& pos) override;
};

