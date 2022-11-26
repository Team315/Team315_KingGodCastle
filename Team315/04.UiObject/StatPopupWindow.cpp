#include "StatPopupWindow.h"
#include "BackrectText.h"
#include "BackgroundText.h"
#include "Character.h"
#include "ProgressBar.h"
#include "Include.h"

StatPopupWindow::StatPopupWindow(float x, float y)
	: RectangleObj(x, y), useOptional(false)
{
	nameText = new BackrectText(160, 30);
	nameText->SetFont(*RESOURCE_MGR->GetFont("fonts/GodoB.ttf"));
	nameText->SetTextStyle(Color::White, 22, Color::Black, 2.f);
	nameText->SetFillColor(Color(0x1B, 0x1B, 0x1B));
	nameText->GetText().setString("name");
	nameText->SetTextLocalPos(Vector2f(10.f, 2.f));
	nameText->SetOutline(Color::Black, 1.f);

	starText = new BackgroundText();
	starText->SetFont(*RESOURCE_MGR->GetFont("fonts/GodoB.ttf"));
	starText->SetTextStyle(Color::White, 22, Color::Black, 2.f);
	starText->SetTexture(*RESOURCE_MGR->GetTexture("graphics/commonUI/Level_Frame_02.png"));
	starText->SetScale(0.4f, 0.4f);

	portraitRect.setSize(Vector2f(90.f, 90.f));
	portraitRect.setOutlineColor(Color::Black);
	portraitRect.setOutlineThickness(-2.f);
	portraitRect.setFillColor(Color(0x5B, 0x5B, 0x5B));
	
	adText = new BackrectText(95, 25);
	adText->SetFont(*RESOURCE_MGR->GetFont("fonts/GodoB.ttf"));
	adText->SetTextLocalPos(Vector2f(25.f, 3.f));
	adText->GetText().setString("ad");
	adText->SetTextStyle(Color::White, 15, Color::Black, 2.f);
	adText->SetFillColor(Color(0x1B, 0x1B, 0x1B));
	adText->SetOutline(Color::Black, 1.f);

	apText = new BackrectText(95, 25);
	apText->SetFont(*RESOURCE_MGR->GetFont("fonts/GodoB.ttf"));
	apText->SetTextLocalPos(Vector2f(25.f, 3.f));
	apText->GetText().setString("ap");
	apText->SetTextStyle(Color::White, 15, Color::Black, 2.f);
	apText->SetFillColor(Color(0x1B, 0x1B, 0x1B));
	apText->SetOutline(Color::Black, 1.f);
	
	asText = new BackrectText(95, 25);
	asText->SetFont(*RESOURCE_MGR->GetFont("fonts/GodoB.ttf"));
	asText->SetTextLocalPos(Vector2f(25.f, 3.f));
	asText->GetText().setString("as");
	asText->SetTextStyle(Color::White, 15, Color::Black, 2.f);
	asText->SetFillColor(Color(0x1B, 0x1B, 0x1B));
	asText->SetOutline(Color::Black, 1.f);

	adImg.setTexture(*RESOURCE_MGR->GetTexture("graphics/Charactor/Stat/StatIcon_01.png"));
	apImg.setTexture(*RESOURCE_MGR->GetTexture("graphics/Charactor/Stat/StatIcon_02.png"));
	asImg.setTexture(*RESOURCE_MGR->GetTexture("graphics/Charactor/Stat/StatIcon_03.png"));
	
	adImg.setScale(0.5f, 0.5f);
	apImg.setScale(0.5f, 0.5f);
	asImg.setScale(0.5f, 0.5f);

	hpBar = new ProgressBar(190.f, 11.f);
	hpBar->SetProgressColor(Color::Green);
	hpBar->SetBackgroundColor(Color(0x1B, 0x1B, 0x1B));
	hpBar->SetBackgroundOutline(Color::Black, 1.f);

	currentHp.setFont(*RESOURCE_MGR->GetFont("fonts/GodoB.ttf"));
	currentHp.setString("hp string");
	currentHp.setFillColor(Color::Green);
	currentHp.setCharacterSize(12);
	currentHp.setOutlineColor(Color::Black);
	currentHp.setOutlineThickness(1.f);
	
	//mpBar = new ProgressBar();
}

StatPopupWindow::~StatPopupWindow()
{
}

void StatPopupWindow::Update(float dt)
{
	hpBar->Update(dt);
}

void StatPopupWindow::Draw(RenderWindow& window)
{
	RectangleObj::Draw(window);
	nameText->Draw(window);
	starText->Draw(window);
	window.draw(portraitRect);
	adText->Draw(window);
	apText->Draw(window);
	asText->Draw(window);
	window.draw(adImg);
	window.draw(apImg);
	window.draw(asImg);
	hpBar->Draw(window);
	window.draw(currentHp);
	window.draw(portrait);
}

void StatPopupWindow::SetPos(const Vector2f& pos)
{
	RectangleObj::SetPos(pos);
	nameText->SetPos(pos + Vector2f(35.f, 5.f));
	starText->SetPos(pos + Vector2f(20.f, 5.f));
	portraitRect.setPosition(pos + Vector2f(5.f, 40.f));
	portrait.setPosition(pos + Vector2f(50.f, 130.f));
	Utils::SetOrigin(portrait, Origins::BC);
	adText->SetPos(pos + Vector2f(100.f, 40.f));
	apText->SetPos(pos + Vector2f(100.f, 70.f));
	asText->SetPos(pos + Vector2f(100.f, 100.f));
	adImg.setPosition(pos + Vector2f(100.f, 40.f));
	apImg.setPosition(pos + Vector2f(100.f, 70.f));
	asImg.setPosition(pos + Vector2f(100.f, 100.f));
	hpBar->SetPos(pos + Vector2f(5.f, 135.f));
	currentHp.setPosition(pos + Vector2f(100.f, 143.5f));
	Utils::SetOrigin(currentHp, Origins::BC);
}

void StatPopupWindow::SetOrigin(Origins origin)
{
	RectangleObj::SetOrigin(origin);
}

void StatPopupWindow::SetCharacter(Character* character)
{
	string texPath = "graphics/Charactor/Portrait/Portrait_" + character->GetName() + ".png";
	portrait.setTexture(*RESOURCE_MGR->GetTexture(texPath), true);
	FloatRect fr = (FloatRect)portrait.getTextureRect();
	float width = 90 / fr.width;
	float height = 90 / fr.height;
	float min = width > height ? height : width;
	portrait.setScale(min, min);
	nameText->SetString(character->GetName());
	starText->SetString(to_string(character->GetStarNumber()));
	starText->SetOrigin(Origins::TC);
	adText->SetString(character->GetStat(Stats::AD).GetModifier(), true);
	apText->SetString(character->GetStat(Stats::AP).GetModifier(), true);
	string asStr = to_string(character->GetStat(Stats::AS).GetModifier()).substr(0, 4);
	asText->SetString(asStr);
	currentHp.setString(to_string((int)character->GetStat(Stats::HP).GetCurrent()));
	hpBar->SetProgressValue(character->GetStat(Stats::HP).GetCurRatio());
}