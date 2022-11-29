#pragma once
#include "Object.h"

class RectangleObj : public Object
{
protected:
	RectangleShape shape;

public:
    RectangleObj(float x = 0, float y = 0);
    virtual ~RectangleObj() override;

	virtual void Draw(RenderWindow& window) override;
	virtual void SetOrigin(Origins origin) override;
	virtual void SetPos(const Vector2f& pos) override;

	void SetTexture(Texture* tex);
	void SetScale(float x, float y);
	void SetFillColor(Color color);
	void SetOutline(Color outlColor, float outlThickness);
	void SetSize(float x, float y);
	void SetRotate(float rotate);

	void SetTextureRect(const IntRect& rect);
	const IntRect& GetTextureRect() const;

	Vector2f GetSize()const;
	FloatRect GetGlobalBounds() const;

	RectangleShape& GetShape();
};