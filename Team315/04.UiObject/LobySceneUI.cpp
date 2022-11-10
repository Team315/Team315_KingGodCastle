#include "LobySceneUI.h"
#include "Include.h"
#include "Constant.h"

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
		button->SetButtonSpriteSpacing(15.f, 10.f);

	// top resources
	float blockLength = GAME_SCREEN_WIDTH / gameResourceCount;
	float padding = blockLength * 0.05f;

	vector<string> table(gameResourceCount);
	table[0] = "graphics/mainScene/Icon_Level.png";
	table[1] = "graphics/mainScene/Icon_Jewelry.png";
	table[2] = "graphics/mainScene/Icon_Gold.png";

	Vector2f topResourcePos(padding * 2, 30.f);
	for (int i = 0; i < gameResourceCount; i++)
	{
		RectangleObj* backSprite = new RectangleObj(blockLength - padding * 2, 40);
		backSprite->SetFillColor(Color(0, 0, 0, 100));
		backSprite->SetOutline(Color::Black, 2.f);
		SpriteObj* resourceSprite = new SpriteObj();
		resourceSprite->SetTexture(*RESOURCE_MGR->GetTexture(table[i]));
		GameResources* gameResource = new GameResources(backSprite, resourceSprite);
		gameResource->SetPos(topResourcePos);
		topResourcePos.x += blockLength - padding;

		gameResources.push_back(gameResource);
	}
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
		pos.x += buttonSize + 5.f;
		uiObjList.push_back(button);
	}

	for (auto gameResource : gameResources)
	{
		uiObjList.push_back(gameResource->backSprite);
		uiObjList.push_back(gameResource->resourceSprite);
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
}

void LobySceneUI::Update(float dt)
{
	UIMgr::Update(dt);
}

void LobySceneUI::Draw(RenderWindow& window)
{
	UIMgr::Draw(window);
}