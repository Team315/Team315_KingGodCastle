#include "BattleScene.h"
#include "Include.h"
#include "BattleSceneUI.h"
#include "BattlePanel.h"
#include "Button.h"
#include "Constant.h"
#include "GameManager.h"

BattleScene::BattleScene()
	: Scene(Scenes::Battle)
{
	CLOG::Print3String("battle create");

	gameScreenTopLimit = GAME_SCREEN_HEIGHT * 0.5f;
	gameScreenBottomLimit = GAME_SCREEN_HEIGHT * 1.5f;
	CreateTestTile(GAME_TILE_HEIGHT, GAME_TILE_WIDTH, TILE_SIZE, TILE_SIZE);

	evan = new Evan();
	evan->SetPos(testTile[13][3]->GetPos());
	objList.push_back(evan);

	dummy = new Dummy();
	dummy->SetPos(testTile[10][3]->GetPos());
	objList.push_back(dummy);

	goblin00 = new Goblin00();
	goblin00->SetPos(testTile[1][3]->GetPos());
	objList.push_back(goblin00);

	float tempY = TILE_SIZE;
	overlay.resize(GAME_TILE_HEIGHT);
	float outlineThickness = 2.f;
	for (auto& tiles : overlay)
	{
		tiles = new vector<RectangleObj*>;
		tiles->resize(GAME_TILE_WIDTH);
		float tempX = TILE_SIZE * 2.f;
		for (auto& tile : *tiles)
		{
			tile = new RectangleObj(
				TILE_SIZE - outlineThickness * 2 - 1,
				TILE_SIZE - outlineThickness * 2 - 1);
			tile->SetFillColor(Color(255, 255, 255, 80));
			tile->SetOutline(Color::White, outlineThickness);
			tile->SetPos(Vector2f(tempX, tempY));
			tile->SetOrigin(Origins::BC);
			objList.push_back(tile);
			tempX += TILE_SIZE;
		}
		tempY += TILE_SIZE;
	}
	ui = new BattleSceneUI(this);
}

BattleScene::~BattleScene()
{
}

void BattleScene::Init()
{
	CLOG::Print3String("battle Init");

	//goblin00->SetTarget(evan);
	goblin00->SetTarget(dummy);
	evan->SetTarget(goblin00);
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
	currentView = gameView;

	for (auto& tiles : overlay)
	{
		for (auto& tile : *tiles)
			tile->SetActive(false);
	}
	GAME_MGR->EnterBattleScene();
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
	if (InputMgr::GetKeyDown(Keyboard::Down))
	{
		MoveDownTile();
	}
	if (InputMgr::GetKeyDown(Keyboard::Up))
	{
		MoveUpTile();
		//CLOG::PrintVectorState(dummy->GetPos(), "dummy");
	}
	if (InputMgr::GetKeyDown(Keyboard::F6))
	{
		CLOG::Print3String("print prepare vector");
		CLOG::Print3String("prepare vector");
		int idx = 0;
		vector<int>& prepare = GAME_MGR->GetPrepare();
		for (auto& cell : prepare)
		{
			cout << cell;
			idx++;
			if (idx % 7 == 0)
				cout << endl;
		}
		queue<int>& waitQueue = GAME_MGR->GetWaitQueue();
		int size = waitQueue.size();
		CLOG::Print3String("wait queue");
		for (int i = 0; i < size; i++)
		{
			cout << waitQueue.front();
			waitQueue.pop();
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
					b_centerPos = true;
					CLOG::Print3String("stage start");
					break;
				}
				if (!button->GetName().compare("summon"))
				{
					if (GAME_MGR->GetPrepareSize() == PREPARE_SIZE)
					{
						CLOG::Print3String("can not summon");
						break;
					}
					int idx = GAME_MGR->GetPresetElem(Utils::RandomRange(0, PRESET_SIZE));
					CLOG::Print3String(to_string(idx));
					GAME_MGR->AddPrepare(idx);
					break;
				}
			}
		}
	}

	float wheel = InputMgr::GetMouseWheel();
	if (wheel != 0)
	{
		b_centerPos = wheel == 1 ? true : false;
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
	// Game Input end

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

void BattleScene::MoveDownTile()
{
	nowTile = dummy->GetPos();
	nowTile.y += TILE_SIZE;
	dummy->SetDestination(nowTile);
	dummy->SetMove(true);
	//dummy->SetPos(nowTile);
}

void BattleScene::MoveUpTile()
{
	nowTile = dummy->GetPos();
	nowTile.y -= TILE_SIZE;
	dummy->SetDestination(nowTile);
	dummy->SetMove(true);
	//dummy->SetPos(nowTile);
}

void BattleScene::MoveLeftTile()
{
}

void BattleScene::MoveRightTile()
{
}

void BattleScene::AIMove()
{
}
