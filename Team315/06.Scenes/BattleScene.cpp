#include "BattleScene.h"
#include "BattleSceneUI.h"
#include "BattlePanel.h"
#include "Button.h"
#include "Constant.h"
#include "GameManager.h"
#include "Map/Tile.h"
#include "RectangleObj.h"
#include "VertexArrayObj.h"
#include "CharacterHeaders.h"

BattleScene::BattleScene()
	: Scene(Scenes::Battle), pick(nullptr), battleCharacterCount(10),
	curChapIdx(0), curStageIdx(0), playingBattle(false)
{
	CLOG::Print3String("battle create");

	gameScreenTopLimit = GAME_SCREEN_HEIGHT * 0.5f - TILE_SIZE_HALF;
	gameScreenBottomLimit = GAME_SCREEN_HEIGHT * 1.1f;

	ui = new BattleSceneUI(this);
}

BattleScene::~BattleScene()
{
}

void BattleScene::Init()
{
	CLOG::Print3String("battle Init");

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

	prepareGrid.assign(PREPARE_SIZE, nullptr);
	battleGrid.assign(BATTLE_GRID_ROW * GAME_TILE_WIDTH, nullptr);
	mainGrid.assign(GAME_TILE_HEIGHT * GAME_TILE_WIDTH, nullptr);
	ui->Reset();

	curChapIdx = 0;
	curStageIdx = 0;
	SetCurrentStage(curChapIdx, curStageIdx);
}

void BattleScene::Exit()
{
	CLOG::Print3String("battle exit");

	for (auto& character : prepareGrid)
	{
		delete character;
	}
	prepareGrid.clear();

	for (auto& character : battleGrid)
	{
		delete character;
	}
	battleGrid.clear();
}

void BattleScene::Update(float dt)
{
	Scene::Update(dt);

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
			ui->b_battleGridRect = !ui->b_battleGridRect;

			for (auto& tiles : ui->battleGridRect)
			{
				for (auto& tile : tiles)
					tile->SetActive(ui->b_battleGridRect);
			}
		}
		if (InputMgr::GetKeyDown(Keyboard::Key::F4))
		{
			CLOG::Print3String("battle end");
			playingBattle = false;
		}

		if (InputMgr::GetKeyDown(Keyboard::Key::F5))
		{
			CLOG::Print3String("prev stage test");
			if (curStageIdx > 0)
				curStageIdx--;
			SetCurrentStage(curChapIdx, curStageIdx);
		}
		if (InputMgr::GetKeyDown(Keyboard::Key::F6))
		{
			CLOG::Print3String("next stage test");
			if (curStageIdx < STAGE_MAX_COUNT - 1)
				curStageIdx++;
			SetCurrentStage(curChapIdx, curStageIdx);
		}
		if (InputMgr::GetKeyDown(Keyboard::Key::F7))
		{
			CLOG::Print3String("devmode switch");
			FRAMEWORK->devMode = !FRAMEWORK->devMode;
		}
		if (InputMgr::GetKeyDown(Keyboard::Key::F8))
		{
			int count = 0;
			cout << "-------------------" << endl;
			CLOG::Print3String("main grid state");
			count = 0;
			for (auto& character : mainGrid)
			{
				if ((count / GAME_TILE_WIDTH) == 10)
					break;

				if (character == nullptr)
					cout << "..";
				else
				{
					if (character->GetName().compare("Obstacle"))
						cout << character->GetName()[0] + to_string(character->GetStarNumber());
					else
						cout << "Ob";
				}
				
				cout << ' ';
				count++;
				if ((count % GAME_TILE_WIDTH) == 0)
					cout << endl;
			}
			cout << endl;

			CLOG::Print3String("battle grid state");
			count = 0;
			for (auto& character : battleGrid)
			{
				if (character == nullptr)
					cout << "..";
				else
					cout << character->GetName()[0] + to_string(character->GetStarNumber());
				cout << ' ';
				count++;
				if ((count % GAME_TILE_WIDTH) == 0)
					cout << endl;
			}
			cout << endl;

			CLOG::Print3String("prepare grid state");
			count = 0;
			for (auto& character : prepareGrid)
			{
				if (character == nullptr)
					cout << "..";
				else
					cout << character->GetName()[0] + to_string(character->GetStarNumber());
				cout << ' ';
				count++;
				if ((count % GAME_TILE_WIDTH) == 0)
					cout << endl;
			}
			cout << "-------------------" << endl;
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
				// battle start
				if (!button->GetName().compare("begin"))
				{
					CLOG::Print3String("stage start");
					b_centerPos = true;
					ZoomIn();
					/*for (auto& character : prepareGrid)
					{
						if (character != nullptr)
							character->SetDrawInBattle(true);
					}*/

					int monsterGridCoordR = 70;
					int monsterGridCoordC = 0;
					int curBattleCharacterCount = 0;
					for (auto& character : battleGrid)
					{
						if (character != nullptr)
							curBattleCharacterCount++;
						mainGrid[monsterGridCoordC + monsterGridCoordR] = character;
						monsterGridCoordC++;
					}
					if (curBattleCharacterCount != battleCharacterCount)
						CLOG::Print3String("need more battle character");

					CLOG::Print3String("main grid full state");
					int count = 0;
					for (auto& character : mainGrid)
					{
						if (character == nullptr)
							cout << "..";
						else
						{
							if (character->GetName().compare("Obstacle"))
								cout << character->GetName()[0] + to_string(character->GetStarNumber());
							else
								cout << "Ob";
						}

						cout << ' ';
						count++;
						if ((count % GAME_TILE_WIDTH) == 0)
							cout << endl;
					}

					playingBattle = true;
					break;
				}
				// summon character
				if (!button->GetName().compare("summon"))
				{
					int idx = GetZeroElem(prepareGrid);
					if (idx == -1)
					{
						CLOG::Print3String("can not summon");
						return;
					}
					Character* newPick = GAME_MGR->SpawnPlayer(true, true);
					newPick->SetPos(ui->GetPrepareGridPos(idx));
					newPick->Init();
					newPick->SetDrawingOnBattle(true);
					prepareGrid[idx] = newPick;
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
			continue;

		character->Update(dt);
		if (character->CollideTest(ScreenToWorldPos(InputMgr::GetMousePosI())))
		{
			if (InputMgr::GetMouseDown(Mouse::Left))
			{
				if (pick == nullptr)
				{
					PickUpCharacter(character);
					break;
				}
			}
			else if (InputMgr::GetMouseDown(Mouse::Right))
			{
				if (pick == nullptr)
				{
					Character* temp = character;
					character = nullptr;
					delete temp;
					break;
				}
			}
		}
	}

	if (!playingBattle)
	{
		for (auto& character : battleGrid)
		{
			if (character == nullptr)
				continue;

			character->Update(dt);
			if (character->CollideTest(ScreenToWorldPos(InputMgr::GetMousePosI())))
			{
				if (InputMgr::GetMouseDown(Mouse::Left))
				{
					if (pick == nullptr)
					{
						PickUpCharacter(character);
						break;
					}
				}
				else if (InputMgr::GetMouseDown(Mouse::Right))
				{
					if (pick == nullptr)
					{
						Character* temp = character;
						character = nullptr;
						delete temp;
						break;
					}
				}
			}
		}
	}

	for (auto& character : mainGrid)
	{
		if (character == nullptr)
			continue;
		if (!character->GetType().compare("Obstacle"))
			continue;

		character->Update(dt);
		if (character->CollideTest(ScreenToWorldPos(InputMgr::GetMousePosI())))
		{
			if (InputMgr::GetMouseDown(Mouse::Left))
			{
				/*if (pick == nullptr)
				{
					PickUpCharacter(character);
					break;
				}*/
				CLOG::Print3String(character->GetName());
			}
		}
	}

	// mouse drag control
	if (pick != nullptr && InputMgr::GetMouse(Mouse::Left))
		pick->SetPos(ScreenToWorldPos(InputMgr::GetMousePosI()) + Vector2f(0, TILE_SIZE_HALF));

	if (pick != nullptr && InputMgr::GetMouseUp(Mouse::Left))
	{
		Vector2i destCoord = GAME_MGR->PosToIdx(pick->GetPos() + Vector2f(TILE_SIZE_HALF, TILE_SIZE_HALF));
		bool dest = InBattleGrid(destCoord);

		if (!InPrepareGrid(destCoord) && !dest)
		{
			CLOG::PrintVectorState(destCoord, "can not move");
			pick->SetPos(beforeDragPos);
			return;
		}
		Vector2i beforeCoord = GAME_MGR->PosToIdx(beforeDragPos);
		bool before = InBattleGrid(beforeCoord);
		if (before && dest)
			PutDownCharacter(&battleGrid, &battleGrid, beforeCoord, destCoord);
		else if (before)
			PutDownCharacter(&battleGrid, &prepareGrid, beforeCoord, destCoord);
		else if (dest)
			PutDownCharacter(&prepareGrid, &battleGrid, beforeCoord, destCoord);
		else
			PutDownCharacter(&prepareGrid, &prepareGrid, beforeCoord, destCoord);
	}
	// Game Input end
}

void BattleScene::Draw(RenderWindow& window)
{
	Scene::Draw(window);

	for (auto& row : *curStage)
	{
		for (auto& tile : row)
		{
			tile->Draw(window);
		}
	}

	for (auto& character : prepareGrid)
	{
		if (character != nullptr)
			character->Draw(window);
	}

	if (!playingBattle)
	{
		for (auto& character : battleGrid)
		{
			if (character != nullptr)
				character->Draw(window);
		}
	}

	for (auto& character : mainGrid)
	{
		if (character != nullptr)
			character->Draw(window);
	}
}

VertexArrayObj* BattleScene::GetBackground()
{
	return background;
}

void BattleScene::MoveTile(Character* character, Dir currMoveDir)
{
	//Vector2i curPos = GAME_MGR->PosToIdx(character->GetPos());
	//TilePlay* curTile = testTile[curPos.y][curPos.x];

	//nowTile = character->GetPos();
	//switch (currMoveDir)
	//{
	//case Dir::Up:
	//	nowTile.y -= TILE_SIZE;
	//	break;
	//case Dir::Down:
	//	nowTile.y += TILE_SIZE;
	//	break;
	//case Dir::Left:
	//	nowTile.x -= TILE_SIZE;
	//	break;
	//case Dir::Right:
	//	nowTile.x += TILE_SIZE;
	//	break;
	//}
	//character->SetDestination(nowTile);
	//Vector2i idx = GAME_MGR->PosToIdx(nowTile);
	////CLOG::PrintVectorState(nowTile, "now");
	////CLOG::PrintVectorState(idx, "idx");
	//TilePlay* nextTile = testTile[idx.y][idx.x];
	//if (nextTile->GetOnTileObj() != nullptr)
	//	return;
	//curTile->SetOnTileObj(nullptr);
	//nextTile->SetOnTileObj(character);
	//character->SetMove(true);
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

void BattleScene::PickUpCharacter(Character* character)
{
	beforeDragPos = character->GetPos();
	pick = character;
	pick->SetHitBoxActive(false);
}

void BattleScene::PutDownCharacter(vector<Character*>* start, vector<Character*>* dest, Vector2i startCoord, Vector2i destCoord)
{
	int startIdx = GetIdxFromCoord(startCoord);
	int destIdx = GetIdxFromCoord(destCoord);

	if ((startCoord != destCoord))
	{
		Character* destCharacter = (*dest)[destIdx];
		if (destCharacter != nullptr)
		{
			if (!destCharacter->GetName().compare(pick->GetName()) &&
				destCharacter->GetStarNumber() == pick->GetStarNumber())
			{
				CLOG::Print3String("combinate");
				(*dest)[destIdx] = nullptr;
				destCharacter->Release();
				delete destCharacter;
				pick->UpgradeStar();
			}
			else
			{
				CLOG::Print3String("swap");
				destCharacter->SetPos(beforeDragPos);
			}
		}
		else
		{
			CLOG::Print3String("move to empty");

			// add to new character from prepare
			if (dest == &battleGrid && start == &prepareGrid)
			{
				int count = 0;
				for (auto& character : battleGrid)
				{
					if (character == nullptr)
						continue;
					else
						count++;
				}

				if (count >= battleCharacterCount)
				{
					CLOG::Print3String("can not move more character");
					pick->SetPos(beforeDragPos);
					pick->SetHitBoxActive(true);
					pick = nullptr;
					return;
				}
			}
		}
		// swap
		Character* temp = (*dest)[destIdx];
		(*dest)[destIdx] = pick;
		(*start)[startIdx] = temp;
	}

	pick->SetPos(GAME_MGR->IdxToPos(destCoord));
	pick->SetHitBoxActive(true);
	pick = nullptr;
	return ;
}

int BattleScene::GetIdxFromCoord(Vector2i coord)
{
	return coord.x + (coord.y < 14 ? coord.y - 10 : coord.y - 16) * GAME_TILE_WIDTH; // battle y 10~13 prepare y 16~17
}

void BattleScene::SetCurrentStage(int chap, int stage)
{
	mainGrid.assign(GAME_TILE_HEIGHT * GAME_TILE_WIDTH, nullptr);

	curStage = GAME_MGR->GetStage(chap, stage);

	int row = GAME_TILE_HEIGHT - BATTLE_GRID_ROW; // player zone X
	int col = GAME_TILE_WIDTH;

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			Tile* tile = (*curStage)[i][j];
			TileData td = tile->GetTileData();
			int type = td.TileTypes;

			int curIdx = j + i * col;
			switch (type)
			{
			case (int) TileTypes::Obstacle:
				mainGrid[curIdx] = new Obstacle(tile->GetObstaclePath());
				mainGrid[curIdx]->SetPos(tile->GetPos());
				break;
			case (int) TileTypes::Monster:
				mainGrid[curIdx] = GAME_MGR->SpawnMonster( tile->GetMonsterName(), td.grade);
				mainGrid[curIdx]->SetPos(tile->GetPos());
				mainGrid[curIdx]->Init();
				mainGrid[curIdx]->SetDrawingOnBattle(true);
				break;
			default:
				break;
			}
		}
	}
	cout << "current chapter, stage (" << curChapIdx << ", " << curStageIdx << ")" << endl;
}

Character* BattleScene::GetMainGridCharacter(int r, int c)
{
	int idx = r * GAME_TILE_WIDTH + c;
	return mainGrid[idx];
}

bool InPrepareGrid(Vector2i pos)
{
	return (pos.x >= 0 && pos.x < 7) && (pos.y >= 16 && pos.y < 18); // x(0, 6) y(16, 17)
}

bool InBattleGrid(Vector2i pos)
{
	return (pos.x >= 0 && pos.x < 7) && (pos.y >= 10 && pos.y < 14); // x(0, 6) y(10, 13)
}

int GetZeroElem(vector<Character*>& vec)
{
	for (int idx = 0; idx < PREPARE_SIZE; idx++)
	{
		if (vec[idx] == nullptr)
			return idx;
	}
	return -1; // fail
}