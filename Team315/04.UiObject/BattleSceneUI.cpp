#include "BattleSceneUI.h"
#include "Include.h"
#include "BattlePanel.h"

BattleSceneUI::BattleSceneUI(Scene* scene)
	: UIMgr(scene)
{
	panel = new BattlePanel();
}

BattleSceneUI::~BattleSceneUI()
{
	Release();
}

void BattleSceneUI::Init()
{
	uiObjList.push_back(panel);
	UIMgr::Init();
}

void BattleSceneUI::Release()
{
	UIMgr::Release();
}

void BattleSceneUI::Reset()
{
	panel->SetPos(Vector2f(GAME_SCREEN_WIDTH * 0.5f, GAME_SCREEN_HEIGHT));
	UIMgr::Reset();
}

void BattleSceneUI::Update(float dt)
{
	UIMgr::Update(dt);
}

void BattleSceneUI::Draw(RenderWindow& window)
{
	UIMgr::Draw(window);
}
