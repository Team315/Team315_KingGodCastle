#include "GameObj.h"

GameObj::GameObj()
	: currState(AnimStates::None)
{
}

GameObj::~GameObj()
{
}

void GameObj::Init()
{
	Vector2f hitboxSize(
		GetTextureRect().width * 0.5f < TILE_SIZE ? TILE_SIZE : GetTextureRect().width * 0.5f,
		GetTextureRect().height * 0.5f < TILE_SIZE ? TILE_SIZE : GetTextureRect().height * 0.5f);
	
	SetHitbox(FloatRect(0, 0, hitboxSize.x, hitboxSize.y), Origins::BC);
	Object::Init();
}

void GameObj::SetState(AnimStates newState)
{
	if (currState == newState)
	{
		return;
	}
	currState = newState;
}