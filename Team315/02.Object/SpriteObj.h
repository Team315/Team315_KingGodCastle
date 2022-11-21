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
    virtual void SetOrigin(Origins origin) override;

    void SetTexture(Texture& tex);
	void SetScale(float x, float y);
	void SetColor(Color color);

	void SetTextureRect(const IntRect& rect);
	const IntRect& GetTextureRect() const;

	Vector2f GetSize()const;
	FloatRect GetGlobalBounds() const;

	virtual void SetPos(const Vector2f& pos) override;
};