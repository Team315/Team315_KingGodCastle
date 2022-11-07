#pragma once
#include "Object.h"

class SpriteObj : public Object
{
protected:
    Sprite sprite;

public:
    SpriteObj();
    virtual ~SpriteObj() override;

    virtual void Draw(RenderWindow& window) override;

    void SetTexture(Texture& tex);
    void SetOrigin(Origins origin);
	void SetScale(float x, float y);
	void SetColor(Color color);

	void SetTextureRect(const IntRect& rect);
	const IntRect& GetTextureRect() const;

	Vector2f GetSize()const;
	FloatRect GetGlobalBounds() const;

	void SetPos(const Vector2f& pos) override;
};