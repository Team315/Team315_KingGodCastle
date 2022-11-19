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
	battleGridRect.resize(BATTLE_GRID_ROW);
	battleGrid.resize(BATTLE_GRID_ROW);
	float outlineThickness = 2.f;
	for (auto& tiles : battleGridRect)
	{
		tiles.resize(GAME_TILE_WIDTH);
		float tempX = TILE_SIZE * 2.f;
		for (auto& tile : tiles)
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
	for (auto& row : battleGrid)
		row.resize(GAME_TILE_WIDTH);

	/*evan = new Evan();
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
	objList.push_back(goblin00);*/

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

	FRAMEWORK->GetWindow().setSize(
		Vector2u((unsigned int)GAME_SCREEN_WIDTH, (unsigned int)GAME_SCREEN_HEIGHT));
	screenCenterPos = Vector2f(GAME_SCREEN_WIDTH * 0.5f, GAME_SCREEN_HEIGHT);
	screenSize = FRAMEWORK->GetWindow().getSize();
	currentView = gameView;

	for (auto& tiles : battleGridRect)
	{
		for (auto& tile : tiles)
			tile->SetActive(false);
	}
	GAME_MGR->EnterBattleScene();
	prepareGrid.assign(PREPARE_SIZE, 0);
}

void BattleScene::Exit()
{
	CLOG::Print3String("battle exit");
	for (auto& character : prepareGrid)
	{
		delete character;
	}
	prepareGrid.clear();
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
			b_battleGridRect = !b_battleGridRect;

			for (auto& tiles : battleGridRect)
			{
				for (auto& tile : tiles)
					tile->SetActive(b_battleGridRect);
			}
		}
		if (InputMgr::GetKeyDown(Keyboard::Key::F7))
		{
			CLOG::Print3String("battle devmode switch");
			FRAMEWORK->devMode = !FRAMEWORK->devMode;
		}
		if (InputMgr::GetKeyDown(Keyboard::Key::F8))
		{
			CLOG::Print3String("prepareGrid state");
			int count = 0;
			for (auto& character : prepareGrid)
			{
				if (character == nullptr)
					cout << 0 << ' ';
				else
					cout << 1 << ' ';
				count++;
				if (count == 7)
					cout << endl;
			}
			cout << endl;
		}
		/*if (InputMgr::GetKeyDown(Keyboard::Down))
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
		}*/
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
				// battle start
				if (!button->GetName().compare("begin"))
				{
					CLOG::Print3String("stage start");
					b_centerPos = true;
					ZoomIn();
					for (auto& character : prepareGrid)
					{
						if (character != nullptr)
							character->SetDrawInBattle(true);
					}
					break;
				}
				// summon character
				if (!button->GetName().compare("summon"))
				{
					if (GAME_MGR->GetPrepareSize() == PREPARE_SIZE)
					{
						CLOG::Print3String("can not summon");
						break;
					}
					int idx = GetZeroElem(prepareGrid);
					if (idx == -1)
					{
						CLOG::Print3String("can not");
						return;
					}
					int ran = Utils::RandomRange(0, PRESET_SIZE);
					Character* test;
					if (ran % 2)
						test = new Evan();
					else
						test = new Goblin00();
					test->SetPos(ui->GetPrepareGridPos(idx));
					test->Init();
					test->SetDrawInBattle(false);
					prepareGrid[idx] = test;
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
		b_centerPos ? ZoomIn() : ZoomOut();
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

	// prepare grid & battle grid - character pick up
	for (auto& character : prepareGrid)
	{
		if (character == nullptr)
			break;

		character->Update(dt);
		if (character->CollideTest(ScreenToWorldPos(InputMgr::GetMousePosI())))
		{
			if (InputMgr::GetMouseDown(Mouse::Left))
			{
				if (drag == nullptr)
				{
					DragAction(character);
					break;
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
		Vector2i destIdx = GAME_MGR->PosToIdx(drag->GetPos() + Vector2f(TILE_SIZE_HALF, TILE_SIZE_HALF));

		if (InPrepareGrid(destIdx) || InBattleGrid(destIdx))
		{
			Vector2f coord = GAME_MGR->IdxToPos(destIdx);
			drag->SetPos(coord);
			CLOG::PrintVectorState(destIdx, "can move");
			cout << GetPrepareIdxFromCoord(destIdx) << endl;
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

	for (auto& character : prepareGrid)
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

void BattleScene::MoveTile(Character* character, Dir currMoveDir)
{
	Vector2i curPos = GAME_MGR->PosToIdx(character->GetPos());
	TilePlay* curTile = testTile[curPos.y][curPos.x];
	
	nowTile = character->GetPos();
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
	character->SetDestination(nowTile);
	Vector2i idx = GAME_MGR->PosToIdx(nowTile);
	//CLOG::PrintVectorState(nowTile, "now");
	//CLOG::PrintVectorState(idx, "idx");
	TilePlay* nextTile = testTile[idx.y][idx.x];
	if (nextTile->GetOnTileObj() != nullptr)
		return;
	curTile->SetOnTileObj(nullptr);
	nextTile->SetOnTileObj(character);
	character->SetMove(true);
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

void BattleScene::DragAction(Character* character)
{
	beforeDragPos = character->GetPos();
	drag = character;
	drag->SetHitBoxActive(false);
}

int BattleScene::GetPrepareIdxFromCoord(Vector2i coord)
{
	return coord.x + (coord.y - 16) * PREPARE_SIZE * 0.5f;
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