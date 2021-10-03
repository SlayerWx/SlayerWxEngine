#include "Game.h"
#include <iostream>
Game::Game() 
{
	triangleAuto = Shape(ShapeType::Triangle);
	squareAuto = Shape(ShapeType::Square);
	shape = Shape(ShapeType::Square);
}

void Game::Play()
{
	EngineInit(800,600,"MY EPIC FAIL");
	UpdateEngine();
}

void Game::Start() 
{
	triangleAuto.SetPosition(0.0f, 0.0f, 0.0f);
	shape.SetPosition(-5.0f,0.0f,0.0f);
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
	if (a > 4) right = false;
	else if (a < 0) right = true;

	triangleAuto.Rotate(a,a,a);
	triangleAuto.Scale(0.1+a,1,1);
	triangleAuto.SetPosition(-2+a, -1.2, -5);
	triangleAuto.SetColor(0.f,0.3,0.8);

	squareAuto.Rotate(0,0,a);
	squareAuto.SetPosition(-2.0,1.5,-5);
	squareAuto.SetColor(0.0,1.0,0.0);

	shape.SetPosition(x, y, -5);

	shape.Scale(scaleX, scaleY, scaleZ);

	triangleAuto.Draw();
	squareAuto.Draw();
	shape.Draw();
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
