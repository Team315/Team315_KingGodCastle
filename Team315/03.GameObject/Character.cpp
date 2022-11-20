#include "Character.h"
#include "Include.h"

Character::Character()
	: destination(0, 0), move(false), attack(false),
	currState(AnimStates::None), drawInBattle(false)
{
	hpBar = new ProgressBar();
	hpBarLocalPos = { -TILE_SIZE_HALF * 0.5f, -TILE_SIZE_HALF - TILE_SIZE };
	hpBar->SetSize(TILE_SIZE_HALF, 5.f);
	hpBar->SetProgressColor(Color::Green);
	hpBar->SetBackgroundColor(Color(0, 0, 0, 100));
	hpBar->SetBackgroundOutline(Color::Black, 2.f);
	hpBar->SetProgressValue(1.f);
	// hpBar->SetOrigin(Origins::BC);

	star = new Star();
	//star->SetOrigin(Origins::BC);
	starLocalPos = { 0, -TILE_SIZE * 1.5f };// -TILE_SIZE * 1.5f
}

Character::~Character()
{
}

void Character::Init()
{
	SetHitbox(FloatRect(0, 0, TILE_SIZE, TILE_SIZE), Origins::BC);
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
	SpriteObj::Draw(window);
	hpBar->Draw(window);
	star->Draw(window);
}

void Character::SetPos(const Vector2f& pos)
{
	SpriteObj::SetPos(pos);
	hpBar->SetPos(pos + hpBarLocalPos);
	star->SetPos(pos + starLocalPos);
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

void Character::UpgradeStar()
{
	if (star->CalculateRandomChance())
		CLOG::Print3String("upgrade 2");
	star->UpdateTexture();
}