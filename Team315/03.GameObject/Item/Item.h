#pragma once
#include "GameObj.h"

class Item : public GameObj
{
protected:
	int grade;
	ItemType itemType;
	float potential;
	StatType statType;
	Sprite shadow;
	Vector2f spriteLocalPos;
	float delta;

public:
	Item(int grade = 0, bool useExtraChance = false, ItemType iType = ItemType::None);
	virtual ~Item();

	virtual void Update(float dt);
	virtual void Draw(RenderWindow& window) override;
	virtual void SetPos(const Vector2f& pos) override;

	string MakePath();
	ItemType GetItemType() { return itemType; }
	int GetGrade() { return grade; }
	float GetPotential() { return potential; }
	StatType GetStatType() { return statType; }
	string GetStatTypeString();
	bool Upgrade();
};