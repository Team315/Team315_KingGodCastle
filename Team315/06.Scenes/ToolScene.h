#pragma once
#include "Scene.h"

class TileSelect;
class Theme;
class Number;
class UiName;
class TileSet;
class ToolScene : public Scene
{
protected:

	TileSet* m_TileSet;
	list<UiName*> UiNameList;
	list<Number*> ChapterNumList;
	list<Number*> StageNumList;
	list<Theme*> ThemeList;
	list<TileSelect*> TileSelectList;


public:
	ToolScene();
	virtual ~ToolScene();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Enter() override;
	virtual void Exit() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	void CreateTileSet(int cols, int rows, float quadWidth, float quadHeight);
	void CreateUiName();
	void CreateChapterNum(int count);
	void CreateStageNum(int count);
	void CreateTheme();
	void CreateTileSelect();

};