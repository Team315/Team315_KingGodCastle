#include "MainSceneUI.h"
#include "Include.h"

MainSceneUI::MainSceneUI(Scene* scene)
	: UIMgr(scene), tabCount(5), currentBackground(2)
{
}

MainSceneUI::~MainSceneUI()
{
}

void MainSceneUI::Init()
{
	backgrounds.resize(tabCount);
	for (int i = 0; i < tabCount; i++)
	{
		string textureKey = "graphics/mainBackground_";
		textureKey += (i < 10 ? "0" : "") + to_string(i + 1) + ".png";
		backgrounds[i] = new SpriteObj();
		CLOG::Print3String(textureKey);
		backgrounds[i]->SetTexture(*RESOURCE_MGR->GetTexture(textureKey));
	}
	
}

void MainSceneUI::Release()
{
	UIMgr::Release();
}

void MainSceneUI::Reset()
{
}

void MainSceneUI::Update(float dt)
{
	if (InputMgr::GetKeyDown(Keyboard::Key::Num1))
	{
		CLOG::Print3String("상점");
		currentBackground = 0;
		return;
	}
	if (InputMgr::GetKeyDown(Keyboard::Key::Num2))
	{
		CLOG::Print3String("병영");
		currentBackground = 1;
		return;
	}
	if (InputMgr::GetKeyDown(Keyboard::Key::Num3))
	{
		CLOG::Print3String("성문");
		currentBackground = 2;
		return;
	}
	if (InputMgr::GetKeyDown(Keyboard::Key::Num4))
	{
		CLOG::Print3String("제단");
		currentBackground = 3;
		return;
	}
	if (InputMgr::GetKeyDown(Keyboard::Key::Num5))
	{
		CLOG::Print3String("모드");
		currentBackground = 4;
		return;
	}
	UIMgr::Update(dt);
}

void MainSceneUI::Draw(RenderWindow& window)
{
	UIMgr::Draw(window);
}

void MainSceneUI::DrawBackground(RenderWindow& window)
{
	backgrounds[currentBackground]->Draw(window);
}