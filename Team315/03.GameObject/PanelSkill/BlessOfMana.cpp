#include "BlessOfMana.h"

BlessOfMana::BlessOfMana()
	:isPlaying(false)
{
}

BlessOfMana::~BlessOfMana()
{
}

void BlessOfMana::Enter()
{
	SetAni();
}

void BlessOfMana::Init()
{
}

void BlessOfMana::Release()
{
}

void BlessOfMana::Update(float dt)
{
	m_BlessOfMana.Update(dt);
}

void BlessOfMana::Draw(RenderWindow& window)
{
	if (!m_BlessOfMana.GetEndFrame())
	{
		SpriteObj::Draw(window);
	}
}

void BlessOfMana::SetAni()
{
	m_BlessOfMana.SetTarget(&sprite);
	m_BlessOfMana.AddClip(*RESOURCE_MGR->GetAnimationClip("Fx_BlessOfMana"));
	SetPos({ GAME_SCREEN_WIDTH * 0.5f ,GAME_SCREEN_HEIGHT * 0.5f + 350.f });
	SetScale(12.f, 12.f);
}

void BlessOfMana::PlayingAni()
{
	m_BlessOfMana.Play("Fx_BlessOfMana");
}
