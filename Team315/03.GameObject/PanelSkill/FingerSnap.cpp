#include "FingerSnap.h"

FingerSnap::FingerSnap()
	:isPlaying(false)
{
}

FingerSnap::~FingerSnap()
{
}

void FingerSnap::Enter()
{
	SetAni();
}

void FingerSnap::Init()
{
}

void FingerSnap::Release()
{
}

void FingerSnap::Update(float dt)
{
	m_FingerSnap.Update(dt);
}

void FingerSnap::Draw(RenderWindow& window)
{
	if (!m_FingerSnap.GetEndFrame())
	{
		SpriteObj::Draw(window);
	}
}

void FingerSnap::SetAni()
{
	m_FingerSnap.SetTarget(&sprite);
	m_FingerSnap.AddClip(*RESOURCE_MGR->GetAnimationClip("Fx_FingerSnap"));
	SetPos({ GAME_SCREEN_WIDTH * 0.5f ,GAME_SCREEN_HEIGHT * 0.5f - 50.f });
	SetScale(3.f, 3.f);
}

void FingerSnap::PlayingAni()
{
	m_FingerSnap.Play("Fx_FingerSnap");
}
