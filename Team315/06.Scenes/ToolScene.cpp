#include "ToolScene.h"
#include "Include.h"
#include "TileSet.h"
#include "UiName.h"
#include "Number.h"
#include "TextObj.h"
#include "Theme.h"
#include "TileSelect.h"

ToolScene::ToolScene()
	: Scene(Scenes::Tool)
{
	CLOG::Print3String("tool create");
}

ToolScene::~ToolScene()
{
	Release();
}

void ToolScene::Init()
{
	CLOG::Print3String("tool Init");

	CreateTileSet(Tile_WIDTH, Tile_HEIGHT, Tile_SizeX, Tile_SizeY);
	CreateUiName();
	CreateChapterNum(ChapterMaxCount);
	CreateStageNum(StageMaxCount);
	CreateTheme();
	CreateTileSelect();

	for (auto obj : objList)
	{
		obj->Init();
	}
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
}

void ToolScene::Exit()
{
	CLOG::Print3String("tool exit");
}

void ToolScene::Update(float dt)
{
	if (InputMgr::GetKeyDown(Keyboard::Key::Escape))
	{
		SCENE_MGR->ChangeScene(Scenes::Loby);
		return;
	}

	for (const auto& tile : tileSetList)
	{
		if (tile->GetActive())
		{
			tile->Update(dt);
		}
	}

	for (const auto& UiName : UiNameList)
	{
		if (UiName->GetActive())
		{
			UiName->Update(dt);
		}
	}

	for (const auto& ChapterNum : ChapterNumList)
	{
		if (ChapterNum->GetActive())
		{
			ChapterNum->Update(dt);
		}
	}

	for (const auto& StageNum : StageNumList)
	{
		if (StageNum->GetActive())
		{
			StageNum->Update(dt);
		}
	}

	for (const auto& Theme : ThemeList)
	{
		if (Theme->GetActive())
		{
			Theme->Update(dt);
		}
	}

	for (const auto& TileSelect : TileSelectList)
	{
		if (TileSelect->GetActive())
		{
			TileSelect->Update(dt);
		}
	}
	Scene::Update(dt);
}

void ToolScene::Draw(RenderWindow& window)
{
	Scene::Draw(window);

	for (const auto& tile : tileSetList)
	{
		if (tile->GetActive())
		{
			tile->Draw(window);
		}
	}

	for (const auto& UiName : UiNameList)
	{
		if (UiName->GetActive())
		{
			UiName->Draw(window);
		}
	}

	for (const auto& ChapterNum : ChapterNumList)
	{
		if (ChapterNum->GetActive())
		{
			ChapterNum->Draw(window);
		}
	}

	for (const auto& StageNum : StageNumList)
	{
		if (StageNum->GetActive())
		{
			StageNum->Draw(window);
		}
	}

	for (const auto& Theme : ThemeList)
	{
		if (Theme->GetActive())
		{
			Theme->Draw(window);
		}
	}

	for (const auto& TileSelect : TileSelectList)
	{
		if (TileSelect->GetActive())
		{
			TileSelect->Draw(window);
		}
	}
}

void ToolScene::CreateTileSet(int cols, int rows, float quadWidth, float quadHeight)
{
	if (m_TileSet == nullptr)
	{
		m_TileSet = new TileSet();
		m_TileSet->SetTexture(GetTexture("graphics/TileSet/Field_01.png"));
		tileSetList.push_back(m_TileSet);
		m_TileSet->Init();
	}

	//Vector2f startPos = m_TileSet->GetPos();
	Vector2f startPos = { WINDOW_WIDTH - (cols * quadWidth), 0.f };

	VertexArray& va = m_TileSet->GetVA();
	va.clear();
	va.setPrimitiveType(Quads);
	va.resize(cols * rows * 4);
	Vector2f currPos = startPos;

	Vector2f offsets[4] = {
		{ 0, 0 },
		{ quadWidth, 0 },
		{ quadWidth, quadHeight },
		{ 0, quadHeight },
	};

	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			/*int texIndex = Utils::RandomRange(0, 3);
			if ((i == 0 || i == rows - 1) || (j == 0 || j == cols - 1))
			{
				texIndex = 3;
			}*/

			int quadIndex = i * cols + j;

			for (int k = 0; k < 4; ++k)
			{
				int vertexIndex = quadIndex * 4 + k;
				va[vertexIndex].position = currPos + offsets[k];
				va[vertexIndex].texCoords = offsets[k];
				va[vertexIndex].texCoords.y += quadHeight /** texIndex*/;

			}
			currPos.x += Tile_SizeX;
		}
		currPos.x = startPos.x;
		currPos.y += Tile_SizeY;
	}
}

void ToolScene::CreateUiName()
{
	UiName* chapter = new UiName();
	chapter->SetTexture(*RESOURCE_MGR->GetTexture("graphics/ToolUi/ToolUICover.png"));
	chapter->SetPos({ 60.f, 20.f });
	chapter->SetOrigin(Origins::MC);
	chapter->SetText("CHAPTER");
	UiNameList.push_back(chapter);

	UiName* stage = new UiName();
	stage->SetTexture(*RESOURCE_MGR->GetTexture("graphics/ToolUi/ToolUICover.png"));
	stage->SetPos({ 60.f, 60.f });
	stage->SetOrigin(Origins::MC);
	stage->SetText("STAGE");
	UiNameList.push_back(stage);

	UiName* theme = new UiName();
	theme->SetTexture(*RESOURCE_MGR->GetTexture("graphics/ToolUi/ToolUICover.png"));
	theme->SetPos({ 60.f, 100.f });
	theme->SetOrigin(Origins::MC);
	theme->SetText("THEME");
	UiNameList.push_back(theme);

	UiName* tile = new UiName();
	tile->SetTexture(*RESOURCE_MGR->GetTexture("graphics/ToolUi/ToolUICover.png"));
	tile->SetPos({ 60.f, 260.f });
	tile->SetOrigin(Origins::MC);
	tile->SetText("TILE");
	UiNameList.push_back(tile);

	UiName* obstacle = new UiName();
	obstacle->SetTexture(*RESOURCE_MGR->GetTexture("graphics/ToolUi/ToolUICover.png"));
	obstacle->SetPos({ 60.f, 500.f });
	obstacle->SetOrigin(Origins::MC);
	obstacle->SetText("OBSTACLE");
	UiNameList.push_back(obstacle);

	UiName* monster = new UiName();
	monster->SetTexture(*RESOURCE_MGR->GetTexture("graphics/ToolUi/ToolUICover.png"));
	monster->SetPos({ 60.f, 600.f });
	monster->SetOrigin(Origins::MC);
	monster->SetText("MONSTER");
	UiNameList.push_back(monster);
}

void ToolScene::CreateChapterNum(int count)
{
	for (int i = 0; i < count; ++i)
	{
		Number* number = new Number();
		number->SetNum({ 140.f + (i * 40.f), 20.f }, (i + 1) / 10, (i + 1) % 10, i + 1);
		ChapterNumList.push_back(number);
	}
}

void ToolScene::CreateStageNum(int count)
{
	for (int i = 0; i < count; ++i)
	{
		Number* number = new Number();
		number->SetNum({ 140.f + (i * 40.f), 60.f }, (i + 1) / 10, (i + 1) % 10, i + 1);
		StageNumList.push_back(number);
	}
}

void ToolScene::CreateTheme()
{
	for (int i = 1; i <= 3; ++i)
	{
		Theme* theme = new Theme();
		theme->SetTheme({ 101.f + (202 * (i - 1)) , 180.f }, i);
		ThemeList.push_back(theme);
	}
}

void ToolScene::CreateTileSelect()
{
	float x = 0.f;
	float y = 0.f;

	for (int i = 0; i < Tile_1Type_Count; ++i)
	{
		if (i % 10 == 0)
		{
			y += 51.f;
		}

		x = 51.f * (i % 10);
		TileSelect* tileSelect = new TileSelect();
		tileSelect->SetTileSelect({ 26.f + x, 255.f + y }, ThemeTypes::Goblin, i);
		TileSelectList.push_back(tileSelect);
	}
	
}
