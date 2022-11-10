#include "LobySceneUI.h"
#include "Include.h"
#include "Constant.h"
#include "SpriteButton.h"
#include "RectangleObj.h"
#include "RssProgressWindow.h"
#include "RssTextWindow.h"

LobySceneUI::LobySceneUI(Scene* scene)
	: UIMgr(scene), tabSize((int)buttonModeEnum::count), buttonSize(100.f), gameResourceCount((int)gameResourceEnum::count)
{
	// bottom tab
	for (int i = 0; i < tabSize; i++)
		buttons.push_back(new SpriteButton());

	Vector2f textSpacing(26.f, 60.f);
	buttons[(int)buttonModeEnum::shop]->SetButton(
		*RESOURCE_MGR->GetTexture("graphics/commonUI/Background.png"),
		*RESOURCE_MGR->GetFont("fonts/NANUMBARUNGOTHICBOLD.ttf"), L"상점",
		*RESOURCE_MGR->GetTexture("graphics/mainScene/Bottom_Icon_01.png"),
		textSpacing.x, textSpacing.y);
	buttons[(int)buttonModeEnum::barrack]->SetButton(
		*RESOURCE_MGR->GetTexture("graphics/commonUI/Background.png"),
		*RESOURCE_MGR->GetFont("fonts/NANUMBARUNGOTHICBOLD.ttf"), L"병영",
		*RESOURCE_MGR->GetTexture("graphics/mainScene/Bottom_Icon_02.png"),
		textSpacing.x, textSpacing.y);
	buttons[(int)buttonModeEnum::gate]->SetButton(
		*RESOURCE_MGR->GetTexture("graphics/commonUI/Background.png"),
		*RESOURCE_MGR->GetFont("fonts/NANUMBARUNGOTHICBOLD.ttf"), L"성문",
		*RESOURCE_MGR->GetTexture("graphics/mainScene/Bottom_Icon_03.png"),
		textSpacing.x, textSpacing.y);
	buttons[(int)buttonModeEnum::altar]->SetButton(
		*RESOURCE_MGR->GetTexture("graphics/commonUI/Background.png"),
		*RESOURCE_MGR->GetFont("fonts/NANUMBARUNGOTHICBOLD.ttf"), L"제단",
		*RESOURCE_MGR->GetTexture("graphics/mainScene/Bottom_Icon_04.png"),
		textSpacing.x, textSpacing.y);
	buttons[(int)buttonModeEnum::mode]->SetButton(
		*RESOURCE_MGR->GetTexture("graphics/commonUI/Background.png"),
		*RESOURCE_MGR->GetFont("fonts/NANUMBARUNGOTHICBOLD.ttf"), L"모드",
		*RESOURCE_MGR->GetTexture("graphics/mainScene/Bottom_Icon_05.png"),
		textSpacing.x, textSpacing.y);

	for (auto button : buttons)
		button->SetBtnSpriteLocalPos(15.f, 10.f);

	// top resources
	float blockLength = GAME_SCREEN_WIDTH / gameResourceCount;
	Vector2f startPos(10.f, 10.f);

	expWind = new RssProgressWindow();
	expWind->SetTexture(*RESOURCE_MGR->GetTexture("graphics/mainScene/Icon_Level.png"));
	float texHeight = expWind->GetTextureRect().height;
	expWind->SetSize(Vector2f(120, texHeight * 0.5f));
	expWind->SetColor(Color(0, 0, 0, 100), Color::Green, Color::Black, 2.f);
	expWind->SetProgressLocalPos(Vector2f(expWind->GetTextureRect().width * 0.5f, texHeight * 0.25f));
	expWind->SetPos(startPos);
	startPos.x += blockLength;
	startPos.y += 15.f;

	goldWind = new RssTextWindow(*RESOURCE_MGR->GetFont("fonts/NotoSans-Bold.ttf"));
	goldWind->SetTexture(*RESOURCE_MGR->GetTexture("graphics/mainScene/Icon_Gold.png"));
	goldWind->SetBackLocalPos(Vector2f(20.f, texHeight * 0.25f - 15.f));
	goldWind->SetTextLocalPos(Vector2f(50.f, texHeight * 0.25f - 7.5f));
	goldWind->SetPos(startPos);
	startPos.x += blockLength;
	goldWind->SetSize(Vector2f(120, texHeight * 0.5f));
	goldWind->SetBackgroundColor(Color(0, 0, 0, 100));
	goldWind->SetBackgroundOutline(Color::Black, 2.f);
	goldWind->SetTextStyle(Color::White, 20);
	goldWind->SetTextOutline(Color::Black, 2.f);

	jewelWind = new RssTextWindow(*RESOURCE_MGR->GetFont("fonts/NotoSans-Bold.ttf"));
	jewelWind->SetTexture(*RESOURCE_MGR->GetTexture("graphics/mainScene/Icon_Jewelry.png"));
	jewelWind->SetBackLocalPos(Vector2f(20.f, texHeight * 0.25f - 15.f));
	jewelWind->SetTextLocalPos(Vector2f(50.f, texHeight * 0.25f - 7.5f));
	jewelWind->SetPos(startPos);
	jewelWind->SetSize(Vector2f(120, texHeight * 0.5f));
	jewelWind->SetBackgroundColor(Color(0, 0, 0, 100));
	jewelWind->SetBackgroundOutline(Color::Black, 2.f);
	jewelWind->SetTextStyle(Color::White, 20);
	jewelWind->SetTextOutline(Color::Black, 2.f);
}

LobySceneUI::~LobySceneUI()
{
	Release();
}

void LobySceneUI::Init()
{
	Vector2f pos(0.f, FRAMEWORK->GetWindowSize().y - buttonSize);
	for (auto button : buttons)
	{
		button->SetPos(pos);
		pos.x += buttonSize + 3.f;
		uiObjList.push_back(button);
	}

	uiObjList.push_back(goldWind);
	uiObjList.push_back(jewelWind);
	uiObjList.push_back(expWind);

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