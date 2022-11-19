#include "BattleScene.h"
#include "Include.h"
#include "BattleSceneUI.h"
#include "BattlePanel.h"
#include "Button.h"
#include "Constant.h"
#include "GameManager.h"

BattleScene::BattleScene()
	: Scene(Scenes::Battle), drag(nullptr)
{
	CLOG::Print3String("battle create");

	gameScreenTopLimit = GAME_SCREEN_HEIGHT * 0.5f;
	gameScreenBottomLimit = GAME_SCREEN_HEIGHT * 1.1f;
	CreateTestTile(GAME_TILE_HEIGHT, GAME_TILE_WIDTH, TILE_SIZE, TILE_SIZE);

	float tempY = TILE_SIZE * 11.f;
	battleGrid.resize(BATTLE_GRID_SIZE);
	float outlineThickness = 2.f;
	for (auto& tiles : battleGrid)
	{
		tiles = new vector<RectangleObj*>;
		tiles->resize(GAME_TILE_WIDTH);
		float tempX = TILE_SIZE * 2.f;
		for (auto& tile : *tiles)
		{
			tile = new RectangleObj(
				TILE_SIZE - outlineThickness * 2 - 1,
				TILE_SIZE - outlineThickness * 2 - 1);
			tile->SetFillColor(Color(255, 255, 255, 20));
			tile->SetOutline(Color::White, outlineThickness);
			tile->SetPos(Vector2f(tempX, tempY));
			tile->SetOrigin(Origins::BC);
			objList.push_back(tile);
			tempX += TILE_SIZE;
		}
		tempY += TILE_SIZE;
	}

	evan = new Evan();
	evan->SetPos(testTile[13][3]->GetPos());
	testTile[13][3]->SetOnTileObj(evan);
	objList.push_back(evan);

	dummy = new Dummy();
	dummy->SetPos(testTile[10][3]->GetPos());
	testTile[10][3]->SetOnTileObj(dummy);
	objList.push_back(dummy);

	goblin00 = new Goblin00();
	goblin00->SetPos(testTile[1][3]->GetPos());
	testTile[1][3]->SetOnTileObj(goblin00);
	objList.push_back(goblin00);

	ui = new BattleSceneUI(this);
}

BattleScene::~BattleScene()
{
}

void BattleScene::Init()
{
	CLOG::Print3String("battle Init");

	//goblin00->SetTarget(evan);
	//evan->SetTarget(goblin00);
	/*goblin00->SetTarget(dummy);
	dummy->SetTarget(goblin00);*/

	objList.push_back(ui);
	Scene::Init();
}

void BattleScene::Release()
{
}

void BattleScene::Enter()
{
	CLOG::Print3String("battle enter");

	FRAMEWORK->GetWindow().setSize(Vector2u(GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT));
	screenCenterPos = Vector2f(GAME_SCREEN_WIDTH * 0.5f, GAME_SCREEN_HEIGHT);
	screenSize = FRAMEWORK->GetWindow().getSize();
	currentView = gameView;

	for (auto& tiles : battleGrid)
	{
		for (auto& tile : *tiles)
			tile->SetActive(false);
	}
	GAME_MGR->EnterBattleScene();
	prepare.assign(PREPARE_SIZE, 0);
}

void BattleScene::Exit()
{
	CLOG::Print3String("battle exit");
	for (auto& character : prepare)
	{
		delete character;
	}
	prepare.clear();
}

void BattleScene::Update(float dt)
{
	// Dev Input start
	{
		if (InputMgr::GetKeyDown(Keyboard::Key::Escape))
		{
			CLOG::Print3String("setting window");
			SCENE_MGR->ChangeScene(Scenes::Loby);
			return;
		}
		if (InputMgr::GetKeyDown(Keyboard::Key::Num0))
		{
			CLOG::Print3String("overlay switch");
			b_battleGrid = !b_battleGrid;

			for (auto& tiles : battleGrid)
			{
				for (auto& tile : *tiles)
					tile->SetActive(b_battleGrid);
			}
		}
		if (InputMgr::GetKeyDown(Keyboard::Key::F7))
		{
			CLOG::Print3String("battle devmode on");
			FRAMEWORK->devMode = true;
		}
		if (InputMgr::GetKeyDown(Keyboard::Key::F8))
		{
			CLOG::Print3String("battle devmode off");
			FRAMEWORK->devMode = false;
		}
		if (InputMgr::GetKeyDown(Keyboard::Down))
		{
			MoveTile(Dir::Down);
		}
		if (InputMgr::GetKeyDown(Keyboard::Up))
		{
			MoveTile(Dir::Up);
		}
		if (InputMgr::GetKeyDown(Keyboard::Left))
		{
			MoveTile(Dir::Left);
		}
		if (InputMgr::GetKeyDown(Keyboard::Right))
		{
			MoveTile(Dir::Right);
		}
	}
	// Dev Input end

	// Game Input start
	vector<Button*>& buttons = ui->GetPanel()->GetButtons();
	for (auto button : buttons)
	{
		if (button->CollideTest(ScreenToWorldPos(InputMgr::GetMousePosI())))
		{
			if (InputMgr::GetMouseDown(Mouse::Left))
			{
				//CLOG::Print3String(button->GetName());
				if (!button->GetName().compare("begin"))
				{
					CLOG::Print3String("stage start");
					b_centerPos = true;
					ZoomIn();
					for (auto& character : prepare)
					{
						if (character != nullptr)
							character->SetDrawInBattle(true);
					}
					break;
				}
				if (!button->GetName().compare("summon"))
				{
					if (GAME_MGR->GetPrepareSize() == PREPARE_SIZE)
					{
						CLOG::Print3String("can not summon");
						break;
					}
					/*int idx = GAME_MGR->GetPresetElem(Utils::RandomRange(0, PRESET_SIZE));
					CLOG::Print3String(to_string(idx));
					GAME_MGR->AddPrepare(idx);
					CLOG::PrintVectorState(ui->GetPrepareGridPos(0));*/

					int idx = GetZeroElem(prepare);
					if (idx == -1)
					{
						CLOG::Print3String("can not");
						return;
					}
					int ran = Utils::RandomRange(0, 2);
					Character* test;
					if (ran == 0)
						test = new Evan();
					else
						test = new Goblin00();
					test->SetPos(ui->GetPrepareGridPos(idx));
					test->Init();
					test->SetDrawInBattle(false);
					prepare[idx] = test;
					break;
				}
			}
		}
	}

	// wheel control
	float wheel = InputMgr::GetMouseWheel();
	if (wheel != 0)
	{
		b_centerPos = wheel == 1 ? true : false;
		if (b_centerPos)
			ZoomIn();
		else
			ZoomOut();
	}
	if (b_centerPos)
	{
		if (screenCenterPos.y >= gameScreenTopLimit)
		{
			screenCenterPos.y -= dt * (screenCenterPos.y - gameScreenTopLimit) * 25.f;
			gameView.setCenter(screenCenterPos);
		}
	}
	else
	{
		if (screenCenterPos.y <= gameScreenBottomLimit)
		{
			screenCenterPos.y += dt * (gameScreenBottomLimit - screenCenterPos.y) * 25.f;
			gameView.setCenter(screenCenterPos);
		}
	}

	// prepare grid
	for (auto& character : prepare)
	{
		if (character == nullptr)
			break;

		character->Update(dt);
		if (character->GetHitbox().getGlobalBounds().contains(ScreenToWorldPos(InputMgr::GetMousePosI())))
		{
			if (InputMgr::GetMouseDown(Mouse::Left))
			{
				if (drag == nullptr)
				{
					beforeDragPos = character->GetPos();
					drag = character;
					drag->SetHitBoxActive(false);
				}
			}
		}
	}

	// mouse drag control
	if (drag != nullptr && InputMgr::GetMouse(Mouse::Left))
	{
		drag->SetPos(ScreenToWorldPos(InputMgr::GetMousePosI()) + Vector2f(0, TILE_SIZE_HALF));
	}

	if (drag != nullptr && InputMgr::GetMouseUp(Mouse::Left))
	{
		Vector2i destIdx = GAME_MGR->PosToIdx(drag->GetPos() + Vector2f(0, TILE_SIZE_HALF));

		if (InPrepareGrid(destIdx) || InBattleGrid(destIdx))
		{
			drag->SetPos(GAME_MGR->IdxToPos(destIdx));
			CLOG::PrintVectorState(destIdx, "can move");
		}
		else
		{
			drag->SetPos(beforeDragPos);
			CLOG::PrintVectorState(destIdx, "can not move");
		}
		drag->SetHitBoxActive(true);
		drag = nullptr;
	}
	// Game Input end

	Scene::Update(dt);
}

void BattleScene::Draw(RenderWindow& window)
{
	Scene::Draw(window);

	for (auto& character : prepare)
	{
		if (character != nullptr)
			character->Draw(window);
	}
}

void BattleScene::CreateTestTile(int cols, int rows, float width, float height)
{
	testTile.assign(cols, vector<TilePlay*>(rows));

	int count = 0;
	for (int i = 0; i < cols; ++i)
	{
		for (int j = 0; j < rows; ++j)
		{
			tilePlay = new TilePlay();
			tilePlay->SetTilePlay({ cols, rows },
				{ ((width / 2) + (width * 1.5f)) + (j * width),
				height + (i * height) },
				count++);
			objList.push_back(tilePlay);
			testTile[i][j] = tilePlay;
		}
	}
}

void BattleScene::MoveTile(Dir currMoveDir)
{
	Vector2i curPos = GAME_MGR->PosToIdx(dummy->GetPos());
	TilePlay* curTile = testTile[curPos.y][curPos.x];
	
	nowTile = dummy->GetPos();
	switch (currMoveDir)
	{
	case Dir::Up:
		nowTile.y -= TILE_SIZE;
		break;
	case Dir::Down:
		nowTile.y += TILE_SIZE;
		break;
	case Dir::Left:
		nowTile.x -= TILE_SIZE;
		break;
	case Dir::Right:
		nowTile.x += TILE_SIZE;
		break;
	}
	dummy->SetDestination(nowTile);
	Vector2i idx = GAME_MGR->PosToIdx(nowTile);
	//CLOG::PrintVectorState(nowTile, "now");
	//CLOG::PrintVectorState(idx, "idx");
	TilePlay* nextTile = testTile[idx.y][idx.x];
	if (nextTile->GetOnTileObj() != nullptr)
		return;
	curTile->SetOnTileObj(nullptr);
	nextTile->SetOnTileObj(dummy);
	dummy->SetMove(true);
}

void BattleScene::ZoomIn()
{
	currentView.setSize(GAME_SCREEN_ZOOM_WIDTH, GAME_SCREEN_ZOOM_HEIGHT);
}

void BattleScene::ZoomOut()
{
	currentView.setSize(GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT);
}

void BattleScene::AIMove()
{
	
}

bool InPrepareGrid(Vector2i pos)
{
	return (pos.x >= 0 && pos.x < 7) && (pos.y >= 16 && pos.y < 18); // x(0, 6) y(16, 17)
}

bool InBattleGrid(Vector2i pos)
{
	return (pos.x >= 0 && pos.x < 7) && (pos.y >= 10 && pos.y < 14); // x(0, 6) y(10, 13)
}

int GetZeroElem(vector<Character*> vec)
{
	for (int idx = 0; idx < PREPARE_SIZE; idx++)
	{
		if (vec[idx] == nullptr)
			return idx;
	}
	return -1; // fail
}