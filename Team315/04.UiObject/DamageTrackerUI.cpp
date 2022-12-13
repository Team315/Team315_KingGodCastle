#include "DamageTrackerUI.h"
#include "BackrectText.h"
#include "Include.h"
#include "TrackerProfile.h"
#include "DataTableMgr.h"
#include "StringTable.h"

DamageTrackerUI::DamageTrackerUI(float x, float y)
	: RectangleObj(x, y), show(false)
{
	SetFillColor(Color(0x0a, 0x0a, 0x0a, 100.f));
	SetName("TrackerBg");
	
	onoff = new BackrectText(30.f, 60.f);
	onoff->SetFillColor(Color(0x0a, 0x0a, 0x0a, 100.f));
	onoff->SetName("OnOff");
	onoff->SetFont(*RESOURCE_MGR->GetFont("fonts/GodoB.ttf"));
	onoff->SetString("<");
	onoff->SetTextStyle(Color::White, 20.f, Color::Black, 1.f);
	onoff->SetTextLocalPos(Vector2f(5.f, 20.f));

	selectGiven = new BackrectText(75.f, 30.f);
	selectGiven->SetFillColor(Color(0x0f, 0x0f, 0x0f, 150.f));
	selectGiven->SetName("Given");
	selectGiven->SetFont(*RESOURCE_MGR->GetFont("fonts/GodoB.ttf"));
	selectGiven->SetString(STRING_TABLE->Get("GetDamage"));
	selectGiven->SetTextStyle(Color::White, 10.f, Color::Black, 1.f);
	selectGiven->SetTextLocalPos(Vector2f(10.f, 10.f));

	selectTaken = new BackrectText(75.f, 30.f);
	selectTaken->SetFillColor(Color(0x0a, 0x0a, 0x0a, 100.f));
	selectTaken->SetName("Taken");
	selectTaken->SetFont(*RESOURCE_MGR->GetFont("fonts/GodoB.ttf"));
	selectTaken->SetString(STRING_TABLE->Get("TakeDamage"));
	selectTaken->SetTextStyle(Color::White, 10.f, Color::Black, 1.f);
	selectTaken->SetTextLocalPos(Vector2f(10.f, 10.f));

	buttons.push_back(onoff);
	buttons.push_back(selectGiven);
	buttons.push_back(selectTaken);
}

DamageTrackerUI::~DamageTrackerUI()
{
}

void DamageTrackerUI::Init()
{
	SetHitbox(FloatRect(0, 0, 150, 200), Origins::TL);
	onoff->SetHitbox(FloatRect(0, 0, 30, 50), Origins::TL);
	selectGiven->SetHitbox(FloatRect(0, 0, 75, 30), Origins::TL);
	selectTaken->SetHitbox(FloatRect(0, 0, 75, 30), Origins::TL);
	Object::Init();
	onoff->Init();
	selectGiven->Init();
	selectTaken->Init();

	profiles.Init(10);

	tracker = GAME_MGR->GetBattleTracker();
}

void DamageTrackerUI::Update(float dt)
{
	auto& profileUse = profiles.GetUseList();
	
	float maxTotal = 0.f;
	for (auto& profile : profileUse)
	{
		DamageData* data = profile->GetData();
		if (GAME_MGR->GetBattleTracker()->GetTrackerMode())
		{
			float sum = data->givenAD + data->givenAP;
			if (maxTotal < sum)
				maxTotal = sum;
		}
		else
		{
			float sum = data->takenAD + data->takenAP;
			if (maxTotal < sum)
				maxTotal = sum;
		}
	}

	for (auto& profile : profileUse)
	{
		profile->SetMaxTotal(maxTotal);
		profile->Update(dt);
	}
}

void DamageTrackerUI::Draw(RenderWindow& window)
{
	RectangleObj::Draw(window);
	onoff->Draw(window);
	selectGiven->Draw(window);
	selectTaken->Draw(window);
	
	auto& profileUse = profiles.GetUseList();
	for (auto& profile : profileUse)
	{
		profile->Draw(window);
	}
}

void DamageTrackerUI::SetPos(const Vector2f& pos)
{
	RectangleObj::SetPos(pos);
	onoff->SetPos(pos + Vector2f(-30.f, -30.f));
	selectGiven->SetPos(pos + Vector2f(0.f, -30.f));
	selectTaken->SetPos(pos + Vector2f(75.f, -30.f));
	ProfileSetPos();
}

void DamageTrackerUI::ShowWindow()
{
	show = !show;
	ShowWindow(show);
}

void DamageTrackerUI::ShowWindow(bool value)
{
	show = value;

	if (show)
	{
		SetPos(Vector2f(350.f, 200.f));
		onoff->SetString(">");
	}
	else
	{
		SetPos(Vector2f(500.f, 200.f));
		onoff->SetString("<");
	}
	TrackerUpdate();
}

void DamageTrackerUI::ShowGiven()
{
	selectGiven->SetFillColor(Color(0x0f, 0x0f, 0x0f, 150.f));
	selectTaken->SetFillColor(Color(0x0a, 0x0a, 0x0a, 100.f));
	GAME_MGR->GetBattleTracker()->SetTrackerMode(true);
	TrackerUpdate();
}

void DamageTrackerUI::ShowTaken()
{
	selectTaken->SetFillColor(Color(0x0f, 0x0f, 0x0f, 150.f));
	selectGiven->SetFillColor(Color(0x0a, 0x0a, 0x0a, 100.f));
	GAME_MGR->GetBattleTracker()->SetTrackerMode(false);
	TrackerUpdate();
}

void DamageTrackerUI::ProfileSetPos()
{
	auto& profileUse = profiles.GetUseList();
	Vector2f start = position;
	Vector2f delta(5, 5);
	for (auto& profile : profileUse)
	{
		profile->SetPos(start + delta);
		delta.y += 55.f;
	}
}

void DamageTrackerUI::ProfilesReturn()
{
	profiles.Reset();
}

void DamageTrackerUI::TrackerUpdate()
{
	profiles.Reset();
	auto datas = tracker->GetDatas();
	for (auto& data : *datas)
	{
		auto profile = profiles.Get();
		profile->SetSource(&data);
		profile->Parse();
		profile->SetMode(GAME_MGR->GetBattleTracker()->GetTrackerMode());
	}
	ProfileSetPos();
}