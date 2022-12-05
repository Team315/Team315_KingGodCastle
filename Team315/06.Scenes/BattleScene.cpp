#include "BattleScene.h"
#include "BattleSceneUI.h"
#include "BattlePanel.h"
#include "Button.h"
#include "GameObjHeaders.h"
#include "Constant.h"
#include "GameManager.h"
#include "Map/Tile.h"
#include "Map/FloodFill.h"
#include "RectangleObj.h"

using namespace std;

BattleScene::BattleScene()
	: Scene(Scenes::Battle), pick(nullptr), battleCharacterCount(10),
	curChapIdx(0), curStageIdx(0), playingBattle(false), gameEndTimer(0.f)
{
	CLOG::Print3String("battle create");

	gameScreenTopLimit = GAME_SCREEN_HEIGHT * 0.5f - TILE_SIZE_HALF;
	gameScreenBottomLimit = GAME_SCREEN_HEIGHT * 1.1f;
	prepareGridRect.resize(PREPARE_SIZE);
	float outlineThickness = -2.f;
	float posX = TILE_SIZE * 2.f;
	float posY = GAME_SCREEN_HEIGHT + TILE_SIZE * 2.f;
	int count = 0;
	for (auto& cell : prepareGridRect)
	{
		cell = new RectangleObj(TILE_SIZE - 1, TILE_SIZE - 1);
		cell->SetOutline(Color(255, 255, 255, 100), outlineThickness);
		cell->SetFillColor(Color(0, 0, 0, 0));
		cell->SetPos(Vector2f(posX, posY));
		cell->SetOrigin(Origins::BC);
		objList.push_back(cell);
		count++;
		posX += TILE_SIZE;
		if (count == prepareGridRect.size() * 0.5f)
		{
			posX = TILE_SIZE * 2.f;
			posY += TILE_SIZE;
		}
	}

	castleBackground.setTexture(*RESOURCE_MGR->GetTexture("graphics/battleScene/castleBackground.png"));
	castleBackground.setPosition(0, GAME_SCREEN_HEIGHT - TILE_SIZE);

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

	playingBattle = false;
	GAME_MGR->Init();
	ui->Reset();

	curChapIdx = 0;
	curStageIdx = 0;
	SetCurrentStage(curChapIdx, curStageIdx);

	b_centerPos = false;
	ZoomOut();
	GAME_MGR->damageUI.Reset();


	SOUND_MGR->Play("sounds/Battle.wav", 20.f, true);
	GAME_MGR->damageUI.Reset();
}

void BattleScene::Exit()
{
	CLOG::Print3String("battle exit");
	SOUND_MGR->StopAll();

	for (auto& gameObj : prepareGrid)
	{
		delete gameObj;
	}
	prepareGrid.clear();

	for (auto& gameObj : battleGrid)
	{
		delete gameObj;
	}
	battleGrid.clear();
	GAME_MGR->damageUI.Reset();
}

void BattleScene::Update(float dt)
{
	vector<GameObj*>& mgref = GAME_MGR->GetMainGridRef();
	GAME_MGR->damageUI.Update(dt);
	GAME_MGR->rangePreview.Update(dt);
	if (!GAME_MGR->waitQueue.empty())
	{
		int idx = GetZeroElem(prepareGrid);
		if (idx != -1)
		{
			Item* item = GAME_MGR->waitQueue.front();
			item->SetPos(prepareGridRect[idx]->GetPos());
			item->Init();
			prepareGrid[idx] = item;

			GAME_MGR->waitQueue.pop();
		}
	}

	Scene::Update(dt);

	// Dev Input start
	{
		if (InputMgr::GetKeyDown(Keyboard::Key::Escape))
		{
			CLOG::Print3String("setting window");
			SOUND_MGR->StopAll();
			return;
		}
		if (InputMgr::GetKeyDown(Keyboard::Key::Num1))
		{
			TranslateCoinState(100.f);
			SOUND_MGR->Play("sounds/Battel_getmoney.wav", 20.f, false);
		}

		if (InputMgr::GetKeyDown(Keyboard::Key::F4))
		{
			CLOG::Print3String("battle end");
			playingBattle = false;

			int len = battleGrid.size();
			for (int idx = 0; idx < len; idx++)
			{
				if (battleGrid[idx] == nullptr)
					continue;

				battleGrid[idx]->Reset();
				battleGrid[idx]->SetPos(GAME_MGR->IdxToPos(GetCoordFromIdx(idx, true)));
			}

			b_centerPos = false;
			ZoomOut();

			if (curStageIdx < STAGE_MAX_COUNT - 1)
				curStageIdx++;
			SetCurrentStage(curChapIdx, curStageIdx);
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
			else
			{
				ui->GetPanel()->ChangeTitleTextString(++curChapIdx);
				curStageIdx = 0;
			}
			SetCurrentStage(curChapIdx, curStageIdx);
		}
		if (InputMgr::GetKeyDown(Keyboard::Key::Num5))
		{
			CLOG::Print3String("prev chapter test");
			if (curChapIdx > 0)
				curChapIdx--;
			ui->GetPanel()->ChangeTitleTextString(curChapIdx);
			SetCurrentStage(curChapIdx, curStageIdx);
		}
		if (InputMgr::GetKeyDown(Keyboard::Key::Num6))
		{
			CLOG::Print3String("next chapter test");
			if (curChapIdx < CHAPTER_MAX_COUNT - 1)
				curChapIdx++;
			ui->GetPanel()->ChangeTitleTextString(curChapIdx);
			SetCurrentStage(curChapIdx, curStageIdx);
		}

		if (InputMgr::GetKeyDown(Keyboard::Key::F7))
		{
			CLOG::Print3String("devmode switch");
			FRAMEWORK->devMode = !FRAMEWORK->devMode;
		}
		/*if (InputMgr::GetKeyDown(Keyboard::Key::F8))
		{
			int count = 0;
			CLOG::Print3String("main grid state");
			for (auto& gameObj : mgref)
			{
				string str = "";
				if (gameObj == nullptr)
					str += ".. ";
				else
				{
					if (gameObj->GetName().compare("Obstacle"))
						str += (gameObj->GetName().substr(0, 2) + " ");
					else
						str += "Ob ";
				}
				count++;
				if ((count % GAME_TILE_WIDTH) == 0)
					str += "\n";
				cout << str;
			}
			cout << endl;
		}*/

		//if (InputMgr::GetKeyDown(Keyboard::Key::F9))
		//{
		//	int count = 0;
		//	CLOG::Print3String("battle grid state");
		//	for (auto& gameObj : battleGrid)
		//	{
		//		string str = "";
		//		if (gameObj == nullptr)
		//			str += ".. ";
		//		else
		//		{
		//			str += (gameObj->GetName().substr(0, 2) + " ");
		//		}
		//		count++;
		//		if ((count % GAME_TILE_WIDTH) == 0)
		//			str += "\n";
		//		cout << str;
		//	}
		//	cout << endl;

		//	CLOG::Print3String("prepare grid state");
		//	for (auto& gameObj : prepareGrid)
		//	{
		//		string str = "";
		//		if (gameObj == nullptr)
		//			str += ".. ";
		//		else
		//		{
		//			str += (gameObj->GetName().substr(0, 2) + " ");
		//		}
		//		count++;
		//		if ((count % GAME_TILE_WIDTH) == 0)
		//			str += "\n";
		//		cout << str;
		//	}
		//	cout << endl;
		//}
	}
	// Dev Input end

	// Game Input start

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

	if (InputMgr::GetMouseDown(Mouse::Left))
	{
		ui->SetStatPopup(false, currentView.getCenter());
		ui->SetItemPopup(false, currentView.getCenter());

		for (auto& gameObj : battleGrid)
		{
			if (gameObj != nullptr && IsCharacter(gameObj))
			{
				dynamic_cast<Character*>(gameObj)->OnOffAttackAreas(false);
				pickAttackRangeRect = nullptr;
			}
		}
	}

	vector<Button*>& buttons = ui->GetPanel()->GetButtons();
	for (auto button : buttons)
	{
		if (button->CollideTest(ScreenToWorldPos(InputMgr::GetMousePosI())))
		{
			if (InputMgr::GetMouseDown(Mouse::Left))
			{
				// battle start
				if (!button->GetName().compare("begin") && !playingBattle)
				{
					int monsterGridCoordC = 0;
					int curBattleCharacterCount = 0;

					for (auto& character : battleGrid)
					{
						if (character != nullptr)
							curBattleCharacterCount++;

						mgref[monsterGridCoordC + 70] = character;
						monsterGridCoordC++;
					}
					if (curBattleCharacterCount != battleCharacterCount)
					{
						CLOG::Print3String("need more battle character");
						if (curBattleCharacterCount == 0)
							break;
					}

					for (auto& gameObj : mgref)
					{
						if (gameObj != nullptr && IsCharacter(gameObj))
						{
							dynamic_cast<Character*>(gameObj)->SetIsBattle(true);
						}
					}

					b_centerPos = true;
					ZoomIn();

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

					if (GAME_MGR->GetCurrentCoin() >= GAME_MGR->characterCost)
					{
						TranslateCoinState(-GAME_MGR->characterCost);
					}
					else
					{
						cout << "not enough coin" << endl;
						break;
					}
					Character* newPick = GAME_MGR->SpawnPlayer(true, true);
					newPick->SetPos(prepareGridRect[idx]->GetPos());
					newPick->Init();
					prepareGrid[idx] = newPick;
					break;
				}
				// Item
				if (!button->GetName().compare("item"))
				{
					int idx = GetZeroElem(prepareGrid);
					if (idx == -1)
					{
						CLOG::Print3String("can not create item");
						return;
					}

					if (GAME_MGR->GetCurrentCoin() >= GAME_MGR->itemCost)
					{
						TranslateCoinState(-GAME_MGR->itemCost);

						Item* item = GAME_MGR->SpawnItem();
						item->SetPos(prepareGridRect[idx]->GetPos());
						item->Init();
						prepareGrid[idx] = item;
					}
					else
					{
						cout << "not enough coin" << endl;
						break;
					}
					break;
				}
			}
		}
	}

	// prepare grid & battle grid - gameObj pick up
	for (auto& gameObj : prepareGrid)
	{
		if (gameObj == nullptr)
			continue;

		gameObj->Update(dt);

		if (gameObj->CollideTest(ScreenToWorldPos(InputMgr::GetMousePosI())))
		{
			if (InputMgr::GetMouseDown(Mouse::Left))
			{
				if (pick == nullptr)
				{
					PickUpGameObj(gameObj);
					break;
				}
			}
			else if (InputMgr::GetMouseDown(Mouse::Right))
			{
				if (pick == nullptr)
				{
					SOUND_MGR->Play("sounds/Battel_getmoney.wav", 20.f, false);
					//SOUND_MGR->Release();
					GameObj*& temp = gameObj;
					if (IsCharacter(temp))
					{
						Character* tempCharacter = dynamic_cast<Character*>(temp);
						vector<Item*> tempItems = tempCharacter->GetItems();
						for (auto item : tempItems)
							GAME_MGR->waitQueue.push(item);

						float delta =
							pow(2, tempCharacter->GetStarNumber() - 1) *
							GAME_MGR->characterCost * 2 / 3;
						cout << "sell character, +" << to_string((int)delta) << endl;
						TranslateCoinState(delta);
						gameObj = nullptr;
						delete temp;
						break;
					}
					else
					{
						float delta =
							pow(2, dynamic_cast<Item*>(temp)->GetGrade()) *
							GAME_MGR->itemCost * 3 / 5;
						cout << "sell item, +" << to_string((int)delta) << endl;
						TranslateCoinState(delta);
						gameObj = nullptr;
						delete temp;
						break;
					}
				}
			}
		}
	}

	if (!playingBattle)
	{
		for (auto& gameObj : battleGrid)
		{
			if (gameObj == nullptr)
				continue;

			if (IsCharacter(gameObj))
				gameObj->Update(dt);

			if (gameObj->CollideTest(ScreenToWorldPos(InputMgr::GetMousePosI())))
			{
				if (InputMgr::GetMouseDown(Mouse::Left))
				{
					if (pick == nullptr)
					{
						PickUpGameObj(gameObj);
						if (InBattleGrid(GAME_MGR->PosToIdx(pick->GetPos())))
						{
							dynamic_cast<Character*>(gameObj)->OnOffAttackAreas(true);
							pickAttackRangeRect = dynamic_cast<Character*>(gameObj)->GetAreas();
						}
						break;
					}
				}
				else if (InputMgr::GetMouseDown(Mouse::Right))
				{
					if (pick == nullptr)
					{
						SOUND_MGR->Play("sounds/Battel_getmoney.wav", 20.f, false);
						GameObj* temp = gameObj;
						if (IsCharacter(temp))
						{
							Character* tempCharacter = dynamic_cast<Character*>(temp);
							vector<Item*> tempItems = tempCharacter->GetItems();
							for (auto item : tempItems)
								GAME_MGR->waitQueue.push(item);

							float delta =
								pow(2, tempCharacter->GetStarNumber() - 1) *
								GAME_MGR->characterCost * 2 / 3;
							cout << "sell character, +" << to_string((int)delta) << endl;
							TranslateCoinState(delta);
							gameObj = nullptr;
							delete temp;
							break;
						}
					}
				}
			}
		}
	}

	// main grid update
	int playerCount = 0;
	int aiCount = 0;
	for (auto& gameObj : mgref)
	{
		if (gameObj != nullptr && !gameObj->GetType().compare("Player"))
		{
			gameObj->Update(dt);
			playerCount++;
		}
		else if (gameObj != nullptr && !gameObj->GetType().compare("Monster"))
		{
			gameObj->Update(dt);
			aiCount++;
		}
	}

	// main grid stat pop up
	for (auto& gameObj : mgref)
	{
		if (gameObj != nullptr && IsCharacter(gameObj))
		{
			if (gameObj->CollideTest(ScreenToWorldPos(InputMgr::GetMousePosI())))
			{
				if (InputMgr::GetMouseDown(Mouse::Left))
				{
					ui->SetStatPopup(true, currentView.getCenter(), dynamic_cast<Character*>(gameObj),
						GAME_MGR->SnapToCoord(gameObj->GetPos()));

					dynamic_cast<Character*>(gameObj)->OnOffAttackAreas(true);
					pickAttackRangeRect = dynamic_cast<Character*>(gameObj)->GetAreas();
				}
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
		vector<GameObj*>& beforeContainer = InBattleGrid(beforeCoord) ? battleGrid : prepareGrid;
		vector<GameObj*>& destContainer = dest ? battleGrid : prepareGrid;

		if (IsCharacter(pick))
			PutDownCharacter(&beforeContainer, &destContainer, beforeCoord, destCoord);
		else // item
			PutDownItem(&beforeContainer, &destContainer, beforeCoord, destCoord);

		pick->SetHitBoxActive(true);
		if (InBattleGrid(GAME_MGR->PosToIdx(pick->GetPos())))
		{
			dynamic_cast<Character*>(pick)->OnOffAttackAreas(true);
			pickAttackRangeRect = dynamic_cast<Character*>(pick)->GetAreas();
		}
		pick = nullptr;
		return;
	}

	if (gameEndTimer > 0.f)
	{
		gameEndTimer -= dt;

		if (gameEndTimer < 0.f)
		{
			gameEndTimer = 0.f;
			ui->SetStageEndWindow(false);
			playingBattle = false;

			int len = battleGrid.size();
			for (int idx = 0; idx < len; idx++)
			{
				if (battleGrid[idx] == nullptr)
					continue;

				battleGrid[idx]->Reset();
				battleGrid[idx]->SetPos(GAME_MGR->IdxToPos(GetCoordFromIdx(idx, true)));
			}

			b_centerPos = false;
			ZoomOut();

			if (curStageIdx < STAGE_MAX_COUNT - 1)
				curStageIdx++;
			SetCurrentStage(curChapIdx, curStageIdx);
		}
		return;
	}

	if (playingBattle)
	{
		bool stageEnd = false;
		bool stageResult = false;

		if (playerCount == 0)
		{
			gameEndTimer = 2.0f;
			stageEnd = true;
			stageResult = false;
		}
		else if (aiCount == 0)
		{
			gameEndTimer = 2.0f;
			stageEnd = true;
			stageResult = true;
		}

		if (stageEnd)
		{
			ui->SetStageEndWindow(true, stageResult);
			TranslateCoinState(GAME_MGR->GetClearCoin());
		}
	}

	// Game Input end
}

void BattleScene::Draw(RenderWindow& window)
{
	for (int j = 0; j < BACKGROUND_WIDTH_COUNT * BACKGROUND_HEIGHT_COUNT; ++j)
	{
		int num = ((curChapIdx) * 150) + j;
		GAME_MGR->GetTileBackgroundList()[num]->Draw(window);
	}

	window.draw(castleBackground);
	Scene::Draw(window);

	// draw character on prepare area
	for (auto& gameObj : prepareGrid)
	{
		if (gameObj != nullptr)
		{
			gameObj->Draw(window);
		}
	}

	// draw tile
	for (auto& row : *curStage)
	{
		for (auto& tile : row)
		{
			tile->Draw(window);
		}
	}

	if (pickAttackRangeRect != nullptr)
	{
		for (auto& rect : *pickAttackRangeRect)
		{
			if (rect.GetActive())
				rect.Draw(window);
		}
	}

	auto& rangePreview = GAME_MGR->rangePreview.GetUseList();
	for (auto& preview : rangePreview)
	{
		preview->Draw(window);
	}

	// draw character on gmae screen area
	vector<GameObj*>& mgref = GAME_MGR->GetMainGridRef();
	for (auto& gameObj : mgref)
	{
		if (gameObj != nullptr)
		{
			gameObj->Draw(window);
		}
	}

	// draw character on battle area
	if (!playingBattle)
	{
		for (auto& gameObj : battleGrid)
		{
			if (gameObj != nullptr)
			{
				gameObj->Draw(window);
			}
		}
	}

	ui->Draw(window);
	auto& dmgUIlist = GAME_MGR->damageUI.GetUseList();
	for (auto& dmgUI : dmgUIlist)
	{
		dmgUI->Draw(window);
	}
}

void BattleScene::ZoomIn()
{
	currentView.setSize(GAME_SCREEN_ZOOM_WIDTH, GAME_SCREEN_ZOOM_HEIGHT);
}

void BattleScene::ZoomOut()
{
	currentView.setSize(GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT);
}

void BattleScene::PickUpGameObj(GameObj* gameObj)
{
	beforeDragPos = gameObj->GetPos();
	pick = gameObj;
	pick->SetHitBoxActive(false);
}

void BattleScene::TranslateCoinState(float delta)
{
	GAME_MGR->TranslateCoin(delta);
	ui->GetPanel()->SetCurrentCoin(GAME_MGR->GetCurrentCoin());
}

void BattleScene::PutDownCharacter(vector<GameObj*>* start, vector<GameObj*>* dest, Vector2i startCoord, Vector2i destCoord)
{
	int startIdx = GetIdxFromCoord(startCoord);
	int destIdx = GetIdxFromCoord(destCoord);
	bool canMove = true;

	if (startCoord == destCoord) // pop up stat window
	{
		ui->SetStatPopup(true, currentView.getCenter(), dynamic_cast<Character*>((*start)[startIdx]),
			GAME_MGR->SnapToCoord((*start)[startIdx]->GetPos() + Vector2f(TILE_SIZE_HALF, TILE_SIZE_HALF)));
	}
	else if ((*dest)[destIdx] == nullptr) // move to empty cell
	{
		// add to new character in battleGrid from prepare (prepare -> battleGrid)
		if (playingBattle && !(start == &prepareGrid && dest == &prepareGrid))
			canMove = false;
		else
		{
			if (start == &prepareGrid && dest == &battleGrid)
			{
				int count = 0;
				for (auto& character : battleGrid)
				{
					if (character == nullptr)
						continue;
					count++;
				}
				if (count >= battleCharacterCount)
					canMove = false;
			}
		}
	}
	else if ((*dest)[destIdx] != nullptr)
	{
		if (IsItem((*dest)[destIdx]))
		{
			if (start == &prepareGrid)
				(*dest)[destIdx]->SetPos(beforeDragPos);
			else
				canMove = false;
		}
		else
		{
			if (!playingBattle || (start == &prepareGrid && dest == &prepareGrid))
			{
				// combinate condition
				Character* destCharacter = dynamic_cast<Character*>((*dest)[destIdx]);

				if (!destCharacter->GetName().compare(pick->GetName()) &&
					destCharacter->GetStarNumber() == dynamic_cast<Character*>(pick)->GetStarNumber() &&
					destCharacter->GetStarNumber() != STAR_MAX)
				{
					(*dest)[destIdx] = nullptr;
					GameObj* temp = pick;
					vector<Item*>& pickCrtItems = dynamic_cast<Character*>(temp)->GetItems();
					
					for (auto& pItem : pickCrtItems)
					{
						if (!destCharacter->SetItem(pItem))
						{
							GAME_MGR->waitQueue.push(pItem);
						}
					}

					pick = destCharacter;
					temp->Release();
					delete temp;
					dynamic_cast<Character*>(pick)->UpgradeStar();
				}
				else (*dest)[destIdx]->SetPos(beforeDragPos);
			}
			else canMove = false;
		}
	}
	else canMove = false;

	// swap in vector container
	if (canMove)
	{
		GameObj* temp = (*dest)[destIdx];
		(*dest)[destIdx] = pick;
		(*start)[startIdx] = temp;
	}
	pick->SetPos(GAME_MGR->IdxToPos(canMove ? destCoord : startCoord));
}

void BattleScene::PutDownItem(vector<GameObj*>* start, vector<GameObj*>* dest, Vector2i startCoord, Vector2i destCoord)
{
	int startIdx = GetIdxFromCoord(startCoord);
	int destIdx = GetIdxFromCoord(destCoord);
	bool canMove = true;
	bool combine = false;

	if (startCoord == destCoord)
	{
		// pop up item stat window
		ui->SetItemPopup(true, currentView.getCenter(), dynamic_cast<Item*>((*dest)[destIdx]),
			GAME_MGR->SnapToCoord((*dest)[destIdx]->GetPos() + Vector2f(TILE_SIZE_HALF, TILE_SIZE_HALF)));
	}
	else if ((*dest)[destIdx] != nullptr)
	{
		if (IsItem((*dest)[destIdx])) // item swap or combinate
		{
			Item* destItem = dynamic_cast<Item*>((*dest)[destIdx]);
			Item* pickItem = dynamic_cast<Item*>(pick);
			if (!destItem->GetName().compare(pick->GetName()) &&
				destItem->GetGrade() == pickItem->GetGrade())
			{
				if (pickItem->Upgrade())
				{
					CLOG::Print3String("item combinate");
					(*dest)[destIdx] = nullptr;
					destItem->Release();
					delete destItem;
				}
				else canMove = false;
			}
			else destItem->SetPos(beforeDragPos);
		}
		else // give a item to the character
		{
			if (!playingBattle || dest == &prepareGrid)
			{
				Character* destCharacter = dynamic_cast<Character*>((*dest)[destIdx]);
				if (destCharacter->SetItem(dynamic_cast<Item*>(pick)))
				{
					(*start)[startIdx] = nullptr;
					combine = true;
					destCharacter->ArrangeItems();
				}
			}
			canMove = false;
		}
	}
	else if (dest == &prepareGrid) canMove = true;
	else canMove = false;

	// swap in vector container
	if (canMove)
	{
		GameObj* temp = (*dest)[destIdx];
		(*dest)[destIdx] = pick;
		(*start)[startIdx] = temp;
	}
	if (!combine)
		pick->SetPos(GAME_MGR->IdxToPos(canMove ? destCoord : startCoord));
}

void BattleScene::SetCurrentStage(int chap, int stage)
{
	curStage = GAME_MGR->GetStage(chap, stage);

	GAME_MGR->Reset();

	int row = GAME_TILE_HEIGHT - BATTLE_GRID_ROW; // player zone X
	int col = GAME_TILE_WIDTH;

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			Tile* tile = (*curStage)[i][j];
			int type = tile->GetTileData().TileTypes;

			int curIdx = j + i * col;

			vector<GameObj*>& mgref = GAME_MGR->GetMainGridRef();
			switch (type)
			{
			case (int)TileTypes::Obstacle:
				mgref[curIdx] = new Obstacle(tile->GetObstaclePath());
				mgref[curIdx]->SetPos(tile->GetPos());
				break;
			case (int)TileTypes::Monster:
				mgref[curIdx] = GAME_MGR->SpawnMonster(tile->GetMonsterName(), tile->GetTileData().grade);
				mgref[curIdx]->SetPos(tile->GetPos());
				mgref[curIdx]->Init();
				break;
			default:
				break;
			}
		}
	}

	ui->GetPanel()->SetStageNumber(curStageIdx + 1);
	cout << "current chapter, stage (" << curChapIdx << ", " << curStageIdx << ")" << endl;
}

int GetIdxFromCoord(Vector2i coord)
{
	return coord.x + (coord.y < 14 ? coord.y - 10 : coord.y - 16) * GAME_TILE_WIDTH; // battle y 10~13 prepare y 16~17
}

Vector2i GetCoordFromIdx(int idx, bool battle)
{
	Vector2i coord(idx % GAME_TILE_WIDTH, idx / GAME_TILE_WIDTH);
	if (battle)
		coord.y += 10;
	else
		coord.y += 16;
	return coord;
}

bool IsItem(GameObj* gameObj)
{
	return !gameObj->GetType().compare("Item");
}

bool IsCharacter(GameObj* gameObj)
{
	return !gameObj->GetType().compare("Player") || !gameObj->GetType().compare("Monster");
}

bool InPrepareGrid(Vector2i pos)
{
	return (pos.x >= 0 && pos.x < 7) && (pos.y >= 16 && pos.y < 18); // x(0, 6) y(16, 17)
}

bool InBattleGrid(Vector2i pos)
{
	return (pos.x >= 0 && pos.x < 7) && (pos.y >= 10 && pos.y < 14); // x(0, 6) y(10, 13)
}

int GetZeroElem(vector<GameObj*>& vec)
{
	for (int idx = 0; idx < PREPARE_SIZE; idx++)
	{
		if (vec[idx] == nullptr)
			return idx;
	}
	return -1; // fail
}