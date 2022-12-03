#include "BattleSceneUI.h"
#include "Include.h"
#include "BattlePanel.h"
#include "Character.h"
#include "RectangleObj.h"
#include "BackrectText.h"
#include "Item/Item.h"
#include "StatPopupWindow.h"

BattleSceneUI::BattleSceneUI(Scene* scene)
	: UIMgr(scene)
{
	panel = new BattlePanel();
	CreateBackground(panel, 1, 3, 188.f, 500.f);

	statPopup = new StatPopupWindow(200.f, 180.f);
	statPopup->SetOutline(Color::Black, -2.f);
	statPopup->SetOrigin(Origins::TL);

	itemPopup = new BackrectText(100, 60);
	itemPopup->SetOutline(Color::Black, 2.0f);
	itemPopup->SetFillColor(Color(0, 0, 0, 150.f));
	itemPopup->SetFont(*RESOURCE_MGR->GetFont("fonts/GodoB.ttf"));
	itemPopup->SetTextStyle(Color::White, 20, Color::Black, -1.0f);
	itemPopup->SetTextLocalPos(Vector2f(10.f, 10.f));

	stageEndWindow = new BackrectText(GAME_SCREEN_WIDTH, 100.f);
	stageEndWindow->SetTextLocalPos(Vector2f(-20.f, 0.f));
	stageEndWindow->SetPos(Vector2f(GAME_SCREEN_WIDTH * 0.5f, 200.f));
	stageEndWindow->SetFillColor(Color(0, 0, 0, 150.f));
	stageEndWindow->SetOrigin(Origins::MC);
	stageEndWindow->SetFont(*RESOURCE_MGR->GetFont("fonts/GodoB.ttf"));
	stageEndWindow->SetTextStyle(Color::White, 20, Color::Black, -1.0f);
}

BattleSceneUI::~BattleSceneUI()
{
	Release();
}

void BattleSceneUI::Init()
{
	uiObjList.push_back(panel);
	uiObjList.push_back(statPopup);
	uiObjList.push_back(itemPopup);
	uiObjList.push_back(stageEndWindow);
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
	itemPopup->SetActive(false);
	stageEndWindow->SetActive(false);
	panel->SetCurrentCoin(GAME_MGR->GetCurrentCoin());
}

void BattleSceneUI::Update(float dt)
{
	UIMgr::Update(dt);
}

void BattleSceneUI::Draw(RenderWindow& window)
{
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

	Vector2f modPos = pos;
	if (pos.x + statPopup->GetSize().x >= GAME_SCREEN_ZOOM_WIDTH)
		modPos.x = GAME_SCREEN_ZOOM_WIDTH - statPopup->GetSize().x ;
	if (Utils::EqualFloat(viewCenter.y, GAME_SCREEN_ZOOM_HEIGHT * 0.5f, 3.f) &&
		(pos.y + statPopup->GetSize().y >= GAME_SCREEN_ZOOM_HEIGHT))
		modPos.y = GAME_SCREEN_ZOOM_HEIGHT - statPopup->GetSize().y - 5.f;

	statPopup->SetCharacter(character);
	statPopup->SetPos(modPos);
}

void BattleSceneUI::SetItemPopup(bool active, Vector2f viewCenter,
	Item* item, Vector2f pos)
{
	itemPopup->SetActive(active);
	if (!active)
		return;

	Vector2f modPos = pos;
	if (pos.x + itemPopup->GetSize().x >= GAME_SCREEN_ZOOM_WIDTH)
		modPos.x = GAME_SCREEN_ZOOM_WIDTH - itemPopup->GetSize().x;
	if (Utils::EqualFloat(viewCenter.y, GAME_SCREEN_ZOOM_HEIGHT * 0.5f, 3.f) &&
		(pos.y + itemPopup->GetSize().y >= GAME_SCREEN_ZOOM_HEIGHT))
		modPos.y = GAME_SCREEN_ZOOM_HEIGHT - itemPopup->GetSize().y - 5.f;

	itemPopup->SetString(item->GetName() + item->GetStatTypeString() + to_string(item->GetPotential()));
	itemPopup->SetPos(modPos);
}

void BattleSceneUI::SetStageEndWindow(bool active, bool result)
{
	stageEndWindow->SetActive(active);
	if (!active)
		return;

	stageEndWindow->SetString(result ? L"전투 승리!" : L"전투 패배!");
}