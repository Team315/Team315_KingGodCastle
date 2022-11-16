#include "BattleScene.h"
#include "Include.h"
#include "BattleSceneUI.h"
#include "BattlePanel.h"
#include "Button.h"
#include "Constant.h"

BattleScene::BattleScene()
	: Scene(Scenes::Battle)
{
	CLOG::Print3String("battle create");

	/*CreateBackground(TILE_WIDTH, TILE_HEIGHT * 2, TILE_SIZE_X, TILE_SIZE_Y);
	screenCenterPos = Vector2f(GAME_SCREEN_WIDTH * 0.5f, GAME_SCREEN_HEIGHT);
	
	
	background->SetPos(screenCenterPos);
	background->SetOrigin(Origins::MC);*/

	gameScreenTopLimit = GAME_SCREEN_HEIGHT * 0.5f;
	gameScreenBottomLimit = GAME_SCREEN_HEIGHT * 1.5f;
	CreateTestTile(14, 7, 51.f, 51.f);

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

	float tempY = TILE_SIZE_Y;
	overlay.resize(GAME_TILE_HEIGHT);
	float outlineThickness = 2.f;
	for (auto& tiles : overlay)
	{
		tiles = new vector<RectangleObj*>;
		tiles->resize(GAME_TILE_WIDTH);
		float tempX = TILE_SIZE_X * 2.f;
		for (auto& tile : *tiles)
		{
			tile = new RectangleObj(
				TILE_SIZE_X - outlineThickness * 2 - 1,
				TILE_SIZE_Y - outlineThickness * 2 - 1);
			tile->SetFillColor(Color(255, 255, 255, 80));
			tile->SetOutline(Color::White, outlineThickness);
			tile->SetPos(Vector2f(tempX, tempY));
			tile->SetOrigin(Origins::BC);
			objList.push_back(tile);
			tempX += TILE_SIZE_X;
		}
		tempY += TILE_SIZE_Y;
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
	//evan->SetTarget(goblin00);
	goblin00->SetTarget(dummy);
	dummy->SetTarget(goblin00);
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
		MoveTile(Dir::Down);
		//MoveDownTile();
	}
	if (InputMgr::GetKeyDown(Keyboard::Up))
	{
		MoveTile(Dir::Up);
		//MoveUpTile();
	}
	if (InputMgr::GetKeyDown(Keyboard::Left))
	{
		MoveTile(Dir::Left);
		//MoveLeftTile();
	}
	if (InputMgr::GetKeyDown(Keyboard::Right))
	{
		MoveTile(Dir::Right);
		//MoveRightTile();
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
				CLOG::Print3String(button->GetName());
				if (!button->GetName().compare("begin"))
				{
					b_centerPos = true;
					CLOG::Print3String("stage start");
					break;
				}
				if (!button->GetName().compare("summon"))
				{

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
	

	nowTile = dummy->GetPos();
	switch (currMoveDir)
	{
	case Dir::Up:
		nowTile.y -= TILE_SIZE_Y;
		break;
	case Dir::Down:
		nowTile.y += TILE_SIZE_Y;
		break;
	case Dir::Left:
		nowTile.x -= TILE_SIZE_X;
		break;
	case Dir::Right:
		nowTile.x += TILE_SIZE_X;
		break;
	}
	dummy->SetDestination(nowTile);
	dummy->SetMove(true);
}

void BattleScene::AIMove()
{
}

