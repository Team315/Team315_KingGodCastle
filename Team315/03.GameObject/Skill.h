#pragma once
#include "GameObj.h"
#include "Include.h"
#include <vector>

class Character;

class Skill : public GameObj
{
protected:
	vector<float> baseDamage; // skill base damage
	vector<Vector2i> range;    // skill range

	float damage;
	Vector2i startPos;
	Vector2i destPos;
	int starNumber;

public:
	Skill();
	virtual ~Skill();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
	virtual void SetPos(const Vector2f& pos) override;
	virtual void SetRotation(Vector2f dir);

	virtual void SetState(AnimStates newState);
	AnimStates GetState() { return currState; }
	void CalculateDamage(Character* character);
};