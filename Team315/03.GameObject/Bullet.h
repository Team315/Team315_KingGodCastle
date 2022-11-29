#pragma once
#include "SpriteObj.h"
#include "Include.h"

class Bullet : public SpriteObj
{
protected:
	Vector2f dir;
	float speed;
	float range;
public:
	Bullet();
	~Bullet();

	void Fire(const Vector2f& pos, const Vector2f& dir, float speed, float range = 0.f);

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
};

