#pragma once
#include "RectangleObj.h"

class DamageData;
class TwoFactorProgress;

class TrackerProfile : public RectangleObj
{
protected:
	DamageData* data;
	Sprite portrait;
	Sprite star;
	Text characterName;
	Text quantity;
	TwoFactorProgress* bar;
	bool givenOrTaken;
	float maxTotal;

public:
	TrackerProfile(float x = 140.f, float y = 50.f);
	virtual ~TrackerProfile();

	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
	virtual void SetPos(const Vector2f& pos) override;

	void SetSource(DamageData* data);
	void SetMode(bool mode) { givenOrTaken = mode; }
	void Parse();
	void SetMaxTotal(float value) { maxTotal = value; }

	DamageData* GetData();
};