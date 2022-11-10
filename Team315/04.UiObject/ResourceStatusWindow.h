#pragma once
#include "Object.h"

class ResourceStatusWindow : public Object
{
protected:
	Sprite			sprite;
	RectangleShape	shape;

	Vector2f		spriteLocalPos;
	Vector2f		shapeLocalPos;

public:
	ResourceStatusWindow();
	virtual	~ResourceStatusWindow();

	virtual void Draw(RenderWindow& window) override;
	virtual void SetPos(const Vector2f& pos) override;

	void SetSpriteLocalPos(Vector2f sprPos);
	void SetShapeLocalPos(Vector2f shapePos);
	void SetTexture(Texture& tex);
	void SetShapeColor(Color color);
};