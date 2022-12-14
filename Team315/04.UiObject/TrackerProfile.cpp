#include "TrackerProfile.h"
#include "TwoFactorProgress.h"
#include "Include.h"
#include "Character.h"

TrackerProfile::TrackerProfile(float x, float y)
	: RectangleObj(x, y), givenOrTaken(true)
{
	shape.setFillColor(Color(0x1a, 0x1a, 0x1a, 150.f));

	characterName.setFont(*RESOURCE_MGR->GetFont("fonts/GodoB.ttf"));
	characterName.setCharacterSize(10.f);
	characterName.setFillColor(Color::White);
	characterName.setOutlineColor(Color::Black);
	characterName.setOutlineThickness(-1.f);
	characterName.setString("name");

	quantity.setFont(*RESOURCE_MGR->GetFont("fonts/GodoB.ttf"));
	quantity.setCharacterSize(10.f);
	quantity.setFillColor(Color::White);
	quantity.setOutlineColor(Color::Black);
	quantity.setOutlineThickness(-1.f);
	quantity.setString("number");

	bar = new TwoFactorProgress(80.f, 12.f);
	bar->SetBackgroundOutline(Color::Black, 1.f);
	bar->SetBackgroundColor(Color::Black);
	bar->SetProgressColor(Color(200.f, 0.f, 0.f));
	bar->SetSecondProgressColor(Color(0.f, 0.f, 200.f));
}

TrackerProfile::~TrackerProfile()
{
}

void TrackerProfile::Update(float dt)
{
	bar->Update(dt);
	
	if (givenOrTaken)
	{
		bar->SetRatio(maxTotal, data->givenAD, data->givenAP);
		int sum = data->givenAD + data->givenAP;
		quantity.setString(to_string(sum));
	}
	else
	{
		bar->SetRatio(maxTotal, data->takenAD, data->takenAP);
		int sum = data->takenAD + data->takenAP;
		quantity.setString(to_string(sum));
	}
}

void TrackerProfile::Draw(RenderWindow& window)
{
	RectangleObj::Draw(window);
	window.draw(characterName);
	window.draw(quantity);
	window.draw(portrait);
	window.draw(star);
	bar->Draw(window);
}

void TrackerProfile::SetPos(const Vector2f& pos)
{
	RectangleObj::SetPos(pos);
	portrait.setPosition(pos + Vector2f(25.f, 45.f));
	star.setPosition(pos + Vector2f(25.f, 45.f));
	characterName.setPosition(pos + Vector2f(55.f, 5.f));
	quantity.setPosition(pos + Vector2f(55.f, 17.f));
	bar->SetPos(pos + Vector2f(55.f, 32.f));
}

void TrackerProfile::SetSource(DamageData* data)
{
	this->data = data;
}

void TrackerProfile::Parse()
{
	string portraitPath = "graphics/Character/Portrait/Portrait_";
	string starPath = "graphics/commonUI/Level_Star_";
	string ext = ".png";
	
	portraitPath += (data->character->GetName() + ext);
	starPath += (to_string(data->character->GetStarNumber()) + ext);

	portrait.setTexture(*RESOURCE_MGR->GetTexture(portraitPath), true);
	float min = Utils::GetMinScaleRatioFromFloatRect(
		40.f, 40.f, (FloatRect)portrait.getTextureRect());
	portrait.setScale(min, min);
	Utils::SetOrigin(portrait, Origins::BC);

	star.setTexture(*RESOURCE_MGR->GetTexture(starPath), true);
	star.setScale(0.5f, 0.5f);
	Utils::SetOrigin(star, Origins::BC);

	characterName.setString(data->character->GetName());
}

DamageData* TrackerProfile::GetData()
{
	return data;
}