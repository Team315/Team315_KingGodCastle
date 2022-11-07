#pragma once
#include "TextObj.h"

class FloatingObj : public TextObj
{
protected:
	Vector2f dir;
	float speed;
	float range;
	float dist;

public:
	FloatingObj();
	FloatingObj(Font& font,
		string textString,
		float posX = 0, float posY = 0,
		Color textColor = Color::White,
		int textSize = 75);
	virtual ~FloatingObj() {}

	virtual void Release() override;
	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	void Fire(const Vector2f pos,
		const Vector2f dir = { 0, -1 },
		float speed = 50.f,
		float range = 50.f);
};