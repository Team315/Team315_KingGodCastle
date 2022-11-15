#include "BattleSceneUI.h"
#include "Include.h"
#include "BattlePanel.h"

BattleSceneUI::BattleSceneUI(Scene* scene)
	: UIMgr(scene)
{
	panel = new BattlePanel();
	CreateBackground(panel, 1, 3, 188.f, 400.f);
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
	panel->SetPos(Vector2f(0, GAME_SCREEN_HEIGHT * 1.1f));
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