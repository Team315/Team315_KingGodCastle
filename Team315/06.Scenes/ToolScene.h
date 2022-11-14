#pragma once
#include "Scene.h"
#include "Include.h"

class TilePlay;
class SelectStar;
class SelectMonster;
class SelectObstacle;
class SelectTile;
class Theme;
class Number;
class UiName;
class TileSet;
class ToolScene : public Scene
{
protected:
	ClickMode m_clickMode;

	int m_nowChapter;
	int m_nowStage;
	int m_nowTheme;
	int m_nowTileSet;
	int m_nowObstacle;
	int m_nowStar;
	int m_monster;

	vector<vector<TilePlay*>> m_TilePlayList;
	TileSet* m_TileSet;
	list<UiName*> UiNameList;
	list<Number*> ChapterNumList;
	list<Number*> StageNumList;
	list<Theme*> ThemeList;
	list<SelectTile*> SelectTileList;
	list<SelectObstacle*> SelectObstacleList;
	list<SelectStar*> SelectStarList;
	list<SelectMonster*> SelectMonsterList;


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
	void CreateTilePlay(int cols, int rows, float quadWidth, float quadHeight);
	void CreateUiName();
	void CreateChapterNum(int count);
	void CreateStageNum(int count);
	void CreateTheme();
	void CreateSelectTile();
	void CreateSelectObstacle();
	void CreateSelectMonster();
	void CreateSelectStar();

	void SetClickMode(ClickMode clickMode);

};