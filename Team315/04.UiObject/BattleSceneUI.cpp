#include "BattleSceneUI.h"
#include "Include.h"
#include "BattlePanel.h"
#include "RectangleObj.h"
#include "StatPopupWindow.h"

BattleSceneUI::BattleSceneUI(Scene* scene)
	: UIMgr(scene)
{
	panel = new BattlePanel();
	CreateBackground(panel, 1, 3, 188.f, 500.f);

	statPopup = new StatPopupWindow(200.f, 200.f);
	statPopup->SetFillColor(Color(50, 50, 50, 200));
	statPopup->SetOutline(Color::Black, -2.f);
	statPopup->SetType("Popup");
	statPopup->SetOrigin(Origins::TL);
}

BattleSceneUI::~BattleSceneUI()
{
	Release();
}

void BattleSceneUI::Init()
{
	uiObjList.push_back(panel);
	uiObjList.push_back(statPopup);
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

void BattleSceneUI::SetStatPopup(bool active, Vector2f viewCenter, Vector2f pos)
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
	statPopup->SetPos(modPos);
}