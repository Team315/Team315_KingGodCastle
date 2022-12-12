#include "BattleScene.h"
#include "BackrectText.h"
#include "BattleSceneUI.h"
#include "BattlePanel.h"
#include "Button.h"
#include "Constant.h"
#include "DamageTrackerUI.h"
#include "GameManager.h"
#include "GameObjHeaders.h"
#include "Map/Tile.h"
#include "Map/FloodFill.h"
#include "RectangleObj.h"

BattleScene::BattleScene()
	: Scene(Scenes::Battle), pick(nullptr), gameEndTimer(0.f), gameOverTimer(0.f),
	remainLife(3), isGameOver(false), stageEnd(false), stageResult(false)
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

	flags.resize(3);
	Vector2f flagPos(GAME_SCREEN_WIDTH * 0.5f - 70.f, GAME_SCREEN_HEIGHT + TILE_SIZE_HALF);
	for (auto& flag : flags)
	{
		flag = new SpriteObj();
		flag->SetTexture(*RESOURCE_MGR->GetTexture("graphics/battleScene/Flag.png"));
		flag->SetPos(flagPos);
		flag->SetScale(0.7f, 0.7f);
		flag->SetOrigin(Origins::BC);
		flagPos.x += 70.f;
		objList.push_back(flag);
	}
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

	GAME_MGR->GMReset();
	ui->Reset();

	GAME_MGR->curChapIdx = 0;
	GAME_MGR->curStageIdx = 0;
	SetCurrentStage(GAME_MGR->curChapIdx, GAME_MGR->curStageIdx);

	b_centerPos = false;
	ZoomOut();
	GAME_MGR->damageUI.Reset();

	SOUND_MGR->Play("sounds/Battle.wav", 20.f, true);
	stageResult = false;
	stageEnd = false;
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
	if (isGameOver)
	{
		gameOverTimer -= dt;
		if (gameOverTimer < 0.f)
		{
			SCENE_MGR->ChangeScene(Scenes::Title);
		}
		return;
	}

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
			item->SetActive(true);
			prepareGrid[idx] = item;

			GAME_MGR->waitQueue.pop();
		}
	}

	vector<Item*>& drops = GAME_MGR->drops;
	for (auto it = drops.begin(); it != drops.end();)
	{
		(*it)->Update(dt);
		if ((*it)->CollideTest(ScreenToWorldPos(InputMgr::GetMousePosI())))
		{
			if (InputMgr::GetMouseDown(Mouse::Left))
			{
				int idx = GetZeroElem(prepareGrid);
				if (idx != -1)
				{
					(*it)->SetDestination(prepareGridRect[idx]->GetPos());
					prepareGrid[idx] = (*it);
					it = drops.erase(it);
				}
				else it++;
			}
			else it++;
		}
		else it++;
	}

	Scene::Update(dt);

	// Dev Input start
	{
		if (InputMgr::GetKeyDown(Keyboard::Key::Escape))
		{
			CLOG::Print3String("setting window");
			SOUND_MGR->StopAll();
			SCENE_MGR->ChangeScene(Scenes::Title);
			return;
		}

		if (InputMgr::GetKeyDown(Keyboard::Key::Num1))
		{
			TranslateCoinState(100.f);
			SOUND_MGR->Play("sounds/Battel_getmoney.wav", 20.f, false);
		}

		if (InputMgr::GetKeyDown(Keyboard::Key::Num2))
		{
			cout << "create New Item" << endl;
			GAME_MGR->waitQueue.push(GAME_MGR->SpawnItem());
		}

		if (InputMgr::GetKeyDown(Keyboard::Key::Num3))
		{
			cout << "create New Item" << endl;
			GAME_MGR->waitQueue.push(GAME_MGR->SpawnItem(1));
		}

		if (InputMgr::GetKeyDown(Keyboard::Key::Num4))
		{
			cout << "create New Item" << endl;
			GAME_MGR->waitQueue.push(GAME_MGR->SpawnItem(2));
		}

		if (InputMgr::GetKeyDown(Keyboard::Key::F3))
		{
			LoseFlag();
		}

		if (InputMgr::GetKeyDown(Keyboard::Key::F4))
		{
			CLOG::Print3String("battle end");
			GAME_MGR->SetPlayingBattle(false);

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

			if (GAME_MGR->curStageIdx < STAGE_MAX_COUNT - 1)
				GAME_MGR->curStageIdx++;
			SetCurrentStage(GAME_MGR->curChapIdx, GAME_MGR->curStageIdx);
		}

		if (InputMgr::GetKeyDown(Keyboard::Key::F5))
		{
			CLOG::Print3String("prev stage test");
			if (GAME_MGR->curStageIdx > 0)
				GAME_MGR->curStageIdx--;
			else
				GAME_MGR->curStageIdx = STAGE_MAX_COUNT - 1;
			SetCurrentStage(GAME_MGR->curChapIdx, GAME_MGR->curStageIdx);
		}
		if (InputMgr::GetKeyDown(Keyboard::Key::F6))
		{
			CLOG::Print3String("next stage test");
			if (GAME_MGR->curStageIdx < STAGE_MAX_COUNT - 1)
				GAME_MGR->curStageIdx++;
			else
			{
				if (GAME_MGR->curChapIdx != 2)
					ui->GetPanel()->ChangeTitleTextString(++GAME_MGR->curChapIdx);
				GAME_MGR->curStageIdx = 0;
			}
			SetCurrentStage(GAME_MGR->curChapIdx, GAME_MGR->curStageIdx);
		}

		if (InputMgr::GetKeyDown(Keyboard::Key::Num5))
		{
			CLOG::Print3String("prev chapter test");
			if (GAME_MGR->curChapIdx > 0)
				GAME_MGR->curChapIdx--;
			ui->GetPanel()->ChangeTitleTextString(GAME_MGR->curChapIdx);
			SetCurrentStage(GAME_MGR->curChapIdx, GAME_MGR->curStageIdx);
		}

		if (InputMgr::GetKeyDown(Keyboard::Key::Num6))
		{
			CLOG::Print3String("next chapter test");
			if (GAME_MGR->curChapIdx < CHAPTER_MAX_COUNT - 1)
				GAME_MGR->curChapIdx++;
			ui->GetPanel()->ChangeTitleTextString(GAME_MGR->curChapIdx);
			SetCurrentStage(GAME_MGR->curChapIdx, GAME_MGR->curStageIdx);
		}

		if (InputMgr::GetKeyDown(Keyboard::Key::F7))
		{
			CLOG::Print3String("devmode switch");
			FRAMEWORK->devMode = !FRAMEWORK->devMode;
		}

		if (InputMgr::GetKeyDown(Keyboard::Key::F8))
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
		}

		if (InputMgr::GetKeyDown(Keyboard::Key::F9))
		{
			int count = 0;
			CLOG::Print3String("battle grid state");
			for (auto& gameObj : battleGrid)
			{
				string str = "";
				if (gameObj == nullptr)
					str += ".. ";
				else
				{
					str += (gameObj->GetName().substr(0, 2) + " ");
				}
				count++;
				if ((count % GAME_TILE_WIDTH) == 0)
					str += "\n";
				cout << str;
			}
			cout << endl;
			CLOG::Print3String("prepare grid state");
			for (auto& gameObj : prepareGrid)
			{
				string str = "";
				if (gameObj == nullptr)
					str += ".. ";
				else
				{
					str += (gameObj->GetName().substr(0, 2) + " ");
				}
				count++;
				if ((count % GAME_TILE_WIDTH) == 0)
					str += "\n";
				cout << str;
			}
			cout << endl;
		}

		if (InputMgr::GetKeyDown(Keyboard::Key::Y))
		{
			for (auto& gameObj : mgref)
			{
				if (gameObj == nullptr)
					continue;

				if (!gameObj->GetType().compare("Monster"))
					dynamic_cast<Character*>(gameObj)->UpgradeStar(false, false);
			}
		}

		if (InputMgr::GetKeyDown(Keyboard::Key::U))
		{
			for (auto& gameObj : mgref)
			{
				if (gameObj == nullptr)
					continue;

				if (!gameObj->GetType().compare("Monster"))
					dynamic_cast<Character*>(gameObj)->SetItem(new Armor());
			}
		}

		if (InputMgr::GetKeyDown(Keyboard::Key::I))
		{
			for (auto& gameObj : mgref)
			{
				if (gameObj == nullptr)
					continue;

				if (!gameObj->GetType().compare("Monster"))
					dynamic_cast<Character*>(gameObj)->SetItem(new Sword());
			}
		}

		if (InputMgr::GetKeyDown(Keyboard::Key::O))
		{
			for (auto& gameObj : mgref)
			{
				if (gameObj == nullptr)
					continue;

				if (!gameObj->GetType().compare("Monster"))
					dynamic_cast<Character*>(gameObj)->SetItem(new Staff());
			}
		}

		if (InputMgr::GetKeyDown(Keyboard::Key::P))
		{
			for (auto& gameObj : mgref)
			{
				if (gameObj == nullptr)
					continue;

				if (!gameObj->GetType().compare("Monster"))
					dynamic_cast<Character*>(gameObj)->SetItem(new Bow());
			}
		}
	}
	// Dev Input end

	// Game Input start

	// wheel control
	vector<BackrectText*>& trackerButtons = ui->GetTracker()->GetButtons();
	for (auto& button : trackerButtons)
	{
		if (button->CollideTest(ScreenToWorldPos(InputMgr::GetMousePosI())))
		{
			if (InputMgr::GetMouseDown(Mouse::Left))
			{
				if (!button->GetName().compare("OnOff"))
				{
					ui->GetTracker()->ShowWindow();
					return;
				}
				else if (!button->GetName().compare("Given"))
				{
					ui->GetTracker()->ShowGiven();
					return;
				}
				else if (!button->GetName().compare("Taken"))
				{
					ui->GetTracker()->ShowTaken();
					return;
				}
			}
		}
	}

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
			screenCenterPos.y -= dt * (screenCenterPos.y - gameScreenTopLimit) * 5.f;
			gameView.setCenter(screenCenterPos);
		}
	}
	else
	{
		if (screenCenterPos.y <= gameScreenBottomLimit)
		{
			screenCenterPos.y += dt * (gameScreenBottomLimit - screenCenterPos.y) * 5.f;
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
				// Start battle
				if (!button->GetName().compare("begin") && !GAME_MGR->GetPlayingBattle())
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
					if (curBattleCharacterCount != GAME_MGR->GetCharacterCount())
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
					GAME_MGR->GetBattleTracker()->SetDatas();

					b_centerPos = true;
					ZoomIn();

					GAME_MGR->SetPlayingBattle(true);

					ui->GetTracker()->ShowGiven();
					ui->GetTracker()->ShowWindow(false);
					break;
				}
				// Summon character
				else if (!button->GetName().compare("summon"))
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
					Character* newPick = GAME_MGR->SpawnPlayer(true);
					newPick->SetPos(prepareGridRect[idx]->GetPos());
					newPick->Init();
					prepareGrid[idx] = newPick;
					break;
				}
				// Expansion
				else if (!button->GetName().compare("expansion"))
				{
					int cost = GAME_MGR->GetCurrentExpansionCost();
					if (GAME_MGR->GetCurrentCoin() >= cost)
					{
						cout << "expansion troops" << endl;
						GAME_MGR->SetCharacterCount(GAME_MGR->GetCharacterCount() + 1);
						TranslateCoinState(-cost);
						GAME_MGR->TranslateExpansionCount(1);
						ui->GetPanel()->SetExpansionCostText(GAME_MGR->GetCurrentExpansionCost());
						break;
					}
					else
					{
						cout << "not enough coin" << endl;
						break;
					}

					/*int idx = GetZeroElem(prepareGrid);
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
						prepareGrid[idx] = item;
					}
					else
					{
						cout << "not enough coin" << endl;
						break;
					}
					break;*/
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

	if (!GAME_MGR->GetPlayingBattle())
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
			pick->SetHitBoxActive(true);
			pick = nullptr;
			return;
		}
		Vector2i beforeCoord = GAME_MGR->PosToIdx(beforeDragPos);
		vector<GameObj*>& beforeContainer = InBattleGrid(beforeCoord) ? battleGrid : prepareGrid;
		vector<GameObj*>& destContainer = dest ? battleGrid : prepareGrid;

		if (IsCharacter(pick))
		{
			PutDownCharacter(&beforeContainer, &destContainer, beforeCoord, destCoord);
			if (InBattleGrid(GAME_MGR->PosToIdx(pick->GetPos())))
			{
				dynamic_cast<Character*>(pick)->OnOffAttackAreas(true);
				pickAttackRangeRect = dynamic_cast<Character*>(pick)->GetAreas();
			}
		}
		else // item
			PutDownItem(&beforeContainer, &destContainer, beforeCoord, destCoord);

		if (pick != nullptr)
		{
			pick->SetHitBoxActive(true);
			pick = nullptr;
		}
		return;
	}

	if (gameEndTimer > 0.f)
	{
		gameEndTimer -= dt;

		if (gameEndTimer < 0.f)
		{
			gameEndTimer = 0.f;
			stageEnd = false;
			ui->SetStageEndWindow(false);
			ui->GetTracker()->ShowWindow(false);
			ui->GetTracker()->ProfilesReturn();

			GAME_MGR->SetPlayingBattle(false);

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

			// when stage clear
			if (stageResult)
			{
				WaveReward wr = GAME_MGR->GetWaveRewardMapElem();
				cout << wr.exp << wr.forge << wr.power << endl;
				if (wr.forge)
					cout << "reward is forge" << endl;
				else if (wr.power)
					cout << "reward is power" << endl;
				GAME_MGR->cumulativeExp += wr.exp;
				cout << "현재 누적 경험치: " << wr.exp << endl;

				if (GAME_MGR->curStageIdx < STAGE_MAX_COUNT - 1)
					GAME_MGR->curStageIdx++;
			}
			SetCurrentStage(GAME_MGR->curChapIdx, GAME_MGR->curStageIdx);
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
			//GAME_MGR->GetBattleTracker()->PrintAllData();
		}
		return;
	}

	if (GAME_MGR->GetPlayingBattle())
	{
		if (playerCount == 0)
		{
			gameEndTimer = 3.5f;
			stageEnd = true;
			stageResult = false;
			LoseFlag();
		}
		else if (aiCount == 0)
		{
			gameEndTimer = 3.5f;
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
		int num = ((GAME_MGR->curChapIdx) * 150) + j;
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

	vector<Item*>& drops = GAME_MGR->drops;
	for (auto& dropItem : drops)
	{
		dropItem->Draw(window);
	}

	// draw character on battle area
	if (!GAME_MGR->GetPlayingBattle())
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
		if (GAME_MGR->GetPlayingBattle() && !(start == &prepareGrid && dest == &prepareGrid))
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
				if (count >= GAME_MGR->GetCharacterCount())
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
			if (!GAME_MGR->GetPlayingBattle() || (start == &prepareGrid && dest == &prepareGrid))
			{
				// combinate condition
				Character* destCharacter = dynamic_cast<Character*>((*dest)[destIdx]);

				if (destCharacter->GetStarNumber() != STAR_MAX &&
					!destCharacter->GetName().compare(pick->GetName()) &&
					destCharacter->GetStarNumber() ==
					dynamic_cast<Character*>(pick)->GetStarNumber())
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
					destCharacter->UpdateItems();

					temp->Release();
					delete temp;
					dynamic_cast<Character*>(pick)->UpgradeStar(true, true);
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
		if (IsItem((*dest)[destIdx]))
		{
			Item* destItem = dynamic_cast<Item*>((*dest)[destIdx]);
			Item* pickItem = dynamic_cast<Item*>(pick);

			Item* newItem = GAME_MGR->CombineItem(destItem, pickItem);
			if (newItem != nullptr) // item + item combinate
			{
				CLOG::Print3String("item combinate");
				pick = newItem;
				(*start)[startIdx] = nullptr;
				(*dest)[destIdx] = nullptr;
				destItem->Release();
				pickItem->Release();
				delete destItem;
				delete pickItem;
			}
			else destItem->SetPos(beforeDragPos); // swap
		}
		else // give a item to the character
		{
			if (!GAME_MGR->GetPlayingBattle() || dest == &prepareGrid)
			{
				Character* destCharacter = dynamic_cast<Character*>((*dest)[destIdx]);
				Item* pickItem = dynamic_cast<Item*>(pick);
				if (pickItem->GetItemType() == ItemType::Book)
				{
					if (pickItem->GetGrade() == (destCharacter->GetStarNumber() - 1) / 2)
					{
						destCharacter->UpgradeStar(false, false);
						(*start)[startIdx] = nullptr;
						pickItem->Release();
						delete pickItem;
						combine = true;
						pick = nullptr;
					}
				}
				else
				{
					if (destCharacter->SetItem(pickItem))
					{
						(*start)[startIdx] = nullptr;
						combine = true;
						destCharacter->UpdateItems();
						pick = nullptr;
					}
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

	GAME_MGR->MainGridReset();

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

	ui->GetPanel()->SetStageNumber(GAME_MGR->curStageIdx + 1);
	cout << "current chapter, stage (" << GAME_MGR->curChapIdx << ", " << GAME_MGR->curStageIdx << ")" << endl;
}

void BattleScene::LoseFlag()
{
	remainLife--;
	flags[remainLife]->SetActive(false);
	if (!remainLife)
	{
		isGameOver = true;
		gameOverTimer = 5.f;

		cout << "Game Over !!" << endl;
		GAME_MGR->accountInfo.AddExp(GAME_MGR->cumulativeExp);
		GAME_MGR->accountInfo.UpdateLevel(GAME_MGR->accountExpLimit);
		GAME_MGR->GameEnd();
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