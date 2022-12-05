#include "RangePreview.h"

RangePreview::RangePreview(float x, float y)
	: RectangleObj(x, y), timer(0.f)
{
	SetFillColor(Color(0, 0xff, 0xff, 100.f));
	SetOutline(Color::White, -1.f);
}

RangePreview::~RangePreview()
{
}

void RangePreview::Reset()
{
	timer = 0.f;
}

void RangePreview::Update(float dt)
{
	if (timer > 0.f)
	{
		timer -= dt;
		if (timer < 0.f)
		{
			timer = 0.f;
			SetActive(false);
		}
	}
}

void RangePreview::Fire(const Vector2f pos, float timer)
{
	SetActive(true);
	SetPos(pos);
	SetOrigin(Origins::BC);
	this->timer = timer;
}