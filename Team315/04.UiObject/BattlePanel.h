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
	Vector2f coinLocalPos;

	Sprite coinSprite;
	BackrectText* coinState;
	
	Sprite characterCostSprite;
	BackrectText* characterCostText;
	Sprite expansionCostSprite;
	BackrectText* expansionCostText;

	Sprite expansionObjectSprite;
	BackrectText* expansionText;

public:
	BattlePanel();
	virtual ~BattlePanel();

	virtual void Draw(RenderWindow& window) override;
	virtual void SetPos(const Vector2f& pos) override;

	TextObj* GetTitleText() { return titleText; }
	TextObj* GetStageText() { return stageText; }
	TextObj* GetTitleNumberText() { return titleNumberText; }
	vector<Button*>& GetButtons() { return buttons; }

	void ChangeTitleTextString(int chapIdx);
	void SetStageNumber(int num);
	void SetCurrentCoin(int num);
	void SetSummonCostText();
	void SetExpansionCostText(int num);
	void SetExpansionStateText(int num, int limit);
};