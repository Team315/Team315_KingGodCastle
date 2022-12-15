#pragma once
#include "Character.h"

class Slime02 : public Character
{
protected:
public:
	Slime02(bool mode, bool useExtraUpgrade, int starGrade = 0);
	virtual ~Slime02();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
	virtual void SetPos(const Vector2f& pos) override;
};

