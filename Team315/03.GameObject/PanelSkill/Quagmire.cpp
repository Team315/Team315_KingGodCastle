#include "Quagmire.h"

Quagmire::Quagmire()
	:isPlaying(false)
{
}

Quagmire::~Quagmire()
{
}

void Quagmire::Enter()
{
	SetAni();
}

void Quagmire::Init()
{
}

void Quagmire::Release()
{

}

void Quagmire::Update(float dt)
{
	m_Quagmire.Update(dt);
}

void Quagmire::Draw(RenderWindow& window)
{
	//if (isPlaying)
	if(!m_Quagmire.GetEndFrame())
	{
		SpriteObj::Draw(window);
	}
}

void Quagmire::SetAni()
{
	m_Quagmire.SetTarget(&sprite);
	m_Quagmire.AddClip(*RESOURCE_MGR->GetAnimationClip("Fx_Quagmire"));
	SetPos({ GAME_SCREEN_WIDTH * 0.5f ,GAME_SCREEN_HEIGHT * 0.5f +100.f});
	SetScale(3.f, 3.f);
}

void Quagmire::PlayingAni()
{
	m_Quagmire.Play("Fx_Quagmire");
}