#include "Game.h"

Game::Game() 
{
	shape = Shape(renderer);
}

void Game::Play()
{
	EngineInit(800,600,"MY EPIC GAME");
	UpdateEngine();
}

void Game::Start() 
{
	shape.SetPosition(0.5f, 0.0f, 0.0f);
}
float a = 0;
void Game::Update()
{
	a += 0.0001;
	shape.Rotate(0,0,a);
	shape.Scale(0.1+a,1,1);
	shape.SetPosition(-1+a, 0, 0);
	shape.Draw();
}
