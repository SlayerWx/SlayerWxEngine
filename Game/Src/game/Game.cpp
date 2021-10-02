#include "Game.h"
#include <iostream>
Game::Game() 
{
	shape = Shape(renderer);
	shape2 = Shape(renderer);
}

void Game::Play()
{
	EngineInit(800,600,"MY EPIC FAIL");
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
const float valueModif = 0.001f;
float cameraX = 0.1;
float cameraY = 0.1;
float cameraZ = 0.1;
void Game::Update()
{

	Input(KEYCODE_F, x, -valueModif);
	Input(KEYCODE_H, x, +valueModif);

	Input(KEYCODE_G, y, -valueModif);
	Input(KEYCODE_T, y, +valueModif);

	Input(KEYCODE_K, scaleY, -valueModif* 10);
	Input(KEYCODE_I, scaleY, +valueModif* 10);

	Input(KEYCODE_J, scaleX, -valueModif* 10);
	Input(KEYCODE_L, scaleX, +valueModif* 10);

	Input(KEYCODE_U, scaleZ, -valueModif* 10);
	Input(KEYCODE_O, scaleZ, +valueModif* 10);

	Input(KEYCODE_A, cameraX, -valueModif * 10);
	Input(KEYCODE_D, cameraX, +valueModif * 10);

	Input(KEYCODE_S, cameraY, -valueModif * 10);
	Input(KEYCODE_W, cameraY, +valueModif * 10);
	

	CameraMove(cameraX, cameraY, cameraZ);
	

	if (right)a += 0.0001;
	else a -= 0.0001;;
	if (a > 2) right = false;
	else if (a < 0) right = true;

	shape.Rotate(a,a,a);
	shape.Scale(0.1+a,1,1);
	shape.SetPosition(-1+a, 0, -5);
	//shape.SetColor(0.3f,0.3f,0.8f);

	shape2.SetPosition(x, y, -5);

	shape2.Scale(scaleX, scaleY, scaleZ);

	shape.Draw();
	shape2.Draw();
}
bool Game::Input(int keycode,float &variable,float modif)
{
	if (GetKey(keycode))
	{
		variable += modif;
		return true;
	}
	return false;
}
