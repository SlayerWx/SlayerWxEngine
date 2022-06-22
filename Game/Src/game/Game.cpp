#include "Game.h"
#include <iostream>
CameraType cameraState = CameraType::free;
Game::Game()
{
	downAnim = nullptr;
	idleDownAnim = nullptr;
	leftAnim = nullptr;
	idleLeftAnim = nullptr;
	idleRightAnim = nullptr;
	rightAnim = nullptr;
	upAnim = nullptr;
	idleUpAnim = nullptr;

	triangleAuto = Shape(ShapeType::Triangle);
	squareAuto = Shape(ShapeType::Square);
	shape = Shape(ShapeType::Square);
}

void Game::Play()
{
	EngineInit(800,600,"MY EPIC FAIL");
	UpdateEngine();
}
enum State
{
	Sleft, Sright, Sup, Sdown
};
State linkState = Sdown;
void Game::Start()
{
	
	SpriteStart();
	ShapeStart();
	MaterialStart();
	Light::SetAmbientLight(1.0, 0.5, 0.31);
	Light::SetAmbientSrength(0.5);
}
float a = 0.0f;
bool right = true;
float x = 0.0f;
float y = 0.0f;
float scaleX = 1.0f;
float scaleY = 1.0f;
float scaleZ = 1.0f;
const float valueModif = 500.0f;
float cameraX = 0.1f;
float cameraY = 0.1f;
float cameraZ = 0.1f;
float cameraSpeedRotateX = 200.07f;
float cameraSpeedRotateY = 200.07f;
void Game::Update()
{

	Input(KEYCODE_F, x, -valueModif * DeltaTime());
	Input(KEYCODE_H, x, +valueModif * DeltaTime());

	Input(KEYCODE_G, y, -valueModif * DeltaTime());
	Input(KEYCODE_T, y, +valueModif * DeltaTime());

	Input(KEYCODE_K, scaleY, -valueModif* 10.0f * DeltaTime());
	Input(KEYCODE_I, scaleY, +valueModif* 10.0f * DeltaTime());

	Input(KEYCODE_J, scaleX, -valueModif* 10.0f * DeltaTime());
	Input(KEYCODE_L, scaleX, +valueModif* 10.0f * DeltaTime());

	Input(KEYCODE_U, scaleZ, -valueModif* 10.0f * DeltaTime());
	Input(KEYCODE_O, scaleZ, +valueModif* 10.0f * DeltaTime());

	SpriteUpdate();


	if (GetKey(KEYCODE_W))
		CameraMove(CameraDirection::front, 4000.0f * DeltaTime());
	if (GetKey(KEYCODE_S))
		CameraMove(CameraDirection::back, 4000.0f * DeltaTime());

	if (GetKey(KEYCODE_A))
		CameraMove(CameraDirection::left, 4000.0f * DeltaTime());
	if (GetKey(KEYCODE_D))
		CameraMove(CameraDirection::right, 4000.0f * DeltaTime());

	if (GetKey(KEYCODE_Q))
		CameraMove(CameraDirection::up, 4000.0f * DeltaTime());
	if (GetKey(KEYCODE_E))
		CameraMove(CameraDirection::down, 4000.0f * DeltaTime());


	if (GetKey(KEYCODE_KP_6))
		CameraRotate(cameraSpeedRotateX * DeltaTime(), 0);
	if (GetKey(KEYCODE_KP_2))
		CameraRotate(0, cameraSpeedRotateY * DeltaTime());
	if (GetKey(KEYCODE_KP_4))
		CameraRotate(-cameraSpeedRotateX * DeltaTime(), 0);
	if (GetKey(KEYCODE_KP_8))
		CameraRotate(0, -cameraSpeedRotateY * DeltaTime());

	//SetCameraPosition(cameraX, cameraY, cameraZ);

	if (right)a += 0.0001f * DeltaTime();
	else a -= 0.0001f * DeltaTime();
	if (a > 4.0f) right = false;
	else if (a < 0.0f) right = true;

	ShapeUpdate();
	MaterialUpdate();
	if (GetKey(KEYCODE_SPACE))
	{		
		SetCameraProjection(CameraProjection::ortho);
	}
	else
	{
		SetCameraProjection(CameraProjection::perspective);

	}

	SpriteDraw();
	ShapeDraw();
	MaterialDraw();
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
void Game::Delete()
{
	if (rightAnim) delete rightAnim;
	if(leftAnim) delete leftAnim;
	if(upAnim) delete upAnim;
	if(downAnim) delete downAnim;
	if(idleRightAnim) delete idleRightAnim;
	if(idleUpAnim) delete idleUpAnim;
	if(idleLeftAnim) delete idleLeftAnim;
	if(idleDownAnim) delete idleDownAnim;
}
void Game::ShapeStart()
{
	triangleAuto.SetPosition(0.0f, 0.0f, 0.0f);
	shape.SetPosition(-5.0f,0.0f,0.0f);
}
void Game::SpriteStart()
{
	itsfineSprite = Sprite("assets/This_Is_Fine.png");
	dog = Sprite("assets/logo.png");
	ncat = Sprite("assets/logoCat.png");
	link = Sprite("assets/link.png");
	dog.canCollision = true;
	link.canCollision = true;
	link.strength = 1;
	rightAnim = new Animation();
	rightAnim->AddFrame(0, 0, 96, 104, 961, 831, 0.001, 10);
	upAnim = new Animation();
	upAnim->AddFrame(0, 103, 96, 104, 961, 831, 0.001, 10);
	leftAnim = new Animation();
	leftAnim->AddFrame(2, 208, 96, 102, 961, 831, 0.001, 10);
	downAnim = new Animation();
	downAnim->AddFrame(2, 312, 96, 102, 961, 831, 0.001, 10);
	idleRightAnim = new Animation();
	idleRightAnim->AddFrame(2, 415, 96, 102, 961, 831, 0.007, 3);
	idleUpAnim = new Animation();
	idleUpAnim->AddFrame(2, 517, 96, 102, 961, 831, 0.007, 1);
	idleLeftAnim = new Animation();
	idleLeftAnim->AddFrame(2, 620, 96, 102, 961, 831, 0.007, 3);
	idleDownAnim = new Animation();
	idleDownAnim->AddFrame(2, 723, 96, 102, 961, 831, 0.007, 3);
	link.SetAnimation(idleDownAnim);

	itsfineSprite.SetPosition(0.0f, 0.0f, 2.0f);
	itsfineSprite.Scale(1.0f, 1.0f, 1.0f);
	dog.SetPosition(-3.5f, 0.0f, -1.0f);
	dog.Scale(1.0f, 1.0f, 1.0f);
	ncat.SetPosition(-2.5f, 0.0f, 0.0f);
	ncat.Scale(1.0f, 1.0f, 1.0f);
	link.SetPosition(4.0f, 0.0f, -2.0f);
	link.Scale(1.0f, 1.0f, 1.0f);

}
void Game::MaterialStart()
{
	mat1 = Material2D("assets/rick.png");
	mat1.SetPosition(0.0f, 1.0f, 2.0f);
	mat1.Scale(1.0f, 1.0f, 1.0f);
}
void Game::ShapeUpdate()
{

	triangleAuto.Rotate(a,a,a);
	triangleAuto.Scale(0.1f+a,1.0f,1.0f);
	triangleAuto.SetPosition(+a-2.0f, -1.5f, -5.0f);
	triangleAuto.SetColor(0.0f,0.3f,0.8f);
	
	squareAuto.Rotate(0.0f,0.0f,a);
	squareAuto.SetPosition(-1.9f,+1.5f,-5.0f);
	squareAuto.SetColor(0.0f,1.0f,0.0f);
	
	shape.SetPosition(x, y, -4.0f);
	
	shape.Scale(scaleX, scaleY, scaleZ);
}
void Game::SpriteUpdate()
{
	if (GetKey(KEYCODE_1))
	{
		linkState = Sleft;
		link.SetAnimation(leftAnim);
		link.SetPosition(link.GetPositionX() - 5.0f * DeltaTime(), link.GetPositionY(), link.GetPositionZ());
	}
	else if (linkState == Sleft)
	{
		link.SetAnimation(idleLeftAnim);
	}
	if (GetKey(KEYCODE_2))
	{
		linkState = Sright;
		link.SetAnimation(rightAnim);
		link.SetPosition(link.GetPositionX() + 5.0f * DeltaTime(), link.GetPositionY(), link.GetPositionZ());
	}
	else if (linkState == Sright)
	{
		link.SetAnimation(idleRightAnim);
	}
	if (GetKey(KEYCODE_3))
	{
		linkState = Sup;
		link.SetAnimation(upAnim);
		link.SetPosition(link.GetPositionX(), link.GetPositionY() + 5.0f * DeltaTime(), link.GetPositionZ());
	}
	else if (linkState == Sup)
	{
		link.SetAnimation(idleUpAnim);
	}
	if (GetKey(KEYCODE_4))
	{
		linkState = Sdown;
		link.SetAnimation(downAnim);
		link.SetPosition(link.GetPositionX(), link.GetPositionY() - 5.0f * DeltaTime(), link.GetPositionZ());
	}
	else if (linkState == Sdown)
	{
		link.SetAnimation(idleDownAnim);
	}
	link.CheckCollisionAABB(dog);
	link.Update();
	if (GetKey(KEYCODE_5)) cameraState = CameraType::free;
	if (GetKey(KEYCODE_6)) cameraState = CameraType::FirstPerson;
	if (GetKey(KEYCODE_7)) cameraState = CameraType::ThridPerson;
		CameraFollowObj(cameraState, link.GetPosition(), 5);
}
void Game::MaterialUpdate()
{
}
void Game::SpriteDraw()
{
	
	itsfineSprite.Draw();
	dog.Draw();
	ncat.Draw();
	link.Draw();

}
void Game::ShapeDraw()
{
	triangleAuto.Draw();
	squareAuto.Draw();
	shape.Draw();

}
void Game::MaterialDraw()
{
	mat1.Draw();
}