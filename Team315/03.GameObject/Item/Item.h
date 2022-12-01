#pragma once
#include "GameObj.h"

class Item : public GameObj
{
protected:
	int grade;
	ItemType type;
	float potential;
	StatType statType;

public:
	Item(int grade = 0, ItemType type = ItemType::None);
	virtual ~Item();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
	virtual void SetPos(const Vector2f& pos) override;

	virtual void ApplyToCharacter(Character* character);

	string MakePath();
	int GetGrade() { return grade; }
	float GetPotential() { return potential; }
	StatType GetStatType() { return statType; }
	bool Upgrade();
};