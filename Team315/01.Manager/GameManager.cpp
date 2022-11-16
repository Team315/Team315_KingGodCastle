#include "GameManager.h"
#include "Include.h"

GameManager::GameManager()
{
	CLOG::Print3String("Game");
	prepare.resize(PREPARE_SIZE, 0);
}

GameManager::~GameManager()
{
}