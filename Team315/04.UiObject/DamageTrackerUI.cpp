#include "DamageTrackerUI.h"
#include "BackrectText.h"
#include "Include.h"

DamageTrackerUI::DamageTrackerUI(float x, float y)
	: RectangleObj(x, y), show(false), givenOrTaken(true)
{
	SetFillColor(Color(0x0a, 0x0a, 0x0a, 100.f));
	SetName("TrackerBg");
	
	onoff = new BackrectText(20.f, 40.f);
	onoff->SetFillColor(Color(0x0a, 0x0a, 0x0a, 100.f));
	onoff->SetName("OnOff");
	onoff->SetFont(*RESOURCE_MGR->GetFont("fonts/GodoB.ttf"));
	onoff->SetString(">");
	onoff->SetTextStyle(Color::White, 18.f, Color::Black, 1.f);
	onoff->SetTextLocalPos(Vector2f(3.f, 10.f));

	selectGiven = new BackrectText(50.f, 20.f);
	selectGiven->SetFillColor(Color(0x0f, 0x0f, 0x0f, 150.f));
	selectGiven->SetName("Given");
	selectGiven->SetFont(*RESOURCE_MGR->GetFont("fonts/GodoB.ttf"));
	selectGiven->SetString(L"가한 피해량");
	selectGiven->SetTextStyle(Color::White, 10.f, Color::Black, 1.f);
	selectGiven->SetTextLocalPos(Vector2f(2.f, 0.f));

	selectTaken = new BackrectText(50.f, 20.f);
	selectTaken->SetFillColor(Color(0x0a, 0x0a, 0x0a, 100.f));
	selectTaken->SetName("Taken");
	selectTaken->SetFont(*RESOURCE_MGR->GetFont("fonts/GodoB.ttf"));
	selectTaken->SetString(L"받은 피해량");
	selectTaken->SetTextStyle(Color::White, 10.f, Color::Black, 1.f);
	selectTaken->SetTextLocalPos(Vector2f(2.f, 0.f));

	buttons.push_back(onoff);
	buttons.push_back(selectGiven);
	buttons.push_back(selectTaken);
}

DamageTrackerUI::~DamageTrackerUI()
{
}

void DamageTrackerUI::Init()
{
	SetHitbox(FloatRect(0, 0, 100, 200), Origins::TL);
	onoff->SetHitbox(FloatRect(0, 0, 20, 40), Origins::TL);
	selectGiven->SetHitbox(FloatRect(0, 0, 50, 20), Origins::TL);
	selectTaken->SetHitbox(FloatRect(0, 0, 50, 20), Origins::TL);
	Object::Init();
	onoff->Init();
	selectGiven->Init();
	selectTaken->Init();
}

void DamageTrackerUI::Draw(RenderWindow& window)
{
	RectangleObj::Draw(window);
	onoff->Draw(window);
	selectGiven->Draw(window);
	selectTaken->Draw(window);
}

void DamageTrackerUI::SetPos(const Vector2f& pos)
{
	RectangleObj::SetPos(pos);
	onoff->SetPos(pos + Vector2f(-20.f, -20.f));
	selectGiven->SetPos(pos + Vector2f(0.f, -20.f));
	selectTaken->SetPos(pos + Vector2f(50.f, -20.f));
}

void DamageTrackerUI::ShowWindow()
{
	show = !show;

	if (show)
	{
		Translate(Vector2f(100.f, 0.f));
		onoff->SetString("<");
	}
	else
	{
		Translate(Vector2f(-100.f, 0.f));
		onoff->SetString(">");
	}
}

void DamageTrackerUI::ShowGiven()
{
	selectGiven->SetFillColor(Color(0x0f, 0x0f, 0x0f, 150.f));
	selectTaken->SetFillColor(Color(0x0a, 0x0a, 0x0a, 100.f));
	givenOrTaken = true;
}

void DamageTrackerUI::ShowTaken()
{
	selectTaken->SetFillColor(Color(0x0f, 0x0f, 0x0f, 150.f));
	selectGiven->SetFillColor(Color(0x0a, 0x0a, 0x0a, 100.f));
	givenOrTaken = false;
}