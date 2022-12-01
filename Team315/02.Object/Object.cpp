#include "Object.h"
#include "Framework.h"

int Object::objCount = 1;

Object::Object()
	: enabled(true)
{
	id = objCount++;
	Init();
}

Object::~Object()
{
	Release();
}

int Object::GetObjId() const
{
	return id;
}

void Object::SetActive(bool active)
{
	enabled = active;
}

bool Object::GetActive()
{
	return enabled;
}

void Object::Init()
{
	hitbox.setFillColor(Color(255, 0, 0, 180));
	hitbox.setOutlineColor(Color::Black);
	hitbox.setOutlineThickness(1.f);
}

void Object::Release()
{
}

void Object::Reset()
{
	enabled = true;
}

void Object::SetPos(const Vector2f& pos)
{
	position = pos;
	Vector2f hitboxPos = { hitBoxRect.left, hitBoxRect.top };
	hitbox.setPosition(hitboxPos + pos);
}

const Vector2f& Object::GetPos() const
{
	return position;
}

void Object::Translate(Vector2f delta)
{
	SetPos(position + delta);
}

void Object::Update(float dt)
{
}

void Object::Draw(RenderWindow& window)
{
	if ( FRAMEWORK->devMode )
	{
		window.draw(hitbox);
	}
}

void Object::SetHitbox(const FloatRect rect, Origins origin, int ltDelta, int whDelta)
{
	hitBoxRect = rect;
	hitBoxRect.left		+= ltDelta;
	hitBoxRect.top		+= ltDelta;
	hitBoxRect.width	+= whDelta;
	hitBoxRect.height	+= whDelta;
	hitbox.setSize({ hitBoxRect.width, hitBoxRect.height });
	Utils::SetOrigin(hitbox, origin);
	SetPos(position);
}

void Object::SetHitbox(const IntRect rect, Origins origin, int ltDelta, int whDelta)
{
	SetHitbox((FloatRect)rect, origin, ltDelta, whDelta);
}

void Object::SetHitboxScale(float x, float y)
{
	hitbox.setScale(x, y);
}

RectangleShape& Object::GetHitbox()
{
	return hitbox;
}

void Object::SetHitBoxActive(bool hitboxActive)
{
	if (hitboxActive)
		hitbox.setSize({ hitBoxRect.width, hitBoxRect.height });
	else
		hitbox.setSize({ 0, 0 });
}

bool Object::CollideTest(Vector2f pos)
{
	if (hitbox.getGlobalBounds().contains(pos))
	{
		return true;
	}
	return false;
}