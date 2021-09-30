#include "Game.h"

void Game::Play()
{
	EngineInit(800,600,"MY EPIC GAME");
	UpdateEngine();
}

void Game::Start()
{
	shape = Shape();
}
void Game::Update()
{
	shape.Draw();
}

