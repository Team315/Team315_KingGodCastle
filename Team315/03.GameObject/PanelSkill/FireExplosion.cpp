#include "FireExplosion.h"

FireExplosion::FireExplosion()
	:isPlaying(false)
{
}

FireExplosion::~FireExplosion()
{
}

void FireExplosion::Enter()
{
	SetAni();
}

void FireExplosion::Init()
{
}

void FireExplosion::Release()
{
}

void FireExplosion::Update(float dt)
{
	m_FireExplosion.Update(dt);
}

void FireExplosion::Draw(RenderWindow& window)
{
	if (!m_FireExplosion.GetEndFrame())
	{
		SpriteObj::Draw(window);
	}
}

void FireExplosion::SetAni()
{
	m_FireExplosion.SetTarget(&sprite);
	m_FireExplosion.AddClip(*RESOURCE_MGR->GetAnimationClip("Fx_FireExplosion"));
	SetPos({ GAME_SCREEN_WIDTH * 0.5f ,GAME_SCREEN_HEIGHT * 0.5f + 200.f });
	SetScale(3.f, 3.f);
}

void FireExplosion::PlayingAni()
{
	m_FireExplosion.Play("Fx_FireExplosion");
}
