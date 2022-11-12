#include "Character.h"

Character::Character()
{
	hpBar = new ProgressBar();
	hpBarLocalPos = { -10.f, -30.f };
	hpBar->SetSize(20.f, 5.f);
	hpBar->SetProgressColor(Color::Green);
	hpBar->SetBackgroundColor(Color(0, 0, 0, 100));
	hpBar->SetBackgroundOutline(Color::Black, 2.f);
	hpBar->SetProgressValue(1.f);
}

Character::~Character()
{
}

void Character::Init()
{
	Object::Init();
}

void Character::Update(float dt)
{
	hpBar->Update(dt);
	SpriteObj::Update(dt);
}

void Character::Draw(RenderWindow& window)
{
	hpBar->Draw(window);
	SpriteObj::Draw(window);
}

void Character::SetPos(const Vector2f& pos)
{
	SpriteObj::SetPos(pos);
	hpBar->SetPos(pos + hpBarLocalPos);
}

void Character::SetTarget(Character* target)
{
	this->target = target;
}

void Character::SetHpBarLocalPos(Vector2f pos)
{
	hpBarLocalPos = pos;
	SetPos(position);
}
