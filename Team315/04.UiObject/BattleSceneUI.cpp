#include "BattleSceneUI.h"
#include "Include.h"
#include "BattlePanel.h"
#include "RectangleObj.h"
#include "StatPopupWindow.h"

BattleSceneUI::BattleSceneUI(Scene* scene)
	: UIMgr(scene), b_battleGridRect(false)
{
	panel = new BattlePanel();
	CreateBackground(panel, 1, 3, 188.f, 500.f);

	prepareGrid.resize(PREPARE_SIZE);
	float outlineThickness = -2.f;
	float posX = TILE_SIZE * 2.f;
	float posY = GAME_SCREEN_HEIGHT + TILE_SIZE * 2.f;
	int count = 0;
	for (auto& cell : prepareGrid)
	{
		cell = new RectangleObj(TILE_SIZE - 1, TILE_SIZE - 1);
		cell->SetOutline(Color(255, 255, 255, 100), outlineThickness);
		cell->SetFillColor(Color(0, 0, 0, 0));
		cell->SetPos(Vector2f(posX, posY));
		cell->SetOrigin(Origins::BC);
		uiObjList.push_back(cell);
		count++;
		posX += TILE_SIZE;
		if (count == prepareGrid.size() * 0.5f)
		{
			posX = TILE_SIZE * 2.f;
			posY += TILE_SIZE;
		}
	}

	battleGridRect.resize(BATTLE_GRID_ROW);
	posY = TILE_SIZE * 11.f;
	for (auto& tiles : battleGridRect)
	{
		tiles.resize(GAME_TILE_WIDTH);
		float posX = TILE_SIZE * 2.f;
		for (auto& tile : tiles)
		{
			tile = new RectangleObj(TILE_SIZE - 1, TILE_SIZE - 1);
			tile->SetFillColor(Color(255, 255, 255, 20));
			tile->SetOutline(Color::White, outlineThickness);
			tile->SetPos(Vector2f(posX, posY));
			tile->SetOrigin(Origins::BC);
			uiObjList.push_back(tile);
			posX += TILE_SIZE;
		}
		posY += TILE_SIZE;
	}

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
	UIMgr::Reset();
	b_battleGridRect = false;
	for (auto& tiles : battleGridRect)
	{
		for (auto& tile : tiles)
			tile->SetActive(b_battleGridRect);
	}
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

Vector2f BattleSceneUI::GetGridPos(int idx)
{
	return prepareGrid[idx]->GetPos();
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