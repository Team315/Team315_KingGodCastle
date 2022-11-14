#pragma once
#include "VertexArrayObj.h"
#include "SpriteButton.h"

class BattlePanel : public VertexArrayObj
{
protected:
	SpriteButton* summon;
	SpriteButton* begin;
	SpriteButton* expansion;

	Vector2f summonLocalPos;
	Vector2f beginLocalPos;
	Vector2f expansionLocalPos;

public:
	BattlePanel();
	virtual ~BattlePanel();

	virtual void Draw(RenderWindow& window) override;
	virtual void SetPos(const Vector2f& pos) override;
};