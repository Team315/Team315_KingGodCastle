#include "Brazier.h"

Brazier::Brazier(int grade)
	:m_grade(grade), m_maxGrade(grade)
{
	
}

Brazier::~Brazier()
{
}

void Brazier::Init()
{
	sprite.setTexture(*RESOURCE_MGR->GetTexture("graphics/Altar/Altar_Brazier.png"),true);
	Vector2f vec = { GAME_SCREEN_WIDTH * 0.5f, GAME_SCREEN_HEIGHT * 0.95f };
	SetPos(vec);
	SetOrigin(Origins::MC);

	m_maxLevelSprite.SetTexture(*RESOURCE_MGR->GetTexture("graphics/Altar/AltarMaxLevel.png"));
	Vector2f maxvec = { GAME_SCREEN_WIDTH * 0.25f, GAME_SCREEN_HEIGHT * 0.92f };
	m_maxLevelSprite.SetOrigin(Origins::MC);
	m_maxLevelSprite.SetScale(0.5f, 0.5f);
	m_maxLevelSprite.SetPos(maxvec);

	m_collectSprite.SetTexture(*RESOURCE_MGR->GetTexture("graphics/Altar/AltarCallect.png"));
	Vector2f collectvec = { GAME_SCREEN_WIDTH * 0.75f, GAME_SCREEN_HEIGHT * 0.92f };
	m_collectSprite.SetOrigin(Origins::MC);
	m_collectSprite.SetScale(0.5f, 0.5f);
	m_collectSprite.SetPos(collectvec);

	
	m_levelNumber.SetFont(*RESOURCE_MGR->GetFont("fonts/GodoB.ttf"));
	m_levelNumber.SetString(to_string(m_grade));
	m_levelNumber.SetCharacterSize(16);
	m_levelNumber.SetColor(Color::White);
	//m_levelNumber.SetOutlineColor(Color::White);
	//m_levelNumber.SetOutlineThickness(2.f);
	m_levelNumber.SetOrigin(Origins::MC);
	m_levelNumber.SetPos(vec);

	Vector2f flameVec = { GAME_SCREEN_WIDTH * 0.5f ,706.f };
	m_Flame.SetTarget(&m_sFlame);
	m_Flame.AddClip(*RESOURCE_MGR->GetAnimationClip("Flame1"));
	m_Flame.AddClip(*RESOURCE_MGR->GetAnimationClip("Flame2"));
	m_Flame.AddClip(*RESOURCE_MGR->GetAnimationClip("Flame3"));
	m_Flame.AddClip(*RESOURCE_MGR->GetAnimationClip("Flame4"));
	m_sFlame.setPosition(flameVec);
	//Utils::SetOrigin(m_sFlame,Origins::BC);
}

void Brazier::Release()
{

}

void Brazier::Update(float dt)
{
	m_Flame.Update(dt);
	//m_Flame.Play("Flame4");
}

void Brazier::Draw(RenderWindow& window)
{
	SpriteObj::Draw(window);
	window.draw(sprite);
	m_maxLevelSprite.Draw(window);
	m_collectSprite.Draw(window);
	m_levelNumber.Draw(window);

	if (m_grade != 0)
		window.draw(m_sFlame);
	
}

void Brazier::Enter()
{
	PlayAni(0);
}

bool Brazier::ClickButton(Vector2f nowMousePos)
{
	if (m_collectSprite.GetGlobalBounds().contains(nowMousePos))
	{
		m_grade = m_maxGrade;
		m_Flame.Play("Flame4");
		m_levelNumber.SetString(to_string(m_grade));
		m_levelNumber.SetOrigin(Origins::MC);
		//PlayAni(m_grade);

		return true;
	}

	return false;
}

void Brazier::PlayAni(int grade)
{
	m_grade -= grade;
	m_levelNumber.SetString(to_string(m_grade));
	m_levelNumber.SetOrigin(Origins::MC);

	if (m_grade >= 1 && m_grade <= 5)
	{
		m_Flame.Play("Flame1");
	}
	else if (m_grade >= 6 && m_grade <= 10)
	{
		m_Flame.Play("Flame2");
	}
	else if (m_grade >= 10 && m_grade <= 15)
	{
		m_Flame.Play("Flame3");
	}
	else if (m_grade >= 16 && m_grade <= 20)
	{
		m_Flame.Play("Flame4");
	}
}

void Brazier::ReSet()
{

}

void Brazier::MoveSetPos(Vector2f movepos)
{
	//m_sFlame.setPosition(movepos);
	m_Flame.Play("Flame4");

}
