#pragma once
#include "VertexArrayObj.h"
#include <vector>

class Button;
class SpriteObj;
class TextObj;

class BattlePanel : public VertexArrayObj
{
protected:
	SpriteObj* paper;
	SpriteObj* titleBackground;
	SpriteObj* bottomGradiant;

	Button* summon;
	Button* begin;
	Button* expansion;
	vector<Button*> buttons;

	TextObj* titleText;
	TextObj* stageText;
	TextObj* titleNumberText;

	Vector2f paperLocalPos;
	Vector2f titlebgLocalPos;
	Vector2f summonLocalPos;
	Vector2f beginLocalPos;
	Vector2f expansionLocalPos;

	Vector2f titleTextLocalPos;
	Vector2f stageTextLocalPos;
	Vector2f dnmTitleTextLocalPos;
	Vector2f gradiantLocalPos;

public:
	BattlePanel();
	virtual ~BattlePanel();

	virtual void Draw(RenderWindow& window) override;
	virtual void SetPos(const Vector2f& pos) override;

	TextObj* GetTitleText() { return titleText; }
	TextObj* GetStageText() { return stageText; }
	TextObj* GetTitleNumberText() { return titleNumberText; }
	vector<Button*> GetButtons() { return buttons; }
};