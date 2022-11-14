#include "BattleScene.h"
#include "Include.h"
#include "Constant.h"

BattleScene::BattleScene()
	: Scene(Scenes::Battle)
{
	CLOG::Print3String("battle create");

	CreateBackground(TILE_WIDTH, TILE_HEIGHT, TILE_SIZE_X, TILE_SIZE_Y);
	Vector2f cenPos = ((Vector2f(GAME_SCREEN_WIDTH / 2.f, GAME_SCREEN_HEIGHT / 2.f)));
	background->SetPos(cenPos);
	background->SetOrigin(Origins::MC);

	evan = new Evan();
	objList.push_back(evan);

	goblin00 = new Goblin00();
	objList.push_back(goblin00);

	float tempY = TILE_SIZE_Y;
	overlay.resize(GAME_TILE_HEIGHT);
	for (auto& tiles : overlay)
	{
		tiles = new vector<RectangleObj*>;
		tiles->resize(GAME_TILE_WIDTH);
		float tempX = TILE_SIZE_X * 2.f;
		for (auto& tile : *tiles)
		{
			tile = new RectangleObj(47.f, 47.f);
			tile->SetFillColor(Color(255, 255, 255, 80));
			tile->SetOutline(Color::White, 1.5f);
			tile->SetPos(Vector2f(tempX, tempY));
			tile->SetOrigin(Origins::BC);
			objList.push_back(tile);
			tempX += TILE_SIZE_X;
		}
		tempY += TILE_SIZE_Y;
	}
}

BattleScene::~BattleScene()
{
}

void BattleScene::Init()
{
	CLOG::Print3String("battle Init");

	goblin00->SetTarget(evan);
	evan->SetTarget(goblin00);
	Scene::Init();
}

void BattleScene::Release()
{
}

void BattleScene::Enter()
{
	CLOG::Print3String("battle enter");

	FRAMEWORK->GetWindow().setSize(Vector2u(GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT));
	currentView = gameView;

	for (auto& tiles : overlay)
	{
		for (auto& tile : *tiles)
			tile->SetActive(false);
	}
}

void BattleScene::Exit()
{
	CLOG::Print3String("battle exit");
}

void BattleScene::Update(float dt)
{
	// Dev Input start
	if (InputMgr::GetKeyDown(Keyboard::Key::Escape))
	{
		CLOG::Print3String("setting window");
		SCENE_MGR->ChangeScene(Scenes::Loby);
		return;
	}
	if (InputMgr::GetKeyDown(Keyboard::Key::Num0))
	{
		CLOG::Print3String("overlay true");
		for (auto& tiles : overlay)
		{
			for (auto& tile : *tiles)
				tile->SetActive(true);
		}
	}
	if (InputMgr::GetKeyUp(Keyboard::Key::Num0))
	{
		CLOG::Print3String("overlay false");
		for (auto& tiles : overlay)
		{
			for (auto& tile : *tiles)
				tile->SetActive(false);
		}
	}
	float wheel = InputMgr::GetMouseWheel();
	if (wheel != 0)
	{
		CLOG::Print3String(to_string(wheel));
	}

	// Dev Input end

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
		background->SetTexture(GetTexture("graphics/battleScene/TempBackground.png"));
		objList.push_back(background);
	}

	Vector2f startPos = background->GetPos();
	VertexArray& va = background->GetVA();
	va.setPrimitiveType(Quads);
	va.resize(cols * rows * 4);

	Vector2f currPos = startPos;

	Vector2f offsets[4] = { {0, 0}, {qWidth, 0}, {qWidth, qHeight}, {0, qHeight} };
	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			int quadIndex = i * cols + j;

			/*int texIndex = (i == 0 || i == rows - 1) || ((j == 0) || (j == cols - 1))
				? 3 : 3;*/

			int texX = 0;
			int texY = 0;

			for (int k = 0; k < 4; ++k)
			{
				va[quadIndex * 4 + k].position = currPos + offsets[k];
				va[quadIndex * 4 + k].texCoords = offsets[k] + Vector2f{ texX * qWidth, texY * qHeight };
			}
			currPos.x += qWidth;
		}
		currPos.x = startPos.x;
		currPos.y += qHeight;
	}
}
