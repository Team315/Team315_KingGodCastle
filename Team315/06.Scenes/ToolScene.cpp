#include "ToolScene.h"

#include "TileSet.h"
#include "UiName.h"
#include "Number.h"
#include "TextObj.h"
#include "Theme.h"
#include "SelectTile.h"
#include "SelectObstacle.h"
#include "SelectMonster.h"
#include "SelectStar.h"
#include "TilePlay.h"
#include "ToolChapter.h"
#include "ToolStage.h"
#include "FileManager.h"


ToolScene::ToolScene()
	: Scene(Scenes::Tool), m_clickMode(ClickMode::None), m_nowChapter(1), m_nowStage(1), m_nowTileSet(-1), m_nowObstacle(-1), m_nowTheme(1), m_nowStar(0), m_monster(-1)
{
	SetClickMode(m_clickMode);
	CLOG::Print3String("tool create");
}

ToolScene::~ToolScene()
{
	Release();
}

void ToolScene::Init()
{
	CLOG::Print3String("tool Init");

	//CreateChapterNum(ChapterMaxCount);
	//CreateStageNum(StageMaxCount);
	CreateChapterNum(CHAPTER_MAX_COUNT);
	CreateStageNum(STAGE_MAX_COUNT);
	CreateTheme();
	CreateSelectTile();
	CreateSelectObstacle();
	CreateSelectMonster();
	CreateSelectStar();
	CreateUiName();

	for (int i = 0; i < CHAPTER_MAX_COUNT; i++)
	{
		ToolChapter* toolChapter = new ToolChapter();
		toolChapter->CreateToolStage(STAGE_MAX_COUNT, GAME_TILE_HEIGHT, GAME_TILE_WIDTH, TILE_SIZE, TILE_SIZE);
		ToolChapterLIst.push_back(toolChapter);
	}

	Scene::Init();
}

void ToolScene::Release()
{
	CLOG::Print3String("tool Release");

	for (const auto& UiName : UiNameList)
	{
		UiName->Release();
		delete UiName;
	}
	UiNameList.clear();
}

void ToolScene::Enter()
{
	CLOG::Print3String("tool enter");

	FRAMEWORK->SetWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	currentView = toolView;
}

void ToolScene::Exit()
{
	CLOG::Print3String("tool exit");
}

void ToolScene::Update(float dt)
{
	// Dev key
	if (InputMgr::GetKeyDown(Keyboard::Key::F7))
	{
		CLOG::Print3String("tool devmode on");
		FRAMEWORK->devMode = true;
	}
	if (InputMgr::GetKeyDown(Keyboard::Key::F8))
	{
		CLOG::Print3String("tool devmode off");
		FRAMEWORK->devMode = false;
	}
	// Dev key end

	if (InputMgr::GetKeyDown(Keyboard::Key::Escape))
	{
		SCENE_MGR->ChangeScene(Scenes::Loby);
		return;
	}

	for (auto chapterNum : ChapterNumList)
	{
		chapterNum->OnEdge(m_nowChapter);
		if (chapterNum->CollisionCheck(ScreenToToolPos(InputMgr::GetMousePosI()), m_nowChapter))
		{
			if (InputMgr::GetMouseUp(Mouse::Left))
			{
				m_nowChapter = chapterNum->GetIndex();
			}
		}
	}

	for (auto stageNum : StageNumList)
	{
		stageNum->OnEdge(m_nowStage);
		if (stageNum->CollisionCheck(ScreenToToolPos(InputMgr::GetMousePosI()), m_nowStage))
		{
			if (InputMgr::GetMouseUp(Mouse::Left))
			{
				m_nowStage = stageNum->GetIndex();
			}
		}
	}

	for (auto Theme : ThemeList)
	{
		Theme->OnEdge(m_nowTheme);
		if (Theme->CollisionCheck(ScreenToToolPos(InputMgr::GetMousePosI()), m_nowTheme))
		{
			if (InputMgr::GetMouseUp(Mouse::Left))
			{
				SetClickMode(ClickMode::Theme);
				m_nowTheme = Theme->GetIndex();
			}
		}
	}

	for (auto SelectTile : SelectTileList)
	{

		SelectTile->OnEdge(m_nowTileSet);
		if (SelectTile->CollisionCheck(ScreenToToolPos(InputMgr::GetMousePosI()), m_nowTileSet))
		{
			if (InputMgr::GetMouseUp(Mouse::Left))
			{
				SetClickMode(ClickMode::Tile);
				m_nowTileSet = SelectTile->GetIndex();
			}
		}
	}

	for (auto SelectObstacle : SelectObstacleList)
	{
		if(SelectObstacle->GetThemeTypes() == (ThemeTypes)m_nowTheme)
		{ 
			SelectObstacle->SetActive(true);
		}
		else
		{
			SelectObstacle->SetActive(false);
		}
		SelectObstacle->OnEdge(m_nowObstacle);
		if (SelectObstacle->CollisionCheck(ScreenToToolPos(InputMgr::GetMousePosI()), m_nowObstacle))
		{
			if (InputMgr::GetMouseUp(Mouse::Left))
			{
				SetClickMode(ClickMode::Obstacle);

				m_nowObstacle = SelectObstacle->GetIndex();
			}
		}
	}


	for (auto SelectStar : SelectStarList)
	{
		SelectStar->OnEdge(m_nowStar);
		if (SelectStar->CollisionCheck(ScreenToToolPos(InputMgr::GetMousePosI()), m_nowStar))
		{
			if (InputMgr::GetMouseUp(Mouse::Left))
			{
				SetClickMode(ClickMode::Monster);

				m_nowStar = SelectStar->GetIndex();
			}
		}
	}

	for (auto SelectMonster : SelectMonsterList)
	{
		if (SelectMonster->GetThemeTypes() == (ThemeTypes)m_nowTheme)
		{
			SelectMonster->SetActive(true);
		}
		else
		{
			SelectMonster->SetActive(false);
		}
		SelectMonster->OnEdge(m_monster);
		if (SelectMonster->CollisionCheck(ScreenToToolPos(InputMgr::GetMousePosI()), m_monster))
		{
			if (InputMgr::GetMouseUp(Mouse::Left))
			{
				SetClickMode(ClickMode::Monster);

				m_monster = SelectMonster->GetIndex();
				//cout << m_monster << endl;
			}
		}
	}

	for (int i = 0; i < GAME_TILE_HEIGHT - 4; ++i)
	{
		for (int j = 0; j < GAME_TILE_WIDTH; ++j)
		{
			if (ToolChapterLIst[m_nowChapter - 1]->
				GetToolStage()[m_nowStage - 1]->
				GetTileTool()[i][j]->
				CollisionCheck(ScreenToToolPos(InputMgr::GetMousePosI()), 1))
			{
				if (InputMgr::GetMouseUp(Mouse::Left))
				{
					if (m_clickMode == ClickMode::Monster)
					{
						ToolChapterLIst[m_nowChapter - 1]->
							GetToolStage()[m_nowStage - 1]->
							GetTileTool()[i][j]->SetMonster((ThemeTypes)m_nowTheme, m_monster, m_nowStar);
					}
					else if (m_clickMode == ClickMode::Obstacle)
					{
						ToolChapterLIst[m_nowChapter - 1]->
							GetToolStage()[m_nowStage - 1]->
							GetTileTool()[i][j]->SetObstacle((ThemeTypes)m_nowTheme, m_nowObstacle);
					}
				}
				else if (InputMgr::GetMouseUp(Mouse::Right))
				{
					ToolChapterLIst[m_nowChapter - 1]->
						GetToolStage()[m_nowStage - 1]->
						GetTileTool()[i][j]->SetEraser();
				}
			}
		}
	}

	//if (InputMgr::GetKeyDown(Keyboard::Key::F6))
	//{
	//	Chapters cha = GAME_MGR->GetPlayTiles();

	//	int a=0;
	//}

	if (InputMgr::GetKeyDown(Keyboard::Key::F3))
	{
		FileManager* file = new FileManager();

		file->SaveTileData(*this);

		delete file;
	}

	if (InputMgr::GetKeyDown(Keyboard::Key::F4))
	{
		FileManager* file = new FileManager();

		file->LoadTileData(*this);

		delete file;
	}

	Scene::Update(dt);
}

void ToolScene::Draw(RenderWindow& window)
{
	for (int i = 0; i < GAME_TILE_HEIGHT; ++i)
	{
		for (int j = 0; j < GAME_TILE_WIDTH; ++j)
		{
			ToolChapterLIst[m_nowChapter - 1]->
				GetToolStage()[m_nowStage - 1]->
				GetTileTool()[i][j]->Draw(window);
		}
	}

	Scene::Draw(window);
}

//void ToolScene::CreateTilePlay(int maxChapter, int maxStage, int cols, int rows, float quadWidth, float quadHeight)
//{
//	m_TilePlayList.assign(cols, vector<TilePlay*>(rows));
//
//	int count = 0;
//
//	for (int i = 0; i < cols; ++i)
//	{
//		TileTypes tileTypes;
//		if (i >= 10)
//		{
//			tileTypes = TileTypes::PlayerArea;
//		}
//		else
//		{
//			tileTypes = TileTypes::None;
//		}
//
//		for (int j = 0; j < rows; ++j)
//		{
//			TilePlay* tilePlay = new TilePlay();
//			tilePlay->SetTilePlay({ cols, rows }, { (WINDOW_WIDTH - (quadWidth * 8)) + (j * quadWidth), quadHeight + (i * quadHeight) }, count++, tileTypes);
//
//			objList.push_back(tilePlay);
//			m_TilePlayList[i][j] = tilePlay;
//		}
//	}
//}

void ToolScene::CreateUiName()
{
	UiName* chapter = new UiName();
	chapter->SetTexture(*RESOURCE_MGR->GetTexture("graphics/ToolUi/ToolUICover.png"));
	chapter->SetPos({ 60.f, 20.f });
	chapter->SetOrigin(Origins::MC);
	chapter->SetText("CHAPTER");
	UiNameList.push_back(chapter);
	objList.push_back(chapter);

	UiName* stage = new UiName();
	stage->SetTexture(*RESOURCE_MGR->GetTexture("graphics/ToolUi/ToolUICover.png"));
	stage->SetPos({ 60.f, 60.f });
	stage->SetOrigin(Origins::MC);
	stage->SetText("STAGE");
	UiNameList.push_back(stage);
	objList.push_back(stage);

	UiName* theme = new UiName();
	theme->SetTexture(*RESOURCE_MGR->GetTexture("graphics/ToolUi/ToolUICover.png"));
	theme->SetPos({ 60.f, 100.f });
	theme->SetOrigin(Origins::MC);
	theme->SetText("THEME");
	UiNameList.push_back(theme);
	objList.push_back(theme);

	UiName* tile = new UiName();
	tile->SetTexture(*RESOURCE_MGR->GetTexture("graphics/ToolUi/ToolUICover.png"));
	tile->SetPos({ 60.f, 260.f });
	tile->SetOrigin(Origins::MC);
	tile->SetText("TILE");
	UiNameList.push_back(tile);
	objList.push_back(tile);

	UiName* obstacle = new UiName();
	obstacle->SetTexture(*RESOURCE_MGR->GetTexture("graphics/ToolUi/ToolUICover.png"));
	obstacle->SetPos({ 60.f, 455.f });
	obstacle->SetOrigin(Origins::MC);
	obstacle->SetText("OBSTACLE");
	UiNameList.push_back(obstacle);
	objList.push_back(obstacle);

	UiName* monster = new UiName();
	monster->SetTexture(*RESOURCE_MGR->GetTexture("graphics/ToolUi/ToolUICover.png"));
	monster->SetPos({ 60.f, 570.f });
	monster->SetOrigin(Origins::MC);
	monster->SetText("MONSTER");
	UiNameList.push_back(monster);
	objList.push_back(monster);
}

void ToolScene::CreateChapterNum(int count)
{
	string name = "chap num";
	for (int i = 0; i < count; ++i)
	{
		Number* number = new Number(i+1);
		number->SetNum({ 140.f + (i * 40.f), 20.f }, (i + 1) / 10, (i + 1) % 10, i + 1);
		ChapterNumList.push_back(number);
		objList.push_back(number);
	}
}

void ToolScene::CreateStageNum(int count)
{
	for (int i = 0; i < count; ++i)
	{
		Number* number = new Number(i + 1);
		number->SetNum({ 140.f + (i * 40.f), 60.f }, (i + 1) / 10, (i + 1) % 10, i + 1);
		StageNumList.push_back(number);
		objList.push_back(number);
	}
}

void ToolScene::CreateTheme()
{
	for (int i = 1; i <= 3; ++i)
	{
		Theme* theme = new Theme(i);
		theme->SetTheme({ 101.f + (202 * (i - 1)) , 180.f }, i);
		ThemeList.push_back(theme);
		objList.push_back(theme);
	}
}

void ToolScene::CreateSelectTile()
{
	float x = 0.f;
	float y = 0.f;

	for (int i = 0; i < TYPE1_TILE_COUNT; ++i)
	{
		if (i % 10 == 0)
		{
			y += 51.f;
		}

		x = 51.f * (i % 10);
		SelectTile* tileSelect = new SelectTile();
		tileSelect->SetSelectTile({ 26.f + x, 255.f + y }, ThemeTypes::Goblin, i);
		SelectTileList.push_back(tileSelect);
		objList.push_back(tileSelect);
	}
}

void ToolScene::CreateSelectObstacle()
{
	float x = 0.f;
	float y = 0.f;

	//for (int i = 0; i < TYPE1_OBSTACLE_COUNT; ++i)
	for (int i = 1; i <= (int)ThemeTypes::Slime; ++i)
	{
		for (int j = 0; j < TYPE1_OBSTACLE_COUNT; ++j)
		{
			if (j % 10 == 0)
			{
				y += 66.f;
			}

			x = 66.f * (j % 10);
			SelectObstacle* selectObstacle = new SelectObstacle();
			selectObstacle->SetSelectObstacle({ 33.f + x, 445.f + y }, (ThemeTypes)i, j);
			selectObstacle->SetActive(false);
			SelectObstacleList.push_back(selectObstacle);
			objList.push_back(selectObstacle);
		}
		x = 0.f;
		y = 0.f;
	}
}

void ToolScene::CreateSelectMonster()
{
	MonsterTypes types;

	for (int i = 1; i <= (int)ThemeTypes::Slime; i++)
	{
		int count;

		switch (i)
		{
		case 1:
			count = TYPE1_MONSTER_COUNT;
			break;
		case 2:
			count = TYPE2_MONSTER_COUNT;
			break;
		case 3:
			count = TYPE3_MONSTER_COUNT;
			break;
		default:
			break;
		}
		for (int j = 0; j < count; ++j)
		{
			if (j == 0)
				types = MonsterTypes::Boss;
			else
				types = MonsterTypes::Monster;

			SelectMonster* selectMonster = new SelectMonster(types);
			selectMonster->SetSelectMonster({ 54.f + (j * 108.f),WINDOW_HEIGHT - 75.f }, (ThemeTypes)(i), j, m_nowStar);
			selectMonster->SetActive(false);
			SelectMonsterList.push_back(selectMonster);
			objList.push_back(selectMonster);
		}
	}
}

void ToolScene::CreateSelectStar()
{
	for (int i = 0; i < 7; i++)
	{
		SelectStar* selectStar = new SelectStar();

		selectStar->SetSelectStar({ 40.f + (i * 85.f) , 622.f }, (i + 1));
		SelectStarList.push_back(selectStar);
		objList.push_back(selectStar);
	}
}

void ToolScene::SetClickMode(ClickMode clickMode)
{
	switch (clickMode)
	{
	case ClickMode::None:
		m_nowChapter = 1;
		m_nowStage = 1;
		m_nowTheme = 1;
		m_nowStar = 1;
		break;
	case ClickMode::Theme:
		m_nowTileSet = -1;
		m_nowObstacle = -1;
		m_nowStar = 1;
		m_monster = -1;
		break;
	case ClickMode::Tile:
		m_nowObstacle = -1;
		m_monster = -1;
		break;
	case ClickMode::Obstacle:
		m_clickMode = ClickMode::Obstacle;
		m_nowTileSet = -1;
		m_monster = -1;
		break;
	case ClickMode::Monster:
		m_clickMode = clickMode;
		m_nowObstacle = -1;
		m_nowTileSet = -1;
		break;
	}
}

Chapters ToolScene::GetTilesData()
{
	Chapters data;
	for (int i = 0; i < ToolChapterLIst.size(); ++i)
	{
		data.data.push_back(vector<vector<vector<ns::TileData>>>());
		auto& stageList = ToolChapterLIst[i]->GetToolStage();

		for (int j = 0; j < stageList.size(); ++j)
		{
			data.data[i].push_back(vector<vector<ns::TileData>>());
			auto& tileList = stageList[j]->GetTileTool();
			for (int k = 0; k < tileList.size(); ++k)
			{
				data.data[i][j].push_back(vector<ns::TileData>());
				for (int l = 0; l < tileList[k].size(); ++l)
				{
					data.data[i][j][k].push_back(tileList[k][l]->GetTileData());
				}
			}
		}
	}
	return data;
}

void ToolScene::SetTilesData(Chapters& data)
{
	for (int i = 0; i < data.data.size(); ++i)
	{
		for (int j = 0; j < data.data[i].size(); ++j)
		{
			for (int k = 0; k < data.data[i][j].size(); ++k)
			{
				for (int l = 0; l < data.data[i][j][k].size(); ++l)
				{
					ToolChapterLIst[i]->
						GetToolStage()[j]->
						GetTileTool()[k][l]->SetTileData(data.data[i][j][k][l]);
				}
			}
		}
	}
}
