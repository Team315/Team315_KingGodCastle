#include "LobySceneUI.h"
#include "Include.h"

LobySceneUI::LobySceneUI(Scene* scene)
	: UIMgr(scene)
{
	hud = new HUD();
}

LobySceneUI::~LobySceneUI()
{
}

void LobySceneUI::Init()
{
	uiObjList.push_back(hud);

	UIMgr::Init();
}

void LobySceneUI::Release()
{
	UIMgr::Release();
}

void LobySceneUI::Reset()
{
	UIMgr::Reset();
}

void LobySceneUI::Update(float dt)
{
	UIMgr::Update(dt);
}

void LobySceneUI::Draw(RenderWindow& window)
{
	UIMgr::Draw(window);
}

HUD::HUD() : tabSize(5)
{
	for (int i = 0; i < tabSize; i++)
	{
		buttons.push_back(new SpriteButton());
	}

	Vector2f textSpacing(26.f, 60.f);
	buttons[(int)buttonMode::shop]->SetButton(
		*RESOURCE_MGR->GetTexture("graphics/commonUI/Background.png"),
		*RESOURCE_MGR->GetFont("fonts/NANUMBARUNGOTHICBOLD.ttf"), L"상점",
		*RESOURCE_MGR->GetTexture("graphics/mainScene/Bottom_Icon_01.png"),
		textSpacing.x, textSpacing.y);
	buttons[(int)buttonMode::barrack]->SetButton(
		*RESOURCE_MGR->GetTexture("graphics/commonUI/Background.png"),
		*RESOURCE_MGR->GetFont("fonts/NANUMBARUNGOTHICBOLD.ttf"), L"병영",
		*RESOURCE_MGR->GetTexture("graphics/mainScene/Bottom_Icon_02.png"),
		textSpacing.x, textSpacing.y);
	buttons[(int)buttonMode::gate]->SetButton(
		*RESOURCE_MGR->GetTexture("graphics/commonUI/Background.png"),
		*RESOURCE_MGR->GetFont("fonts/NANUMBARUNGOTHICBOLD.ttf"), L"성문",
		*RESOURCE_MGR->GetTexture("graphics/mainScene/Bottom_Icon_03.png"),
		textSpacing.x, textSpacing.y);
	buttons[(int)buttonMode::altar]->SetButton(
		*RESOURCE_MGR->GetTexture("graphics/commonUI/Background.png"),
		*RESOURCE_MGR->GetFont("fonts/NANUMBARUNGOTHICBOLD.ttf"), L"제단",
		*RESOURCE_MGR->GetTexture("graphics/mainScene/Bottom_Icon_04.png"),
		textSpacing.x, textSpacing.y);
	buttons[(int)buttonMode::mode]->SetButton(
		*RESOURCE_MGR->GetTexture("graphics/commonUI/Background.png"),
		*RESOURCE_MGR->GetFont("fonts/NANUMBARUNGOTHICBOLD.ttf"), L"모드",
		*RESOURCE_MGR->GetTexture("graphics/mainScene/Bottom_Icon_05.png"),
		textSpacing.x, textSpacing.y);

	for (auto button : buttons)
	{
		button->SetButtonSpriteSpacing(15.f, 10.f);
	}
}

HUD::~HUD()
{
	Release();
}

void HUD::Init()
{
	Vector2f pos(0.f, 600.f);
	for (auto button : buttons)
	{
		button->SetPos(pos);
		pos.x += 105.f;
	}
}

void HUD::Release()
{
	for (auto button : buttons)
	{
		delete button;
	}
	buttons.clear();
}

void HUD::Reset()
{
}

void HUD::Update(float dt)
{
	for (auto button : buttons)
	{
		button->Update(dt);
	}
}

void HUD::Draw(RenderWindow& window)
{
	for (auto button : buttons)
	{
		button->Draw(window);
	}
}