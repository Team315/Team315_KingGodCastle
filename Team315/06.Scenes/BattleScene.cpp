#include "BattleScene.h"
#include "Include.h"
#include "Constant.h"

BattleScene::BattleScene()
	: Scene(Scenes::Battle)
{
	CLOG::Print3String("battle create");

	CreateTestTile(14, 7, 51.f, 51.f);

	evan = new Evan();
	Vector2f pos1 = testTile[13][3]->GetPos();
	pos1.y -= 51.f;
	evan->SetPos(pos1);
	objList.push_back(evan);

	goblin00 = new Goblin00();
	Vector2f pos2 = testTile[0][3]->GetPos();
	pos2.y -= 51.f;
	goblin00->SetPos(pos2);
	objList.push_back(goblin00);

	float tempY = TILE_SIZE_Y;
	overlay.resize(GAME_TILE_HEIGHT);
	for (auto& tiles : overlay)
	{
		tiles = new vector<RectangleObj*>;
		tiles->resize(GAME_TILE_WIDTH);
		float tempX = TILE_SIZE_X * 2.f;
		for (auto& tile : *tiles)
		{
			tile = new RectangleObj(47.f, 47.f);
			tile->SetFillColor(Color(255, 255, 255, 80));
			tile->SetOutline(Color::White, 1.5f);
			tile->SetPos(Vector2f(tempX, tempY));
			tile->SetOrigin(Origins::BC);
			objList.push_back(tile);
			tempX += TILE_SIZE_X;
		}
		tempY += TILE_SIZE_Y;
	}
}

BattleScene::~BattleScene()
{
}

void BattleScene::Init()
{
	CLOG::Print3String("battle Init");

	goblin00->SetTarget(evan);
	evan->SetTarget(goblin00);
	Scene::Init();
}

void BattleScene::Release()
{
}

void BattleScene::Enter()
{
	CLOG::Print3String("battle enter");

	FRAMEWORK->GetWindow().setSize(Vector2u(GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT));
	currentView = gameView;

	for (auto& tiles : overlay)
	{
		for (auto& tile : *tiles)
			tile->SetActive(false);
	}
}

void BattleScene::Exit()
{
	CLOG::Print3String("battle exit");
}

void BattleScene::Update(float dt)
{
	// Dev Input start
	if (InputMgr::GetKeyDown(Keyboard::Key::Escape))
	{
		CLOG::Print3String("setting window");
		SCENE_MGR->ChangeScene(Scenes::Loby);
		return;
	}
	if (InputMgr::GetKeyDown(Keyboard::Key::Num0))
	{
		CLOG::Print3String("overlay true");
		for (auto& tiles : overlay)
		{
			for (auto& tile : *tiles)
				tile->SetActive(true);
		}
	}
	if (InputMgr::GetKeyUp(Keyboard::Key::Num0))
	{
		CLOG::Print3String("overlay false");
		for (auto& tiles : overlay)
		{
			for (auto& tile : *tiles)
				tile->SetActive(false);
		}
	}
	float wheel = InputMgr::GetMouseWheel();
	if (wheel != 0)
	{
		CLOG::Print3String(to_string(wheel));
	}
	// Dev Input end

	Scene::Update(dt);
}

void BattleScene::Draw(RenderWindow& window)
{
	Scene::Draw(window);
}

void BattleScene::CreateTestTile(int cols, int rows, float width, float height)
{
	testTile.assign(cols, vector<TilePlay*>(rows));

	int count = 0;
	for (int i = 0; i < cols; ++i)
	{
		for (int j = 0; j < rows; ++j)
		{
			TilePlay* tilePlay = new TilePlay();
			tilePlay->SetTilePlay({ cols, rows },
				{ ((width / 2) + (width * 1.5f)) + (j * width),
				height + (i * height) },
				count++);

			objList.push_back(tilePlay);
			testTile[i][j] = tilePlay;
		}
	}
}
