#include "Altar.h"

Altar::Altar(Vector2f mainPos, int index)
	:m_Index(index)
{
	string background = "graphics/Altar/Altar_0" + to_string(index) + ".png";
	SetTexture(*RESOURCE_MGR->GetTexture(background));
	SetScale(0.5f, 0.5f);
	SetPos(mainPos);
	SetOrigin(Origins::TL);

	Vector2f altarEffectPos = { 26.f,38.f };
	string Effect = "graphics/Altar/Altar_Effect_0" + to_string(index) + ".png";
	m_altarEffect.SetTexture(*RESOURCE_MGR->GetTexture(Effect));
	m_altarEffect.SetScale(0.5f, 0.5f);
	m_altarEffect.SetPos(mainPos+ altarEffectPos);
	m_altarEffect.SetOrigin(Origins::TL);

	Vector2f altarLightPos = { 20.f,24.f };
	string Light = "graphics/Altar/Altar_Light_0" + to_string(index) + ".png";
	m_altarLight.SetTexture(*RESOURCE_MGR->GetTexture(Light));
	m_altarLight.SetScale(0.5f, 0.5f);
	m_altarLight.SetPos(mainPos + altarLightPos);
	m_altarLight.SetOrigin(Origins::TL);
	SetRomaNumber(mainPos, index);
	SetDot(mainPos, index);

	Vector2f numberPos = { 59.f,19.f };
	m_number.SetFont(*RESOURCE_MGR->GetFont("fonts/GodoB.ttf"));
	m_number.SetString("15");
	m_number.SetColor({ 254,113,235,255 });
	m_number.SetOutlineThickness(2.f);
	m_number.SetOutlineColor({ 254,113,235,100 });
	m_number.SetCharacterSize(15);
	m_number.SetPos(mainPos + numberPos);
	m_number.SetOrigin(Origins::MC);

	Vector2f altarNamePos = { 59.f,19.f };
	m_altarName.SetFont(*RESOURCE_MGR->GetFont("fonts/GodoB.ttf"));
	m_altarName.SetString("15");
	m_altarName.SetColor({ 254,113,235,255 });
	m_altarName.SetOutlineThickness(1.f);
	m_altarName.SetOutlineColor(Color::Black);
	m_altarName.SetCharacterSize(15);
	m_altarName.SetPos(mainPos + altarNamePos);
	m_altarName.SetOrigin(Origins::MC);


}

Altar::~Altar()
{

}

void Altar::Init()
{

}

void Altar::Release()
{

}

void Altar::Update(float dt)
{
	SpriteObj::Update(dt);
}

void Altar::Draw(RenderWindow& window)
{
	SpriteObj::Draw(window);
	m_altarEffect.Draw(window);
	m_altarLight.Draw(window);

	m_romaNum01.Draw(window);

	m_romaNum02.Draw(window);
	m_romaNum03.Draw(window);
	m_romaNum04.Draw(window);

	m_romaNum05.Draw(window);

	m_romaNum06.Draw(window);
	m_romaNum07.Draw(window);
	m_romaNum08.Draw(window);
	m_romaNum09.Draw(window);

	m_romaNum10.Draw(window);

	m_romaNum11.Draw(window);
	m_romaNum12.Draw(window);
	m_romaNum13.Draw(window);
	m_romaNum14.Draw(window);

	m_romaNum15.Draw(window);

	m_number.Draw(window);

	m_altarName.Draw(window);

}

void Altar::MoveSetPos(Vector2f movepos)
{
	//SetPos(GetPos() + movepos);
	m_altarName.SetPos(movepos);
}

void Altar::SetRomaNumber(Vector2f mainPos, int index)
{
	Vector2f romaNum01Pos = { 7.f,128.f };
	string romaNum01 = "graphics/Altar/Altar_RomaNum0" + to_string(index) + "_01.png";
	m_romaNum01.SetTexture(*RESOURCE_MGR->GetTexture(romaNum01));
	m_romaNum01.SetScale(0.5f, 0.5f);
	m_romaNum01.SetPos(mainPos + romaNum01Pos);
	m_romaNum01.SetOrigin(Origins::TL);

	Vector2f romaNum05Pos = { 5.f,50.f };
	string romaNum05 = "graphics/Altar/Altar_RomaNum0" + to_string(index) + "_05.png";
	m_romaNum05.SetTexture(*RESOURCE_MGR->GetTexture(romaNum05));
	m_romaNum05.SetScale(0.5f, 0.5f);
	m_romaNum05.SetPos(mainPos + romaNum05Pos);
	m_romaNum05.SetOrigin(Origins::TL);

	Vector2f romaNum10Pos = { 89.f,50.f };
	string romaNum10 = "graphics/Altar/Altar_RomaNum0" + to_string(index) + "_10.png";
	m_romaNum10.SetTexture(*RESOURCE_MGR->GetTexture(romaNum10));
	m_romaNum10.SetScale(0.5f, 0.5f);
	m_romaNum10.SetPos(mainPos + romaNum10Pos);
	m_romaNum10.SetOrigin(Origins::TL);

	Vector2f romaNum15Pos = { 89.f,128.f };
	string romaNum15 = "graphics/Altar/Altar_RomaNum0" + to_string(index) + "_15.png";
	m_romaNum15.SetTexture(*RESOURCE_MGR->GetTexture(romaNum15));
	m_romaNum15.SetScale(0.5f, 0.5f);
	m_romaNum15.SetPos(mainPos + romaNum15Pos);
	m_romaNum15.SetOrigin(Origins::TL);
}

void Altar::SetDot(Vector2f mainPos, int index)
{
	Vector2f vdot02 = { 9.f,110.f };
	string dot02 = "graphics/Altar/Altar_Point_0" + to_string(index) + ".png";
	m_romaNum02.SetTexture(*RESOURCE_MGR->GetTexture(dot02));
	m_romaNum02.SetScale(0.6f, 0.6f);
	m_romaNum02.SetPos(mainPos + vdot02);
	m_romaNum02.SetOrigin(Origins::TL);

	Vector2f vdot03 = { 9.f,92.f };
	string dot03 = "graphics/Altar/Altar_Point_0" + to_string(index) + ".png";
	m_romaNum03.SetTexture(*RESOURCE_MGR->GetTexture(dot03));
	m_romaNum03.SetScale(0.6f, 0.6f);
	m_romaNum03.SetPos(mainPos + vdot03);
	m_romaNum03.SetOrigin(Origins::TL);

	Vector2f vdot04 = { 9.f,74.f };
	string dot04 = "graphics/Altar/Altar_Point_0" + to_string(index) + ".png";
	m_romaNum04.SetTexture(*RESOURCE_MGR->GetTexture(dot04));
	m_romaNum04.SetScale(0.6f, 0.6f);
	m_romaNum04.SetPos(mainPos + vdot04);
	m_romaNum04.SetOrigin(Origins::TL);

	Vector2f vdot06 = { 11.f,31.f };
	string dot06 = "graphics/Altar/Altar_Point_0" + to_string(index) + ".png";
	m_romaNum06.SetTexture(*RESOURCE_MGR->GetTexture(dot06));
	m_romaNum06.SetScale(0.6f, 0.6f);
	m_romaNum06.SetPos(mainPos + vdot06);
	m_romaNum06.SetOrigin(Origins::TL);

	Vector2f vdot07 = { 25.f,17.f };
	string dot07 = "graphics/Altar/Altar_Point_0" + to_string(index) + ".png";
	m_romaNum07.SetTexture(*RESOURCE_MGR->GetTexture(dot07));
	m_romaNum07.SetScale(0.6f, 0.6f);
	m_romaNum07.SetPos(mainPos + vdot07);
	m_romaNum07.SetOrigin(Origins::TL);

	Vector2f vdot08 = { 77.f,17.f };
	string dot08 = "graphics/Altar/Altar_Point_0" + to_string(index) + ".png";
	m_romaNum08.SetTexture(*RESOURCE_MGR->GetTexture(dot08));
	m_romaNum08.SetScale(0.6f, 0.6f);
	m_romaNum08.SetPos(mainPos + vdot08);
	m_romaNum08.SetOrigin(Origins::TL);

	Vector2f vdot09 = { 91.f,31.f };
	string dot09 = "graphics/Altar/Altar_Point_0" + to_string(index) + ".png";
	m_romaNum09.SetTexture(*RESOURCE_MGR->GetTexture(dot09));
	m_romaNum09.SetScale(0.6f, 0.6f);
	m_romaNum09.SetPos(mainPos + vdot09);
	m_romaNum09.SetOrigin(Origins::TL);

	Vector2f vdot11 = { 93.f,73.f };
	string dot11 = "graphics/Altar/Altar_Point_0" + to_string(index) + ".png";
	m_romaNum11.SetTexture(*RESOURCE_MGR->GetTexture(dot11));
	m_romaNum11.SetScale(0.6f, 0.6f);
	m_romaNum11.SetPos(mainPos + vdot11);
	m_romaNum11.SetOrigin(Origins::TL);

	Vector2f vdot12 = { 93.f,86.f };
	string dot12 = "graphics/Altar/Altar_Point_0" + to_string(index) + ".png";
	m_romaNum12.SetTexture(*RESOURCE_MGR->GetTexture(dot12));
	m_romaNum12.SetScale(0.6f, 0.6f);
	m_romaNum12.SetPos(mainPos + vdot12);
	m_romaNum12.SetOrigin(Origins::TL);

	Vector2f vdot13 = { 93.f,99.f };
	string dot13 = "graphics/Altar/Altar_Point_0" + to_string(index) + ".png";
	m_romaNum13.SetTexture(*RESOURCE_MGR->GetTexture(dot13));
	m_romaNum13.SetScale(0.6f, 0.6f);
	m_romaNum13.SetPos(mainPos + vdot13);
	m_romaNum13.SetOrigin(Origins::TL);

	Vector2f vdot14 = { 93.f,112.f };
	string dot14 = "graphics/Altar/Altar_Point_0" + to_string(index) + ".png";
	m_romaNum14.SetTexture(*RESOURCE_MGR->GetTexture(dot14));
	m_romaNum14.SetScale(0.6f, 0.6f);
	m_romaNum14.SetPos(mainPos + vdot14);
	m_romaNum14.SetOrigin(Origins::TL);
}


