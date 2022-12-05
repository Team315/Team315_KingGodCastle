#include "BattleSceneUI.h"
#include "BattlePanel.h"
#include "BackrectText.h"
#include "Character.h"
#include "DamageTrackerUI.h"
#include "Include.h"
#include "ItemInfoWindow.h"
#include "Item/Item.h"
#include "RectangleObj.h"
#include "StatPopupWindow.h"

BattleSceneUI::BattleSceneUI(Scene* scene)
	: UIMgr(scene), b_stageEndPopup(false)
{
	panel = new BattlePanel();
	CreateBackground(panel, 1, 3, 188.f, 500.f);

	statPopup = new StatPopupWindow(200.f, 180.f);
	statPopup->SetOutline(Color::Black, -2.f);
	statPopup->SetOrigin(Origins::TL);

	itemPopups.resize(3);
	for (auto& popup : itemPopups)
		popup = new ItemInfoWindow(200.f, 60.f);

	stageEndWindow = new BackrectText(GAME_SCREEN_WIDTH, 80.f);
	stageEndWindow->SetTextLocalPos(Vector2f(0.f, -10.f));
	stageEndWindow->SetPos(Vector2f(GAME_SCREEN_WIDTH * 0.5f, 200.f));
	stageEndWindow->SetFillColor(Color(0, 0, 0, 150.f));
	stageEndWindow->SetFont(*RESOURCE_MGR->GetFont("fonts/GodoB.ttf"));
	stageEndWindow->SetTextStyle(Color::White, 20, Color::Black, -1.0f);

	stageEndWindowSprite.setTexture(*RESOURCE_MGR->GetTexture("graphics/battleScene/Start.png"));
	stageEndWindowSprite.setPosition(Vector2f(GAME_SCREEN_WIDTH * 0.5f, 200.f));
	Utils::SetOrigin(stageEndWindowSprite, Origins::MC);

	dmgTrackerUI = new DamageTrackerUI();
	dmgTrackerUI->SetPos(Vector2f(400.f, 200.f));
}

BattleSceneUI::~BattleSceneUI()
{
	Release();
}

void BattleSceneUI::Init()
{
	uiObjList.push_back(panel);
	uiObjList.push_back(statPopup);
	for (auto& popup : itemPopups)
		uiObjList.push_back(popup);
	uiObjList.push_back(stageEndWindow);
	uiObjList.push_back(dmgTrackerUI);
	UIMgr::Init();
}

void BattleSceneUI::Release()
{
	UIMgr::Release();
}

void BattleSceneUI::Reset()
{
	panel->SetPos(Vector2f(0, GAME_SCREEN_HEIGHT * 1.2f));
	statPopup->SetActive(false);
	for (auto& popup : itemPopups)
		popup->SetActive(false);
	stageEndWindow->SetActive(false);
	panel->SetCurrentCoin(GAME_MGR->GetCurrentCoin());
}

void BattleSceneUI::Update(float dt)
{
	UIMgr::Update(dt);
}

void BattleSceneUI::Draw(RenderWindow& window)
{
	if (b_stageEndPopup)
		window.draw(stageEndWindowSprite);
	UIMgr::Draw(window);
}

void BattleSceneUI::SetOrigin(Origins origin)
{
}

void BattleSceneUI::CreateBackground(VertexArrayObj* vao, int rows, int cols, float quadWidth, float quadHeight)
{
	Vector2f startPos = vao->GetPos();
	VertexArray& va = vao->GetVA();
	va.clear();
	va.setPrimitiveType(Quads);
	va.resize(rows * cols * 4);
	Vector2f currPos = startPos;

	Vector2f offsets[4] = {
		{0, 0},
		{quadWidth, 0},
		{quadWidth, quadHeight},
		{0, quadHeight},
	};

	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			int texIndexX = 0;
			int texIndexY = 0;

			int quadIndex = i * cols + j;
			for (int k = 0; k < 4; ++k)
			{
				int vertexIndex = quadIndex * 4 + k;
				va[vertexIndex].position = currPos + offsets[k];
				va[vertexIndex].texCoords = offsets[k];
				va[vertexIndex].texCoords.x += quadWidth * texIndexX;
				va[vertexIndex].texCoords.y += quadHeight * texIndexY;
			}
			currPos.x += quadWidth;
		}
		currPos.x = startPos.x;
		currPos.y += quadHeight;
	}
}

void BattleSceneUI::SetStatPopup(bool active, Vector2f viewCenter,
	Character* character, Vector2f pos)
{
	statPopup->SetActive(active);
	if (!active)
		return;

	statPopup->SetCharacter(character);
	vector<Item*>& items = character->GetItems();
	int len = items.size();

	Vector2f modPos = pos;
	if (pos.x >= GAME_SCREEN_ZOOM_WIDTH - statPopup->GetSize().x - (len > 0 ? 205.f : 0.f))
		modPos.x = GAME_SCREEN_ZOOM_WIDTH - statPopup->GetSize().x - (len > 0 ? 205.f : 0.f);
	if (Utils::EqualFloat(viewCenter.y, GAME_SCREEN_ZOOM_HEIGHT * 0.5f, 3.f) &&
		(pos.y + statPopup->GetSize().y >= GAME_SCREEN_ZOOM_HEIGHT))
		modPos.y = GAME_SCREEN_ZOOM_HEIGHT - statPopup->GetSize().y - 5.f;

	statPopup->SetPos(modPos);

	modPos.x += 205.f;
	modPos.y -= 20.f;
	for (int i = 0; i < len; i++)
	{
		itemPopups[i]->SetActive(true);
		itemPopups[i]->SetItem(items[i]);
		itemPopups[i]->SetPos(modPos);
		modPos.y += 65.f;
	}
}

void BattleSceneUI::SetItemPopup(bool active, Vector2f viewCenter,
	Item* item, Vector2f pos)
{
	itemPopups[0]->SetActive(active);
	itemPopups[1]->SetActive(false);
	itemPopups[2]->SetActive(false);
	if (!active)
		return;

	Vector2f modPos = pos;
	if (pos.x + itemPopups[0]->GetSize().x >= GAME_SCREEN_ZOOM_WIDTH)
		modPos.x = GAME_SCREEN_ZOOM_WIDTH - itemPopups[0]->GetSize().x;
	if (Utils::EqualFloat(viewCenter.y, GAME_SCREEN_ZOOM_HEIGHT * 0.5f, 3.f) &&
		(pos.y + itemPopups[0]->GetSize().y >= GAME_SCREEN_ZOOM_HEIGHT))
		modPos.y = GAME_SCREEN_ZOOM_HEIGHT - itemPopups[0]->GetSize().y - 5.f;
	itemPopups[0]->SetItem(item);
	itemPopups[0]->SetPos(modPos);
}

void BattleSceneUI::SetStageEndWindow(bool active, bool result)
{
	b_stageEndPopup = active;
	stageEndWindow->SetActive(active);
	if (!active)
		return;

	stageEndWindow->SetString(result ? L"전투 승리!" : L"전투 패배!");
	stageEndWindow->SetOrigin(Origins::MC);
}