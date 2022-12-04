#include "Bullet.h"
#include "Character.h"

Bullet::Bullet()
	:dir(), speed(0.f), range(0.f)
{
}

Bullet::~Bullet()
{
}

void Bullet::Fire(const Vector2f& pos, const Vector2f& dir, float speed, float range)
{
	sprite.setRotation(Utils::Angle(dir));
	//SetPos(pos);

	this->dir = dir;
	this->speed = speed;
	this->range = range;
}

void Bullet::Init()
{
	SpriteObj::Init();

	sprite.setTexture(*RESOURCE_MGR->GetTexture("graphics/Effect/player/bullet.png"));
}

void Bullet::Release()
{
	SpriteObj::Release();
}

void Bullet::Reset()
{
	dir = { 0,0 };
	range = 0.f;
	speed = 0.f;
	sprite.setRotation(0.f);
	SetPos({ 0,0 });
}

void Bullet::Update(float dt)
{
	SpriteObj::Update(dt);
	Translate(dir * speed * dt);
	range -= speed * dt;

	if (range < 0)
	{
		SetActive(false);
	}
}

void Bullet::Draw(RenderWindow& window)
{
	SpriteObj::Draw(window);
}