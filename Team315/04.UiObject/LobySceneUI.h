#pragma once
#include "UIMgr.h"
#include "SpriteButton.h"
#include "RectangleObj.h"
#include "Include.h"
#include <vector>

class LobySceneUI : public UIMgr
{
protected:
	// bottom tab
	enum class buttonModeEnum
	{
		none = -1,
		shop,
		barrack,
		gate,
		altar,
		mode,
		count,
	};
	int tabSize;
	float buttonSize;

	// top resources
	enum class gameResourceEnum
	{
		none = -1,
		level,
		gold,
		jewel,
		count,
	};
	struct GameResources
	{
		RectangleObj*	backSprite;
		SpriteObj*		resourceSprite;
		int				value;
		GameResources(RectangleObj* bs, SpriteObj* rs)
			: backSprite(bs), resourceSprite(rs), value(0)
		{}
		void SetPos(Vector2f pos)
		{
			backSprite->SetPos(pos);
			resourceSprite->SetPos(pos);
		}
		void SetValue(int v) { value = v; }
		int GetValue() { return value; }
	};
	vector<GameResources*> gameResources;
	int gameResourceCount;

public:
	LobySceneUI(Scene* scene);
	virtual ~LobySceneUI();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	int GetTabSize() { return tabSize; }
	vector<SpriteButton*> buttons;
};