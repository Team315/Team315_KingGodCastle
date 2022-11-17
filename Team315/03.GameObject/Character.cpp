#include "Character.h"
#include "Include.h"

Character::Character()
	: destination(0, 0), move(false), attack(false),
	currState(AnimStates::None), drawInBattle(false)
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
	hpBar->SetHitbox(FloatRect(0, 0, 20, 5), Origins::LT);
	hpBar->Init();
	Object::Init();
}

void Character::Update(float dt)
{
	hpBar->Update(dt);
	if (move)
	{
		SetState(AnimStates::Move);
		direction = destination - position;
		Translate(Utils::Normalize(direction));
		if (destination == position)
		{
			move = false;
			SetState(AnimStates::MoveToIdle);
		}
	}
}

void Character::Draw(RenderWindow& window)
{
	//if (drawInBattle)
	hpBar->Draw(window);
	SpriteObj::Draw(window);
}

void Character::SetPos(const Vector2f& pos)
{
	SpriteObj::SetPos(pos);
	hpBar->SetPos(pos + hpBarLocalPos);
}

void Character::SetState(AnimStates newState)
{
	if (currState == newState)
	{
		return;
	}
	currState = newState;
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