#include "StatPopupWindow.h"
#include "ProgressBar.h"
#include "BackrectText.h"
#include "BackgroundText.h"
#include "Include.h"

StatPopupWindow::StatPopupWindow(float x, float y)
	: RectangleObj(x, y), useOptional(false)
{
	nameText = new BackrectText();
	nameText->SetFont(*RESOURCE_MGR->GetFont("fonts/GodoB.ttf"));
	nameText->SetTextStyle(Color::White, 20, Color::Black, -1.f);

	starText = new BackgroundText();
	starText->SetFont(*RESOURCE_MGR->GetFont("fonts/GodoB.ttf"));
	starText->SetTextStyle(Color::White, 25, Color::Black, -1.f);
	//starText->SetTexture();
	
	portraitRect.setSize(Vector2f(90.f, 90.f));
	portraitRect.setOutlineColor(Color(150, 150, 150, 255));
	portraitRect.setOutlineThickness(-2.f);

	adImg.setTexture(*RESOURCE_MGR->GetTexture("graphics/Charactor/Stat/StatIcon_01.png"));
	apImg.setTexture(*RESOURCE_MGR->GetTexture("graphics/Charactor/Stat/StatIcon_02.png"));
	asImg.setTexture(*RESOURCE_MGR->GetTexture("graphics/Charactor/Stat/StatIcon_03.png"));
	
	adImg.setScale(0.5f, 0.5f);
	apImg.setScale(0.5f, 0.5f);
	asImg.setScale(0.5f, 0.5f);

	hpBar = new ProgressBar(180.f, 15.f);
	hpBar->SetProgressColor(Color::Green);
	hpBar->SetBackgroundColor(Color(0, 0, 0, 100));
	hpBar->SetBackgroundOutline(Color::Black, -2.f);
	hpBar->SetProgressValue(1.f);

	currentHp.setFont(*RESOURCE_MGR->GetFont("fonts/GodoB.ttf"));
	currentHp.setString("hp string");
	currentHp.setFillColor(Color::Green);
	currentHp.setCharacterSize(10);
	currentHp.setOutlineColor(Color::Black);
	currentHp.setOutlineThickness(1.f);
	

	//mpBar = new ProgressBar();
}

StatPopupWindow::~StatPopupWindow()
{
}

void StatPopupWindow::Draw(RenderWindow& window)
{
	RectangleObj::Draw(window);
	window.draw(portraitRect);
	window.draw(portrait);
	window.draw(adImg);
	window.draw(apImg);
	window.draw(asImg);
	hpBar->Draw(window);
	window.draw(currentHp);
}

void StatPopupWindow::SetPos(const Vector2f& pos)
{
	RectangleObj::SetPos(pos);
	portraitRect.setPosition(pos + Vector2f(5.f, 35.f));
	portrait.setPosition(pos + Vector2f(5.f, 35.f));
	adImg.setPosition(pos + Vector2f(100.f, 35.f));
	apImg.setPosition(pos + Vector2f(100.f, 70.f));
	asImg.setPosition(pos + Vector2f(100.f, 105.f));
	hpBar->SetPos(pos + Vector2f(10.f, 130.f));
	currentHp.setPosition(pos + Vector2f(100.f, 142.f));
	
	Utils::SetOrigin(currentHp, Origins::BC);
}

void StatPopupWindow::SetOrigin(Origins origin)
{
	RectangleObj::SetOrigin(origin);
}