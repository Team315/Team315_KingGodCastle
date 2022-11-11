#include "BattleScene.h"
#include "Include.h"

BattleScene::BattleScene()
	: Scene(Scenes::Battle)
{
	CLOG::Print3String("battle create");

	CreateBackground(10, 16, 51.f, 51.f);
	Vector2f cenPos = ((Vector2f(510.f / 2.f, 765.f / 2.f)));
	background->SetPos(cenPos);
	background->SetOrigin(Origins::MC);

	evan = new Evan();
	evan->Init(goblin00);
	objList.push_back(evan);

	goblin00 = new Goblin00();
	goblin00->Init(evan);
	objList.push_back(goblin00);

	for (auto obj : objList)
	{
		obj->Init();
	}
}

BattleScene::~BattleScene()
{
}

void BattleScene::Init()
{
	CLOG::Print3String("battle Init");

	for (auto obj : objList)
	{
		obj->Init();
	}
}

void BattleScene::Release()
{
}

void BattleScene::Enter()
{
	CLOG::Print3String("battle enter");

	FRAMEWORK->GetWindow().setSize(Vector2u(GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT));
	currentView = gameView;
}

void BattleScene::Exit()
{
	CLOG::Print3String("battle exit");
}

void BattleScene::Update(float dt)
{
	if (InputMgr::GetKeyDown(Keyboard::Key::Escape))
	{
		CLOG::Print3String("setting window");
		SCENE_MGR->ChangeScene(Scenes::Loby);
		return;
	}

	Scene::Update(dt);
}

void BattleScene::Draw(RenderWindow& window)
{
	Scene::Draw(window);
}

void BattleScene::CreateBackground(int cols, int rows, float qWidth, float qHeight)
{
	if (background == nullptr)
	{
		background = new VertexArrayObj();
		background->SetTexture(GetTexture("graphics/Charactor/battelScene_Background/battelScene_Background.png"));
		objList.push_back(background);
	}

	Vector2f startPos = background->GetPos();
	VertexArray& va = background->GetVA();
	va.setPrimitiveType(Quads);
	va.resize(cols * rows * 4);

	Vector2f currPos = startPos;

	Vector2f offsets[4] = { {0,0}, {qWidth,0}, {qWidth,qHeight}, {0,qHeight} };
	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			int quadIndex = i * cols + j;

			int texIndex = (i == 0 || i == rows - 1) || ((j == 0) || (j == cols - 1))
				? 3 : 3;

			for (int k = 0; k < 4; ++k)
			{
				va[quadIndex * 4 + k].position = currPos + offsets[k];
				va[quadIndex * 4 + k].texCoords = offsets[k] + Vector2f{ 0.f, texIndex * qHeight };
			}
			currPos.x += qWidth;
		}
		currPos.x = startPos.x;
		currPos.y += qHeight;
	}
}
