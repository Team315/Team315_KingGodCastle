#include "LobySceneUI.h"
#include "LobyScene.h"
#include "Include.h"
#include "Character.h"
#include "Constant.h"
#include "SpriteButton.h"
#include "RectangleObj.h"
#include "SpriteObj.h"
#include "RssProgressWindow.h"
#include "RssTextWindow.h"

LobySceneUI::LobySceneUI(Scene* scene)
	: UIMgr(scene), tabSize((int)buttonModeEnum::count), buttonSize(100.f), gameResourceCount((int)gameResourceEnum::count)
{
	// bottom tab
	for (int i = 0; i < tabSize; i++)
		buttons.push_back(new SpriteButton());

	{
		Vector2f textLocalPos(26.f, 60.f);
		buttons[(int)buttonModeEnum::shop]->SetButton(
			*RESOURCE_MGR->GetTexture("graphics/commonUI/Background.png"),
			*RESOURCE_MGR->GetFont("fonts/NANUMBARUNGOTHICBOLD.ttf"), L"상점",
			*RESOURCE_MGR->GetTexture("graphics/lobyScene/Bottom_Icon_01.png"),
			textLocalPos.x, textLocalPos.y);
		buttons[(int)buttonModeEnum::barrack]->SetButton(
			*RESOURCE_MGR->GetTexture("graphics/commonUI/Background.png"),
			*RESOURCE_MGR->GetFont("fonts/NANUMBARUNGOTHICBOLD.ttf"), L"병영",
			*RESOURCE_MGR->GetTexture("graphics/lobyScene/Bottom_Icon_02.png"),
			textLocalPos.x, textLocalPos.y);
		buttons[(int)buttonModeEnum::gate]->SetButton(
			*RESOURCE_MGR->GetTexture("graphics/commonUI/Background.png"),
			*RESOURCE_MGR->GetFont("fonts/NANUMBARUNGOTHICBOLD.ttf"), L"성문",
			*RESOURCE_MGR->GetTexture("graphics/lobyScene/Bottom_Icon_03.png"),
			textLocalPos.x, textLocalPos.y);
		buttons[(int)buttonModeEnum::altar]->SetButton(
			*RESOURCE_MGR->GetTexture("graphics/commonUI/Background.png"),
			*RESOURCE_MGR->GetFont("fonts/NANUMBARUNGOTHICBOLD.ttf"), L"제단",
			*RESOURCE_MGR->GetTexture("graphics/lobyScene/Bottom_Icon_04.png"),
			textLocalPos.x, textLocalPos.y);
		buttons[(int)buttonModeEnum::mode]->SetButton(
			*RESOURCE_MGR->GetTexture("graphics/commonUI/Background.png"),
			*RESOURCE_MGR->GetFont("fonts/NANUMBARUNGOTHICBOLD.ttf"), L"모드",
			*RESOURCE_MGR->GetTexture("graphics/lobyScene/Bottom_Icon_05.png"),
			textLocalPos.x, textLocalPos.y);
	}

	Vector2f startPos(0.f, GAME_SCREEN_HEIGHT - buttonSize);
	for (auto button : buttons)
	{
		button->SetBtnSpriteLocalPos(15.f, 10.f);
		button->SetButtonStyle(Color(255, 255, 255, 100), Color(255, 255, 255, 200));
		button->SetButtonTextColor(Color::White, Color::Black, 2.f);
		button->SetPos(startPos);
		startPos.x += buttonSize + 3.f;
	}

	// top resources
	float blockLength = GAME_SCREEN_WIDTH / gameResourceCount;
	startPos = { 10.f, 10.f };

	expWind = new RssProgressWindow();
	expWind->SetTexture(*RESOURCE_MGR->GetTexture("graphics/lobyScene/Icon_Level.png"));
	float texHeight = expWind->GetTextureRect().height;
	expWind->SetSize(Vector2f(120, texHeight * 0.5f));
	expWind->SetColor(Color(0, 0, 0, 100), Color::Green, Color::Black, 2.f);
	expWind->SetProgressLocalPos(Vector2f(expWind->GetTextureRect().width * 0.5f, texHeight * 0.25f));
	expWind->SetLevelTextLocalPos(Vector2f(expWind->GetTextureRect().width * 0.5f + 4, texHeight * 0.5f + 6));
	expWind->SetPos(startPos);
	startPos.x += blockLength;
	startPos.y += 15.f;

	goldWind = new RssTextWindow(*RESOURCE_MGR->GetFont("fonts/NotoSans-Bold.ttf"));
	goldWind->SetTexture(*RESOURCE_MGR->GetTexture("graphics/lobyScene/Icon_Gold.png"));
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
	jewelWind->SetTexture(*RESOURCE_MGR->GetTexture("graphics/lobyScene/Icon_Jewelry.png"));
	jewelWind->SetBackLocalPos(Vector2f(20.f, texHeight * 0.25f - 15.f));
	jewelWind->SetTextLocalPos(Vector2f(50.f, texHeight * 0.25f - 7.5f));
	jewelWind->SetPos(startPos);
	jewelWind->SetSize(Vector2f(120, texHeight * 0.5f));
	jewelWind->SetBackgroundColor(Color(0, 0, 0, 100));
	jewelWind->SetBackgroundOutline(Color::Black, 2.f);
	jewelWind->SetTextStyle(Color::White, 20);
	jewelWind->SetTextOutline(Color::Black, 2.f);

	// shop tab
	shopBackgroundOverlay = new RectangleObj(GAME_SCREEN_WIDTH * 0.8f, GAME_SCREEN_HEIGHT * 0.75f);
	shopBackgroundOverlay->SetPos(Vector2f(GAME_SCREEN_WIDTH * 0.5f, GAME_SCREEN_HEIGHT * 0.5f - 20.f));
	shopBackgroundOverlay->SetOrigin(Origins::MC);
	shopBackgroundOverlay->SetFillColor(Color(50, 50, 50, 100));
	shopBackgroundOverlay->SetOutline(Color::Black, 4.f);
	shopBackgroundOverlay->SetType("Fixed");

	startPos = { 20.f, GAME_SCREEN_HEIGHT * 0.25f };
	shopIllusts.resize(4);
	for (auto& illu : shopIllusts)
	{
		illu = new SpriteObj();
		illu->SetScale(0.32f, 0.32f);
		illu->SetType("Fixed");
	}
	shopIllusts[0]->SetTexture(*RESOURCE_MGR->GetTexture("graphics/lobyScene/Illust01.png"));
	shopIllusts[0]->SetPos(startPos + Vector2f(75.f, -125.f));
	shopIllusts[1]->SetTexture(*RESOURCE_MGR->GetTexture("graphics/lobyScene/Illust02.png"));
	shopIllusts[1]->SetPos(startPos + Vector2f(200.f, 0.f));
	shopIllusts[2]->SetTexture(*RESOURCE_MGR->GetTexture("graphics/lobyScene/Illust03.png"));
	shopIllusts[2]->SetPos(startPos);
	shopIllusts[3]->SetTexture(*RESOURCE_MGR->GetTexture("graphics/lobyScene/Illust04.png"));
	shopIllusts[3]->SetPos(startPos + Vector2f(75.f, 70.f));

	// barrack tab
	barrackPresetRect.resize(PRESET_SIZE);
	float outlineThickness = -2.f;
	startPos = { GAME_SCREEN_WIDTH * 1.f + TILE_SIZE * 1.75f, TILE_SIZE * 6.75f };
	for (auto& rect : barrackPresetRect)
	{
		rect = new RectangleObj(TILE_SIZE - 1, TILE_SIZE - 1);
		rect->SetFillColor(Color(0, 0, 0, 0));
		rect->SetOutline(Color(255, 255, 255, 100), outlineThickness);
		rect->SetPos(startPos);
		rect->SetOrigin(Origins::BC);
		rect->SetType("Fixed");
		startPos.x += TILE_SIZE * 1.25f;
	}

	heroTabRect.resize(PRESET_SIZE * 3);
	startPos = { GAME_SCREEN_WIDTH * 1.f + TILE_SIZE * 1.75f, TILE_SIZE * 9.f };
	int count = 0;
	for (auto& rect : heroTabRect)
	{
		rect = new RectangleObj(TILE_SIZE - 1, TILE_SIZE - 1);
		rect->SetFillColor(Color(0, 0, 0, 0));
		rect->SetOutline(Color(255, 255, 255, 100), outlineThickness);
		rect->SetPos(startPos);
		rect->SetOrigin(Origins::BC);
		rect->SetType("Fixed");
		startPos.x += TILE_SIZE * 1.25f;
		count++;
		if (count == PRESET_SIZE)
		{
			count = 0;
			startPos.x = GAME_SCREEN_WIDTH * 1.f + TILE_SIZE * 1.75f;
			startPos.y += TILE_SIZE * 1.5f;
		}
	}

	startPos = { GAME_SCREEN_WIDTH * 1.f + TILE_SIZE * 1.f, TILE_SIZE * 7.25f };
	heroTabBackground = new RectangleObj(TILE_SIZE * 7.75f, TILE_SIZE * 5.f);
	heroTabBackground->SetFillColor(Color(70, 70, 70, 200.f));
	heroTabBackground->SetOutline(Color(200, 200, 200, 255.f), 5.f);
	heroTabBackground->SetPos(startPos);
	heroTabBackground->SetType("Fixed");

	// gate tab
	startBtn = new Button();
	startBtn->SetButton(
		*RESOURCE_MGR->GetTexture("graphics/commonUI/Background.png"),
		*RESOURCE_MGR->GetFont("fonts/NANUMBARUNGOTHICBOLD.ttf"), L"전투");

	startBtn->SetPos(Vector2f(GAME_SCREEN_WIDTH * 2.4f, GAME_SCREEN_HEIGHT * 0.75f));
	startBtn->SetTextLocalPos(Vector2f(startBtn->GetTextureRect().width * 0.25f, startBtn->GetTextureRect().height * 0.25f));
	startBtn->SetScale(1.f, 0.75f);
	startBtn->SetTextStyle(Color::White, 25, Color::Black, 2.f);
	startBtn->SetButtonStyle(Color(255, 255, 255, 100), Color(255, 255, 255, 200));
	startBtn->SetType("Fixed");
}

LobySceneUI::~LobySceneUI()
{
	Release();
}

void LobySceneUI::Init()
{
	for (auto button : buttons)
	{
		uiObjList.push_back(button);
	}

	uiObjList.push_back(goldWind);
	uiObjList.push_back(jewelWind);
	uiObjList.push_back(expWind);
	uiObjList.push_back(startBtn);

	uiObjList.push_back(shopBackgroundOverlay);
	for (auto& illu : shopIllusts)
	{
		uiObjList.push_back(illu);
	}

	for (auto& rect : barrackPresetRect)
	{
		uiObjList.push_back(rect);
	}

	uiObjList.push_back(heroTabBackground);
	for (auto& rect : heroTabRect)
	{
		uiObjList.push_back(rect);
	}
	
	UIMgr::Init();
}

void LobySceneUI::Release()
{
	UIMgr::Release();
}

void LobySceneUI::Reset()
{
	UIMgr::Reset();

	preset.resize(PRESET_SIZE);
	gatePreset.resize(PRESET_SIZE);
	heroTab.resize(PRESET_SIZE * 3);
}

void LobySceneUI::Update(float dt)
{
	UIMgr::Update(dt);
}

void LobySceneUI::Draw(RenderWindow& window)
{
	UIMgr::Draw(window);
}

void LobySceneUI::SetPos(const Vector2f& pos)
{
	UIMgr::SetPos(pos);
}

void LobySceneUI::SetOrigin(Origins origin)
{
}