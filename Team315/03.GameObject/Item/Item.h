#pragma once
#include "GameObj.h"

class Item : public GameObj
{
protected:
	int grade;
	ItemType type;

public:
	Item(int grade = 1, ItemType type = ItemType::None);
	virtual ~Item();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
	virtual void SetPos(const Vector2f& pos) override;

	string MakePath();
	int GetGrade() { return grade; }
};