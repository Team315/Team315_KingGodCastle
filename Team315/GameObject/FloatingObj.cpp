#include "FloatingObj.h"
#include "../Framework/ConsoleLogger.h"

FloatingObj::FloatingObj()
	: TextObj(), dir(0, -1), speed(50.f), range(50.f), dist(0.f)
{
}

FloatingObj::FloatingObj(Font& font, string textString, float posX, float posY, Color textColor, int textSize)
	: TextObj(font, textString, posX, posY, textColor, textSize),
	dir(0, -1), speed(50.f), range(50.f), dist(0.f)
{
}

void FloatingObj::Release()
{
	TextObj::Release();
}

void FloatingObj::Reset()
{
	this->dir = { 0, -1 };
	this->speed = 50.f;
	this->range = 50.f;
	this->dist = 0.f;

	TextObj::Reset();
}

void FloatingObj::Update(float dt)
{
	if (dist > 0.f)
	{
		dist -= dt * speed;
		Translate(dir * speed * dt);
		if (dist <= 0.f) // 이동 끝나면
		{
			dist = 0.f;
			SetActive(false);
		}
	}
}

void FloatingObj::Draw(RenderWindow& window)
{
	TextObj::Draw(window);
}

void FloatingObj::Fire(const Vector2f pos, const Vector2f dir, float speed, float range)
{
	SetActive(true);
	SetPos(pos);

	this->dir = dir;
	this->speed = speed;
	this->range = range;
	dist = range;
}