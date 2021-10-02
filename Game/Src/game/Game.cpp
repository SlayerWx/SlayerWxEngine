#include "Game.h"
#include <iostream>
Game::Game() 
{
	shape = Shape(renderer);
	shape2 = Shape(renderer);
}

void Game::Play()
{
	EngineInit(800,600,"MY EPIC GAME");
	UpdateEngine();
}

void Game::Start() 
{
	shape.SetPosition(0.0f, 0.0f, 0.0f);
	shape2.SetPosition(-5.0f,0.0f,0.0f);
}
float a = 0;
bool right = true;
float x = 0;
float y = 0;
float scaleX = 1;
float scaleY = 1;
float scaleZ = 1;
const float valueModif = 0.0001f;
void Game::Update()
{

	Input(KEYCODE_A, x, -valueModif);
	Input(KEYCODE_D, x, +valueModif);

	Input(KEYCODE_S, y, -valueModif);
	Input(KEYCODE_W, y, +valueModif);

	Input(KEYCODE_H, scaleY, -valueModif* 10);
	Input(KEYCODE_Y, scaleY, +valueModif* 10);

	Input(KEYCODE_G, scaleX, -valueModif* 10);
	Input(KEYCODE_J, scaleX, +valueModif* 10);

	Input(KEYCODE_T, scaleZ, -valueModif* 10);
	Input(KEYCODE_U, scaleZ, +valueModif* 10);

	if (right)a += 0.0001;
	else a -= 0.0001;;
	if (a > 2) right = false;
	else if (a < 0) right = true;

	shape.Rotate(0,0,a);
	shape.Scale(0.1+a,1,1);
	shape.SetPosition(-1+a, 0, 0);
	shape.SetColor(0.3f,0.3f,0.3f);

	shape2.SetPosition(x, y, 0);
	shape2.Scale(scaleX, scaleY, scaleZ);

	shape.Draw();
	shape2.Draw();
}
void Game::Input(int keycode,float &variable,float modif)
{
	if (GetKey(keycode))
	{
		variable += modif;
	}
}
