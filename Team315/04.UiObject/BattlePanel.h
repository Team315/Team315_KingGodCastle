#pragma once
#include "VertexArrayObj.h"
#include <vector>

class Button;
class SpriteObj;
class TextObj;
class BackrectText;

class BattlePanel : public VertexArrayObj
{
protected:
	SpriteObj* paper;
	Sprite titleBackground;
	Sprite bottomGradiant;

	Button* summon;
	Button* begin;
	Button* equipment;
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
	Vector2f coinLocalPos;

	Sprite coinSprite;
	BackrectText* coinState;

public:
	BattlePanel();
	virtual ~BattlePanel();

	virtual void Draw(RenderWindow& window) override;
	virtual void SetPos(const Vector2f& pos) override;

	TextObj* GetTitleText() { return titleText; }
	TextObj* GetStageText() { return stageText; }
	TextObj* GetTitleNumberText() { return titleNumberText; }
	vector<Button*>& GetButtons() { return buttons; }

	void SetStageNumber(int num);
	void SetCurrentCoin(int num);
};