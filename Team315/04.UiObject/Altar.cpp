#include "Altar.h"
//#include <sstream>

Altar::Altar(Vector2f mainPos, int index, wstring AltarName, Color color, int loadGrade)
	:m_Index(index), m_grade(loadGrade)
{
	Color acolor = color;
	acolor.a = 100;
	
	string background = "graphics/Altar/Altar_0" + to_string(index) + ".png";
	SetTexture(*RESOURCE_MGR->GetTexture(background));
	SetScale(0.5f, 0.5f);
	SetPos(mainPos);
	SetOrigin(Origins::TL);

	Vector2f altarEffectPos = { 26.f,38.f };
	string Effect = "graphics/Altar/Altar_Effect_0" + to_string(index) + ".png";
	m_altarEffect.SetTexture(*RESOURCE_MGR->GetTexture(Effect));
	m_altarEffect.SetAlhpa(0);
	m_altarEffect.SetScale(0.5f, 0.5f);
	m_altarEffect.SetPos(mainPos+ altarEffectPos);
	m_altarEffect.SetOrigin(Origins::TL);

	Vector2f altarLightPos = { 20.f,24.f };
	string Light = "graphics/Altar/Altar_Light_0" + to_string(index) + ".png";
	m_altarLight.SetTexture(*RESOURCE_MGR->GetTexture(Light));
	m_altarLight.SetAlhpa(0);
	m_altarLight.SetScale(0.5f, 0.5f);
	m_altarLight.SetPos(mainPos + altarLightPos);
	m_altarLight.SetOrigin(Origins::TL);


	Vector2f numberPos = { 59.f,19.f };
	m_number.SetFont(*RESOURCE_MGR->GetFont("fonts/GodoB.ttf"));
	m_number.SetString("0");
	m_number.SetColor(color);
	m_number.SetOutlineThickness(2.f);
	m_number.SetOutlineColor(acolor);
	m_number.SetCharacterSize(15);
	m_number.SetPos(mainPos + numberPos);
	m_number.SetOrigin(Origins::MC);

	Vector2f altarNamePos = { 60.f,159.f };
	m_altarName.SetFont(*RESOURCE_MGR->GetFont("fonts/GodoB.ttf"));
	m_altarName.SetString(AltarName);
	m_altarName.SetColor(color);
	m_altarName.SetOutlineThickness(2.f);
	m_altarName.SetOutlineColor(Color::Black);
	m_altarName.SetCharacterSize(14);
	m_altarName.SetPos(mainPos + altarNamePos);
	m_altarName.SetOrigin(Origins::MC);

	Vector2f altarbutton1 = { 8.f,238.f };
	m_button1.SetTexture(*RESOURCE_MGR->GetTexture("graphics/Altar/Altar_Button1.png"));
	m_button1.SetScale(0.5f, 0.5f);
	m_button1.SetPos(mainPos + altarbutton1);
	m_button1.SetOrigin(Origins::TL);

	Vector2f altarbutton5 = { 62.f,238.f };
	m_button5.SetTexture(*RESOURCE_MGR->GetTexture("graphics/Altar/Altar_Button5.png"));
	m_button5.SetScale(0.5f, 0.5f);
	m_button5.SetPos(mainPos + altarbutton5);
	m_button5.SetOrigin(Origins::TL);

	SetRomaNumber(mainPos, index);
	SetBuffString(mainPos);


	string flamestr1 = "Flame0"+ to_string(m_Index) + "_1";
	string flamestr2 = "Flame0" + to_string(m_Index) + "_2";
	string flamestr3 = "Flame0" + to_string(m_Index) + "_3";
	string flamestr4 = "Flame0" + to_string(m_Index) + "_4";
	Vector2f flameVec = { 57.f ,135.f };

	m_Flame.SetTarget(&m_sFlame);
	m_Flame.AddClip(*RESOURCE_MGR->GetAnimationClip(flamestr1));
	m_Flame.AddClip(*RESOURCE_MGR->GetAnimationClip(flamestr2));
	m_Flame.AddClip(*RESOURCE_MGR->GetAnimationClip(flamestr3));
	m_Flame.AddClip(*RESOURCE_MGR->GetAnimationClip(flamestr4));
	m_sFlame.setScale({ 0.5f,0.5f });
	m_sFlame.setPosition(flameVec+ mainPos);
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

	m_Flame.Update(dt);
}

void Altar::Draw(RenderWindow& window)
{
	SpriteObj::Draw(window);
	m_altarEffect.Draw(window);
	m_altarLight.Draw(window);



	if (m_grade != 0)
	{
		for (int i = 0; i < m_grade; ++i)
		{
			numList[i].Draw(window);
		}
	}

	m_number.Draw(window);

	m_altarName.Draw(window);

	m_button1.Draw(window);
	m_button5.Draw(window);

	m_buff1.Draw(window);
	m_buff2.Draw(window);
	m_buff3.Draw(window);
	
	if (m_grade != 0)
	{
		window.draw(m_sFlame);
	}
}

void Altar::Enter()
{
	ChangeAltarNum(m_grade);
	ChangeObjAlhpa(m_grade);
}

void Altar::MoveSetPos(Vector2f movepos)
{
	m_Flame.Play("Flame00_4");
	//SetPos(GetPos() + movepos);
	//m_buff2.SetPos(movepos);
	m_sFlame.setPosition(movepos);
}

//vector<string> split(string input, char delimiter)
//{
//	vector<string> answer;
//	stringstream ss(input);
//	string temp;
//
//	while (getline(ss, temp, delimiter)) 
//	{
//		answer.push_back(temp);
//	}
//
//	return answer;
//}

void Altar::SetAltarString()
{
	string altarDataPath = "data/AltarStringData.csv";

	rapidcsv::Document altarDataDoc(altarDataPath, rapidcsv::LabelParams(0, -1));
	auto key = altarDataDoc.GetColumn<string>(0);
	vector<string> altar1 = altarDataDoc.GetColumn<string>(1);
	vector<string> altar2 = altarDataDoc.GetColumn<string>(2);
	vector<string> altar3 = altarDataDoc.GetColumn<string>(3);
	
	for (int j = 0; j < altarDataDoc.GetRowCount(); ++j)
	{
		AltarStringData.insert({ key[j], AltarStr(Utils::s2w(altar1[j]), Utils::s2w(altar2[j]), Utils::s2w(altar3[j]))});
	}
}

void Altar::SetRomaNumber(Vector2f mainPos, int index)
{
	Vector2f romaNum01Pos = { 7.f,128.f };
	string romaNum01 = "graphics/Altar/Altar_RomaNum0" + to_string(index) + "_01.png";
	m_romaNum01.SetTexture(*RESOURCE_MGR->GetTexture(romaNum01));
	m_romaNum01.SetScale(0.5f, 0.5f);
	m_romaNum01.SetPos(mainPos + romaNum01Pos);
	m_romaNum01.SetOrigin(Origins::TL);
	numList.push_back(m_romaNum01);

	Vector2f vdot02 = { 9.f,110.f };
	string dot02 = "graphics/Altar/Altar_Point_0" + to_string(index) + ".png";
	m_romaNum02.SetTexture(*RESOURCE_MGR->GetTexture(dot02));
	m_romaNum02.SetScale(0.6f, 0.6f);
	m_romaNum02.SetPos(mainPos + vdot02);
	m_romaNum02.SetOrigin(Origins::TL);
	numList.push_back(m_romaNum02);

	Vector2f vdot03 = { 9.f,92.f };
	string dot03 = "graphics/Altar/Altar_Point_0" + to_string(index) + ".png";
	m_romaNum03.SetTexture(*RESOURCE_MGR->GetTexture(dot03));
	m_romaNum03.SetScale(0.6f, 0.6f);
	m_romaNum03.SetPos(mainPos + vdot03);
	m_romaNum03.SetOrigin(Origins::TL);
	numList.push_back(m_romaNum03);

	Vector2f vdot04 = { 9.f,74.f };
	string dot04 = "graphics/Altar/Altar_Point_0" + to_string(index) + ".png";
	m_romaNum04.SetTexture(*RESOURCE_MGR->GetTexture(dot04));
	m_romaNum04.SetScale(0.6f, 0.6f);
	m_romaNum04.SetPos(mainPos + vdot04);
	m_romaNum04.SetOrigin(Origins::TL);
	numList.push_back(m_romaNum04);

	Vector2f romaNum05Pos = { 5.f,50.f };
	string romaNum05 = "graphics/Altar/Altar_RomaNum0" + to_string(index) + "_05.png";
	m_romaNum05.SetTexture(*RESOURCE_MGR->GetTexture(romaNum05));
	m_romaNum05.SetScale(0.5f, 0.5f);
	m_romaNum05.SetPos(mainPos + romaNum05Pos);
	m_romaNum05.SetOrigin(Origins::TL);
	numList.push_back(m_romaNum05);

	Vector2f vdot06 = { 11.f,31.f };
	string dot06 = "graphics/Altar/Altar_Point_0" + to_string(index) + ".png";
	m_romaNum06.SetTexture(*RESOURCE_MGR->GetTexture(dot06));
	m_romaNum06.SetScale(0.6f, 0.6f);
	m_romaNum06.SetPos(mainPos + vdot06);
	m_romaNum06.SetOrigin(Origins::TL);
	numList.push_back(m_romaNum06);

	Vector2f vdot07 = { 25.f,17.f };
	string dot07 = "graphics/Altar/Altar_Point_0" + to_string(index) + ".png";
	m_romaNum07.SetTexture(*RESOURCE_MGR->GetTexture(dot07));
	m_romaNum07.SetScale(0.6f, 0.6f);
	m_romaNum07.SetPos(mainPos + vdot07);
	m_romaNum07.SetOrigin(Origins::TL);
	numList.push_back(m_romaNum07);

	Vector2f vdot08 = { 77.f,17.f };
	string dot08 = "graphics/Altar/Altar_Point_0" + to_string(index) + ".png";
	m_romaNum08.SetTexture(*RESOURCE_MGR->GetTexture(dot08));
	m_romaNum08.SetScale(0.6f, 0.6f);
	m_romaNum08.SetPos(mainPos + vdot08);
	m_romaNum08.SetOrigin(Origins::TL);
	numList.push_back(m_romaNum08);

	Vector2f vdot09 = { 91.f,31.f };
	string dot09 = "graphics/Altar/Altar_Point_0" + to_string(index) + ".png";
	m_romaNum09.SetTexture(*RESOURCE_MGR->GetTexture(dot09));
	m_romaNum09.SetScale(0.6f, 0.6f);
	m_romaNum09.SetPos(mainPos + vdot09);
	m_romaNum09.SetOrigin(Origins::TL);
	numList.push_back(m_romaNum09);

	Vector2f romaNum10Pos = { 89.f,50.f };
	string romaNum10 = "graphics/Altar/Altar_RomaNum0" + to_string(index) + "_10.png";
	m_romaNum10.SetTexture(*RESOURCE_MGR->GetTexture(romaNum10));
	m_romaNum10.SetScale(0.5f, 0.5f);
	m_romaNum10.SetPos(mainPos + romaNum10Pos);
	m_romaNum10.SetOrigin(Origins::TL);
	numList.push_back(m_romaNum10);

	Vector2f vdot11 = { 93.f,73.f };
	string dot11 = "graphics/Altar/Altar_Point_0" + to_string(index) + ".png";
	m_romaNum11.SetTexture(*RESOURCE_MGR->GetTexture(dot11));
	m_romaNum11.SetScale(0.6f, 0.6f);
	m_romaNum11.SetPos(mainPos + vdot11);
	m_romaNum11.SetOrigin(Origins::TL);
	numList.push_back(m_romaNum11);

	Vector2f vdot12 = { 93.f,86.f };
	string dot12 = "graphics/Altar/Altar_Point_0" + to_string(index) + ".png";
	m_romaNum12.SetTexture(*RESOURCE_MGR->GetTexture(dot12));
	m_romaNum12.SetScale(0.6f, 0.6f);
	m_romaNum12.SetPos(mainPos + vdot12);
	m_romaNum12.SetOrigin(Origins::TL);
	numList.push_back(m_romaNum12);

	Vector2f vdot13 = { 93.f,99.f };
	string dot13 = "graphics/Altar/Altar_Point_0" + to_string(index) + ".png";
	m_romaNum13.SetTexture(*RESOURCE_MGR->GetTexture(dot13));
	m_romaNum13.SetScale(0.6f, 0.6f);
	m_romaNum13.SetPos(mainPos + vdot13);
	m_romaNum13.SetOrigin(Origins::TL);
	numList.push_back(m_romaNum13);

	Vector2f vdot14 = { 93.f,112.f };
	string dot14 = "graphics/Altar/Altar_Point_0" + to_string(index) + ".png";
	m_romaNum14.SetTexture(*RESOURCE_MGR->GetTexture(dot14));
	m_romaNum14.SetScale(0.6f, 0.6f);
	m_romaNum14.SetPos(mainPos + vdot14);
	m_romaNum14.SetOrigin(Origins::TL);
	numList.push_back(m_romaNum14);

	Vector2f romaNum15Pos = { 89.f,128.f };
	string romaNum15 = "graphics/Altar/Altar_RomaNum0" + to_string(index) + "_15.png";
	m_romaNum15.SetTexture(*RESOURCE_MGR->GetTexture(romaNum15));
	m_romaNum15.SetScale(0.5f, 0.5f);
	m_romaNum15.SetPos(mainPos + romaNum15Pos);
	m_romaNum15.SetOrigin(Origins::TL);
	numList.push_back(m_romaNum15);

}

void Altar::SetDot(Vector2f mainPos, int index)
{
}

void Altar::SetBuffString(Vector2f mainpos)
{
	SetAltarString();

	string key = "Altar_0" + to_string(m_Index) + "_" + to_string(m_grade/10)  + to_string(m_grade % 10);
	AltarStringData[key];

	Vector2f buff1 = { 57.f,183.f };
	m_buff1.SetFont(*RESOURCE_MGR->GetFont("fonts/GodoB.ttf"));
	m_buff1.SetString(AltarStringData[key].altar1);
	m_buff1.SetLetterSpacing(0.1f);
	m_buff1.SetColor(Color::White);
	m_buff1.SetAlhpa(60);
	m_buff1.SetCharacterSize(10);
	m_buff1.SetPos(mainpos + buff1);
	m_buff1.SetOrigin(Origins::MC);

	Vector2f buff2 = { 57.f,203.f };
	m_buff2.SetFont(*RESOURCE_MGR->GetFont("fonts/GodoB.ttf"));
	m_buff2.SetString(AltarStringData[key].altar2);
	m_buff2.SetLetterSpacing(0.1f);
	m_buff2.SetColor(Color::White);
	m_buff2.SetAlhpa(60);
	m_buff2.SetCharacterSize(10);
	m_buff2.SetPos(mainpos + buff2);
	m_buff2.SetOrigin(Origins::MC);

	Vector2f buff3 = { 57.f, 223.f };
	m_buff3.SetFont(*RESOURCE_MGR->GetFont("fonts/GodoB.ttf"));
	m_buff3.SetString(AltarStringData[key].altar3);
	m_buff3.SetLetterSpacing(0.1f);
	m_buff3.SetColor(Color::White);
	m_buff3.SetAlhpa(60);
	m_buff3.SetCharacterSize(10);
	m_buff3.SetPos(mainpos + buff3);
	m_buff3.SetOrigin(Origins::MC);
}

int Altar::GetButtonCall(Vector2f nowMousePos, int count)
{
	if (count == 0)
		return 0;

	if (m_button1.GetGlobalBounds().contains(nowMousePos))
	{
		++m_grade;
		if (m_grade > 15)
		{
			m_grade = 15;
			cout << m_grade << endl;

			ChangeAltarNum(m_grade);
			ChangeObjAlhpa(m_grade);
			return 0;
		}
		cout << m_grade << endl;

		ChangeAltarNum(m_grade);
		ChangeObjAlhpa(m_grade);

		return 1;
	}
	else if (m_button5.GetGlobalBounds().contains(nowMousePos))
	{
		if (count < 5)
			return 0;

		int temp = m_grade;
		m_grade += 5;

		if (m_grade > 15)
		{
			m_grade = 15;
			cout << m_grade << endl;
			ChangeAltarNum(m_grade);
			ChangeObjAlhpa(m_grade);

			return m_grade - temp;
		}

		cout << m_grade << endl;
		ChangeAltarNum(m_grade);
		ChangeObjAlhpa(m_grade);
		return 5;
	}
	else
	{
		//ChangeAltarNum(m_grade);
		//ChangeObjAlhpa(m_grade);
		return 0;
	}
}

void Altar::AddCount(int count)
{
	m_grade = count;

	if (m_grade > 15)
		m_grade = 15;
}

void Altar::ResetCount()
{
	m_grade = 0;
	ChangeAltarNum(m_grade);
	ChangeObjAlhpa(m_grade);
}

void Altar::ChangeAltarNum(int Num)
{
	wstring str = to_wstring(Num);
	m_number.SetString(str);
	m_number.SetOrigin(Origins::MC);

}

void Altar::ChangeObjAlhpa(int num)
{
	string key = "Altar_0" + to_string(m_Index + 1) + "_" + to_string(m_grade / 10) + to_string(m_grade % 10);
	AltarStringData[key];
	m_buff1.SetString(AltarStringData[key].altar1);
	m_buff2.SetString(AltarStringData[key].altar2);
	m_buff3.SetString(AltarStringData[key].altar3);

	/*m_buff1.SetLetterSpacing(0.1f);
	m_buff2.SetLetterSpacing(0.1f);
	m_buff3.SetLetterSpacing(0.1f);*/

	m_buff1.SetOrigin(Origins::MC);
	m_buff2.SetOrigin(Origins::MC);
	m_buff3.SetOrigin(Origins::MC);

	if (num == 0)
	{
		m_altarEffect.SetAlhpa(0);
		m_altarLight.SetAlhpa(0);
		m_buff1.SetAlhpa(60);
		m_buff2.SetAlhpa(60);
		m_buff3.SetAlhpa(60);
		

		//m_Flame.Stop();
		return;
	}
	if (num >= 1 && num <= 4)
	{
		m_altarEffect.SetAlhpa(60);
		m_altarLight.SetAlhpa(60);
		m_buff1.SetAlhpa(255);
		m_buff2.SetAlhpa(60);
		m_buff3.SetAlhpa(60);

		string flamestr1 = "Flame0" + to_string(m_Index) + "_1";
		m_Flame.Play(flamestr1);

	}
	else if (num >= 5 && num <= 9)
	{
		m_altarEffect.SetAlhpa(120);
		m_altarLight.SetAlhpa(120);
		m_buff1.SetAlhpa(255);
		m_buff2.SetAlhpa(255);
		m_buff3.SetAlhpa(60);

		string flamestr2 = "Flame0" + to_string(m_Index) + "_2";
		m_Flame.Play(flamestr2);

	}
	else if (num >= 10 && num <= 14)
	{
		m_altarEffect.SetAlhpa(180);
		m_altarLight.SetAlhpa(180);
		m_buff1.SetAlhpa(255);
		m_buff2.SetAlhpa(255);
		m_buff3.SetAlhpa(255);

		string flamestr3 = "Flame0" + to_string(m_Index) + "_3";
		m_Flame.Play(flamestr3);

	}
	else if (num == 15)
	{
		m_altarEffect.SetAlhpa(255);
		m_altarLight.SetAlhpa(255);
		m_buff1.SetAlhpa(255);
		m_buff2.SetAlhpa(255);
		m_buff3.SetAlhpa(255);
		string flamestr4 = "Flame0" + to_string(m_Index) + "_4";
		m_Flame.Play(flamestr4);
	}
}