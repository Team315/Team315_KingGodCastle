#pragma once
#include "SpriteObj.h"
#include "ProgressBar.h"

class Character : public SpriteObj
{
protected:
	Character*		target;

	ProgressBar*	hpBar;
	Vector2f		hpBarLocalPos;
	Vector2f		destination;
	bool			move;

public:
	Character();
	virtual ~Character();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
	virtual void SetPos(const Vector2f& pos) override;

	void SetTarget(Character* target);
	void SetHpBarLocalPos(Vector2f pos);
	void SetMove(bool b) { move = b; }
	void SetDestination(Vector2f dest) { destination = dest; }
};