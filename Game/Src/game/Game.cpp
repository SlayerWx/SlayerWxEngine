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

float a = 0.0f;
bool right = true;
float x = 0.0f;
float y = 0.0f;
float scaleX = 50.0f;
float scaleY = 50.0f;
float scaleZ = 50.0f;
const float valueModif = 0.50f;
float cameraX = 0.1f;
float cameraY = 0.1f;
float cameraZ = 0.1f;
float cameraSpeedRotateX = 0.07f;
float cameraSpeedRotateY = 0.07f;
void Game::Start() 
{
	triangleAuto.SetPosition(-300.0f, -200.0f, 0.0f);
	squareAuto.SetPosition(-300.0f,200.0f,0.0f);
	shape.Scale(scaleX, scaleY, scaleZ);
	triangleAuto.Scale(scaleX, scaleY, scaleZ);
	squareAuto.Scale(scaleX, scaleY, scaleZ);
}

void Game::Update()
{
	Input(KEYCODE_F, x, -valueModif);
	Input(KEYCODE_H, x, +valueModif);

	Input(KEYCODE_G, y, -valueModif);
	Input(KEYCODE_T, y, +valueModif);

	Input(KEYCODE_K, scaleY, -valueModif* 10.0f);
	Input(KEYCODE_I, scaleY, +valueModif* 10.0f);

	Input(KEYCODE_J, scaleX, -valueModif* 10.0f);
	Input(KEYCODE_L, scaleX, +valueModif* 10.0f);

	Input(KEYCODE_U, scaleZ, -valueModif* 10.0f);
	Input(KEYCODE_O, scaleZ, +valueModif* 10.0f);

	//Input(KEYCODE_A, cameraX, -valueModif * 10.0f);
	//Input(KEYCODE_D, cameraX, +valueModif * 10.0f);

	//Input(KEYCODE_Q, cameraY, -valueModif * 10.0f);
	//Input(KEYCODE_E, cameraY, +valueModif * 10.0f);

	//Input(KEYCODE_S, cameraZ, -valueModif * 10.0f);
	//Input(KEYCODE_W, cameraZ, +valueModif * 10.0f);

	if (GetKey(KEYCODE_W))
		CameraMove(CameraDirection::front, 50.0f);
	if (GetKey(KEYCODE_S))
		CameraMove(CameraDirection::back, 50.0f);

	if (GetKey(KEYCODE_A))
		CameraMove(CameraDirection::left, 50.0f);
	if (GetKey(KEYCODE_D))
		CameraMove(CameraDirection::right, 50.0f);

	if (GetKey(KEYCODE_Q))
		CameraMove(CameraDirection::up, 50.0f);
	if (GetKey(KEYCODE_E))
		CameraMove(CameraDirection::down, 50.0f);


	if (GetKey(KEYCODE_KP_6))
		CameraRotate(cameraSpeedRotateX, 0);
	if (GetKey(KEYCODE_KP_2))
		CameraRotate(0, cameraSpeedRotateY);
	if (GetKey(KEYCODE_KP_4))
		CameraRotate(-cameraSpeedRotateX, 0);
	if (GetKey(KEYCODE_KP_8))
		CameraRotate(0, -cameraSpeedRotateY);

	//SetCameraPosition(cameraX, cameraY, cameraZ);

	if (right)a += 0.001f;
	else a -= 0.001f;
	if (a > 6.0f) right = false;
	else if (a < 0.0f) right = true;

	triangleAuto.Rotate(a,a,a);
	triangleAuto.Scale(scaleX+a, scaleY, scaleZ);
	triangleAuto.SetPosition(+a * 100.0f- 300.0f, -200.0f, -5.0f);
	triangleAuto.SetColor(0.0f,0.3f,0.8f);

	squareAuto.Rotate(0.0f,0.0f,a);
	squareAuto.SetColor(0.0f,1.0f,0.0f);

	shape.SetPosition(x, y, 100.0f);

	shape.Scale(scaleX, scaleY, scaleZ);
	if (GetKey(KEYCODE_SPACE))
	{		
		SetCameraProjection(CameraProjection::ortho);
	}
	else
	{
		SetCameraProjection(CameraProjection::perspective);

	}

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
