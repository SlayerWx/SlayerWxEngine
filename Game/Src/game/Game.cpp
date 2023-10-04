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
	
	//SpriteStart();
	ShapeStart();
	MaterialStart();
	myDirLight.ambient = glm::vec3(0.1, 0.1, 0.1);
	myDirLight.diffuse = glm::vec3(0.5, 0.5, 0.5);
	myDirLight.specular = glm::vec3(1.0, 1.0, 1.0);
	myDirLight.direction = glm::vec3(-1, 0, 0);
	myDirLight.color = glm::vec3(1.0, 1.0, 1.0);
	myDirLight.enable = 1;
	DirectionalLightning::SetNewActualLight(myDirLight);
	point1 = new PointLight(glm::vec3(-1, 2, 5), glm::vec3(1, 1, 1), glm::vec3(0.1, 0.1, 0.1), glm::vec3(0.5, 0.5, 0.5),
		glm::vec3(1, 1, 1));
	//point2 = new PointLight(glm::vec3(-1, 2, 5), glm::vec3(1, 1, 1), glm::vec3(0.1, 0.1, 0.1), glm::vec3(0.5, 0.5, 0.5),
	//		glm::vec3(1, 1, 1));

	pot1 = new SpotLight(glm::vec3(3,1,0),glm::vec3(0,0,1),0.9,0.9,0.9,1,0.9,glm::vec3(0,1,0),glm::vec3(0.1,0.1,0.1),glm::vec3(0.5,0.5,0.5),glm::vec3(0.7,0.7,0.7));
	
	pot2 = new SpotLight(glm::vec3(1, 1, 2), glm::vec3(1, 0, 0), 0.9, 0.9, 0.9, 1, 0.9, glm::vec3(0, 1, 0), glm::vec3(0.1, 0.1, 0.1), glm::vec3(0.5, 0.5, 0.5), glm::vec3(0.7, 0.7, 0.7));

	lightCUbe.SetPosition(point1->position.x, point1->position.y, point1->position.z);
	spotlightCUbe.SetPosition(pot1->position.x, pot1->position.y, pot1->position.z);
	spotlightCUbe2.SetPosition(pot2->position.x, pot2->position.y, pot2->position.z);

	
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

	//Input(KEYCODE_F, x, -valueModif * DeltaTime());
	//Input(KEYCODE_H, x, +valueModif * DeltaTime());
	//
	//Input(KEYCODE_G, y, -valueModif * DeltaTime());
	//Input(KEYCODE_T, y, +valueModif * DeltaTime());
	//
	//Input(KEYCODE_K, scaleY, -valueModif* 10.0f * DeltaTime());
	//Input(KEYCODE_I, scaleY, +valueModif* 10.0f * DeltaTime());
	//
	//Input(KEYCODE_J, scaleX, -valueModif* 10.0f * DeltaTime());
	//Input(KEYCODE_L, scaleX, +valueModif* 10.0f * DeltaTime());
	//
	//Input(KEYCODE_U, scaleZ, -valueModif* 10.0f * DeltaTime());
	//Input(KEYCODE_O, scaleZ, +valueModif* 10.0f * DeltaTime());

	//SpriteUpdate();


	if (GetKey(KEYCODE_W))
		CameraMove(CameraDirection::front, 2000.0f * DeltaTime());
	if (GetKey(KEYCODE_S))
		CameraMove(CameraDirection::back, 2000.0f * DeltaTime());

	if (GetKey(KEYCODE_A))
		CameraMove(CameraDirection::left, 2000.0f * DeltaTime());
	if (GetKey(KEYCODE_D))
		CameraMove(CameraDirection::right, 2000.0f * DeltaTime());

	if (GetKey(KEYCODE_Q))
		CameraMove(CameraDirection::up, 2000.0f * DeltaTime());
	if (GetKey(KEYCODE_E))
		CameraMove(CameraDirection::down, 2000.0f * DeltaTime());


	if (GetKey(KEYCODE_KP_6))
		CameraRotate(cameraSpeedRotateX * DeltaTime(), 0);
	if (GetKey(KEYCODE_KP_2))
		CameraRotate(0, cameraSpeedRotateY * DeltaTime());
	if (GetKey(KEYCODE_KP_4))
		CameraRotate(-cameraSpeedRotateX * DeltaTime(), 0);
	if (GetKey(KEYCODE_KP_8))
		CameraRotate(0, -cameraSpeedRotateY * DeltaTime());


	ShapeUpdate();
	MaterialUpdate();
	//if (GetKey(KEYCODE_SPACE))
	//{		
	//	SetCameraProjection(CameraProjection::ortho);
	//}
	//else
	//{
	//	SetCameraProjection(CameraProjection::perspective);
	//
	//}

	//SpriteDraw();
	//ShapeDraw();
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
	if (model1) delete model1;
	if (point1) delete point1;
	if (point2) delete point2;
	if (pot1) delete pot1;
	if (pot2) delete pot2;
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
	mat1 = Cube("cube", "assets/container.png", "assets/container.png", "assets/container_specular.png");
	mat1.SetPosition(3.0f, 900.0f, 2.0f);
	mat1.Scale(1.0f, 1.0f, 1.0f);
	
	
	lightCUbe = Cube("lightCube", "assets/rick.png");
	lightCUbe.SetPosition(3.0f, 1.0f, 2.0f);
	lightCUbe.Scale(0.3f, 0.3f, 0.3f);

	spotlightCUbe = Cube("lightCube", "assets/bob.png");
	spotlightCUbe.SetPosition(3.0f, 1.0f, 2.0f);
	spotlightCUbe.Scale(0.3f, 0.3f, 0.3f);

	spotlightCUbe2 = Cube("lightCube", "assets/bob.png");
	spotlightCUbe2.SetPosition(3.0f, 1.0f, 2.0f);
	spotlightCUbe2.Scale(0.3f, 0.3f, 0.3f);

	bspPlaneLeft = BSPPlane("bspPlaneLeft", "assets/red.png",glm::vec3(1,0,0));
	bspPlaneLeft.SetPosition(-10.0f, 1.0f, 2.0f);
	bspPlaneLeft.Scale(0.3f, 15.3f, 60.3f);
	//bspPlaneFront = BSPPlane("bspPlaneFront", "assets/red.png", glm::vec3(0, 0, 1));
	//bspPlaneFront.SetPosition(3.0f, 1.0f, -10.0f);
	//bspPlaneFront.Scale(60.3f, 15.3f, 0.3f);
	//bspPlaneRight = BSPPlane("bspPlaneRight", "assets/red.png", glm::vec3(1, 0, 0));
	//bspPlaneRight.SetPosition(10.0f, 1.0f, 2.0f);
	//bspPlaneRight.Scale(0.3f, 15.3f, 60.3f);

	model1 = new Model();

	model1->SetPosition(0.1f, 0.1f, 0.1f);
	model1->Scale(1, 1, 1);
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
	link.Update();
	//if (GetKey(KEYCODE_5)) cameraState = CameraType::free;
	//if (GetKey(KEYCODE_6)) cameraState = CameraType::FirstPerson;
	//if (GetKey(KEYCODE_7)) cameraState = CameraType::ThridPerson;
	//	CameraFollowObj(cameraState, link.GetPosition(), 5);
}
void Game::MaterialUpdate()
{
	if (GetKey(KEYCODE_1))
	{
		point1->position = glm::vec3(point1->position.x + 10.0f * DeltaTime(), point1->position.y, point1->position.z);
	}
	if (GetKey(KEYCODE_2))
	{
		point1->position = glm::vec3(point1->position.x - 10.0f * DeltaTime(), point1->position.y, point1->position.z);
	}
	if (GetKey(KEYCODE_3))
	{
		point1->position = glm::vec3(point1->position.x, point1->position.y, point1->position.z + 10.0f * DeltaTime());
	}
	if (GetKey(KEYCODE_4))
	{
		point1->position = glm::vec3(point1->position.x, point1->position.y, point1->position.z - 10.0f * DeltaTime());

	}

	if (GetKey(KEYCODE_H))
	{
		model1->SetPosition(model1->position.x + 10.0f * DeltaTime(), model1->position.y, model1->position.z);
	}
	if (GetKey(KEYCODE_F))
	{
		model1->SetPosition(model1->position.x - 10.0f * DeltaTime(), model1->position.y, model1->position.z);
	}
	if (GetKey(KEYCODE_G))
	{
		model1->SetPosition(model1->position.x, model1->position.y, model1->position.z + 10.0f * DeltaTime());
	}
	if (GetKey(KEYCODE_T))
	{
		model1->SetPosition(model1->position.x, model1->position.y, model1->position.z - 10.0f * DeltaTime());

	}

	if (GetKey(KEYCODE_9))
	{
		model1->Scale(model1->localScale.x + 0.1f, model1->localScale.y, model1->localScale.z);
		//model1->ScaleForParts(5, 5, 5);
	}
	if (GetKey(KEYCODE_ENTER))
	{
		point1->enable = 1;
		point1->color = glm::vec4(1.0,0.0,0.0,0.0);
	}
	if (GetKey(KEYCODE_BACKSPACE))
	{
		point1->enable = 0;
	
	}
	spotlightCUbe.SetPosition(pot1->position.x, pot1->position.y, pot1->position.z);
	spotlightCUbe2.SetPosition(pot2->position.x, pot2->position.y, pot2->position.z);
	lightCUbe.SetPosition(point1->position.x, point1->position.y, point1->position.z);
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
	//lightCUbe.Draw();
	//spotlightCUbe.Draw();
	//spotlightCUbe2.Draw();
	if (bspPlaneLeft.FrontPlane(model1->GetPosition()))
	{
		model1->Draw(); 
	}
	bspPlaneLeft.Draw();
	//bspPlaneFront.Draw();
	//bspPlaneRight.Draw();

}