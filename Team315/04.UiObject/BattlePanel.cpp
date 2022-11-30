#include "BattlePanel.h"
#include "Button.h"
#include "TextObj.h"
#include "BackrectText.h"
#include "Include.h"

BattlePanel::BattlePanel()
{
	SetTexture(RESOURCE_MGR->GetTexture("graphics/battleScene/Table.png"));
	
	paper = new SpriteObj();
	paper->SetTexture(*RESOURCE_MGR->GetTexture("graphics/battleScene/paper.png"));
	paperLocalPos = Vector2f(15.f, 0);
	paper->SetScale(0.8f, 0.57f); // 480 x 200

	titleBackground.setTexture(*RESOURCE_MGR->GetTexture("graphics/battleScene/title.png"));
	titlebgLocalPos = Vector2f((GAME_SCREEN_WIDTH - titleBackground.getTextureRect().width) * 0.5f, 30.f);

	bottomGradiant.setTexture(*RESOURCE_MGR->GetTexture("graphics/commonUI/BotGradiant.png"));
	gradiantLocalPos = Vector2f(0, 85.f);

	Vector2f textLocalPos(15.f, 30.f); 
	summon = new Button();
	summon->SetButton(*RESOURCE_MGR->GetTexture("graphics/battleScene/Button_01.png"),
		*RESOURCE_MGR->GetFont("fonts/GodoB.ttf"), L"영웅소환",
		textLocalPos.x, textLocalPos.y);
	summon->SetTextStyle(Color::White, 20, Color::Black, 1.f);
	summonLocalPos = Vector2f(GAME_SCREEN_WIDTH * 0.05f, 200.f);
	summon->SetName("summon");

	begin = new Button();
	begin->SetButton(*RESOURCE_MGR->GetTexture("graphics/battleScene/Start.png"),
		*RESOURCE_MGR->GetFont("fonts/GodoB.ttf"), L"전투개시",
		textLocalPos.x + 20.f, textLocalPos.y + 30.f);
	begin->SetTextStyle(Color::White, 20, Color::Black, 1.f);
	beginLocalPos = Vector2f((GAME_SCREEN_WIDTH - begin->GetSize().x) * 0.5f, 180.f);
	begin->SetName("begin");

	equipment = new Button();
	equipment->SetButton(*RESOURCE_MGR->GetTexture("graphics/battleScene/Button_02.png"),
		*RESOURCE_MGR->GetFont("fonts/GodoB.ttf"), L"장비구입",
		textLocalPos.x, textLocalPos.y);
	equipment->SetTextStyle(Color::White, 20, Color::Black, 1.f);
	expansionLocalPos = Vector2f(GAME_SCREEN_WIDTH * 0.75f, 200.f);
	equipment->SetName("equipment");

	titleText = new TextObj(*RESOURCE_MGR->GetFont("fonts/GodoB.ttf"),
		L"고블린 습격!     번째 침략",
		titlebgLocalPos.x, titlebgLocalPos.y, Color(153.f, 136.f, 126.f), 20.f);
	titleText->SetOutlineColor(Color::Black);
	titleText->SetOutlineThickness(1.f);
	titleTextLocalPos = titlebgLocalPos + Vector2f(95.f, 15.f);

	titleNumberText = new TextObj(*RESOURCE_MGR->GetFont("fonts/GodoB.ttf"), "1",
		titlebgLocalPos.x, titlebgLocalPos.y, Color(189.f, 172.f, 146.f), 22.f);
	titleNumberText->SetOutlineColor(Color::Black);
	titleNumberText->SetOutlineThickness(1.f);
	dnmTitleTextLocalPos = titleTextLocalPos + Vector2f(120.f, -2.f);

	stageText = new TextObj(*RESOURCE_MGR->GetFont("fonts/GodoB.ttf"),
		L"1/10", beginLocalPos.x, beginLocalPos.y, Color::White, 18.f);
	stageText->SetOutlineColor(Color::Black);
	stageText->SetOutlineThickness(1.f);
	stageTextLocalPos = beginLocalPos + Vector2f(50.f, 40.f);

	coinSprite.setTexture(*RESOURCE_MGR->GetTexture("graphics/battleScene/coin_01.png"));

	coinState = new BackrectText(70.f, 30.f);
	coinState->SetFont(*RESOURCE_MGR->GetFont("fonts/GodoB.ttf"));
	coinState->SetString(to_string(GAME_MGR->GetCurrentCoin()));
	coinState->SetTextStyle(Color::White, 20, Color::Black, 2.f);
	coinState->SetFillColor(Color(0x1B, 0x1B, 0x1B, 180.f));
	coinState->SetTextLocalPos(Vector2f(25.f, 4.f));
	coinState->SetOutline(Color::Black, 1.f);
	coinLocalPos = Vector2f((GAME_SCREEN_WIDTH - coinState->GetSize().x) * 0.5f, 150.f);

	buttons.push_back(summon);
	buttons.push_back(begin);
	buttons.push_back(equipment);
}

BattlePanel::~BattlePanel()
{
}

void BattlePanel::Draw(RenderWindow& window)
{
	VertexArrayObj::Draw(window);
	paper->Draw(window);
	window.draw(titleBackground);
	window.draw(bottomGradiant);
	summon->Draw(window);
	begin->Draw(window);
	equipment->Draw(window);
	titleText->Draw(window);
	stageText->Draw(window);
	titleNumberText->Draw(window);
	coinState->Draw(window);
	window.draw(coinSprite);
}

void BattlePanel::SetPos(const Vector2f& pos)
{
	VertexArrayObj::SetPos(pos);
	paper->SetPos(position + paperLocalPos);
	titleBackground.setPosition(position + titlebgLocalPos);
	bottomGradiant.setPosition(position + gradiantLocalPos);
	summon->SetPos(position + summonLocalPos);
	begin->SetPos(position + beginLocalPos);
	equipment->SetPos(position + expansionLocalPos);
	titleText->SetPos(position + titleTextLocalPos);
	stageText->SetPos(position + stageTextLocalPos);
	titleNumberText->SetPos(position + dnmTitleTextLocalPos);
	coinSprite.setScale(2.f, 2.f);
	coinSprite.setPosition(position + coinLocalPos + Vector2f(-coinSprite.getTextureRect().width * 0.75f, 5.f));
	coinState->SetPos(position + coinLocalPos);
}

void BattlePanel::SetStageNumber(int num)
{
	titleNumberText->SetString(to_string(num));
}

void BattlePanel::SetCurrentCoin(int num)
{
	coinState->SetString(to_string(num));
}