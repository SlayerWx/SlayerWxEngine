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
	point2 = new PointLight(glm::vec3(-1, 2, 5), glm::vec3(1, 1, 1), glm::vec3(0.1, 0.1, 0.1), glm::vec3(0.5, 0.5, 0.5),
			glm::vec3(1, 1, 1));

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
float auxYTestPatata = 1.0f;
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
	if (GetKey(KEYCODE_SPACE))
	{		
		//SetCameraProjection(CameraProjection::ortho);
		
	}
	else
	{
		//SetCameraProjection(CameraProjection::perspective);
	
	}

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

	model1 = new Model();
	ModelLoader::LoadModel("assets/models/test/bodyna.fbx", model1->structure);


	model1->SetPosition(0, 2.5, 0);
	model1->SetMeshPosition(0, 0.5, 0, 1);
	
	model1->SetMeshPosition(0, -0.2, 0, 2);
	model1->SetMeshScale(0.5, 1.33, 0.5, 2);
	
	model1->SetMeshPosition(0, -5.225, 0, 3);
	model1->SetMeshScale(1.5, 0.75, 1.5, 3);
	
	model1->SetMeshPosition(5.05, -0.2, 0, 4);
	model1->SetMeshScale(0.33, 1, 0.33, 4);
	
	model1->SetMeshPosition(0, -5.15, -0.05, 5);
	model1->SetMeshScale(0.9, 0.6, 3, 5);
	
	model1->SetMeshPosition(-0.05, -5.2, 0, 6);
	model1->SetMeshScale(0.33, 1, 0.33, 6);
	
	model1->SetMeshPosition(0, -3.15, -0.05, 7);
	model1->SetMeshScale(0.9, 0.6, 3, 7);
	
	model1->SetMeshPosition(5.15, 0, 0, 8);
	model1->SetMeshScale(3, 0.33, 0.5, 8);
	
	model1->SetMeshPosition(5.2, 0.0, 0, 9);
	model1->SetMeshScale(0.33, 2, 2, 9);
	
	model1->SetMeshPosition(-5.15, 0, 0, 10);
	model1->SetMeshScale(3, 0.33, 0.5, 10);
	
	model1->SetMeshPosition(-5.2, 0, 0, 11);
	model1->SetMeshScale(0.33, 2, 2, 11);
	



	//model2 = new Model();
	//ModelLoader::LoadModel("assets/models/test2/bodyna2.fbx", model2->structure);
	//model2->SetMeshPosition(-20.1f, -3.1f, 0.1f,0);
	//model2->SetMeshScale(2, 1, 2,1);
	//
	//model3 = new Model();
	//ModelLoader::LoadModel("assets/models/test2/bodyna2.fbx", model3->structure);
	//model3->SetMeshPosition(20.1f, -3.1f, 0.1f, 0);
	//model3->SetMeshScale(2, 2, 2, 1);
	//
	//model4 = new Model();
	//ModelLoader::LoadModel("assets/models/test2/bodyna2.fbx", model4->structure);
	//model4->SetMeshPosition(-20.1f, -3.1f, -20.1f, 0);
	//model4->SetMeshScale(2, 2, 2, 1);
	//
	//model5 = new Model();
	//ModelLoader::LoadModel("assets/models/test2/bodyna2.fbx", model5->structure);
	//model5->SetMeshPosition(20.1f, -3.1f, -20.1f, 0);
	//model5->SetMeshScale(2, 2, 2, 1);
	//
	//model6 = new Model();
	//ModelLoader::LoadModel("assets/models/test2/bodyna2.fbx", model6->structure);
	//model6->SetMeshPosition(0.1f, -3.1f, 0.1f, 0);
	//model6->SetMeshScale(2, 2, 2, 1);
	//
	//model7 = new Model();
	//ModelLoader::LoadModel("assets/models/test2/bodyna2.fbx", model7->structure);
	//model7->SetMeshPosition(0.1f, -3.1f, -20.1f, 0);
	//model7->SetMeshScale(2, 2, 2, 1);
	
	
	//BSP::AddModel(model1);
	//BSP::AddModel(model2);
	//BSP::AddModel(model3);
	//BSP::AddModel(model4);
	//BSP::AddModel(model5);
	//BSP::AddModel(model6);
	//BSP::AddModel(model7);

	SetShowBSP(false);
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
}
float xMesh = 0.01f, yMesh = 0.01f, zMesh = 0.01f;
float rotate = 0.01f;
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
		xMesh += 5.0f * DeltaTime();
		model1->SetMeshPosition(xMesh, yMesh, zMesh,0);
	}
	if (GetKey(KEYCODE_F))
	{
		xMesh -= 5.0f * DeltaTime();
		model1->SetMeshPosition(xMesh, yMesh, zMesh,0);
	}
	if (GetKey(KEYCODE_G))
	{
		zMesh += 5.0f * DeltaTime();
		model1->SetMeshPosition(xMesh, yMesh, zMesh,0);
	}
	if (GetKey(KEYCODE_T))
	{
		zMesh -= 5.0f * DeltaTime();
		model1->SetMeshPosition(xMesh, yMesh, zMesh,0);

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
	if (GetKey(KEYCODE_SPACE))
	{
		rotate += 0.01f;
		model1->RotateModel(rotate,0,0,1);
		//model1->MoveMeshPosition(5 * DeltaTime(), 0, 0, 4);
	}

	glm::vec3 aux = model1->GetMeshPosition(4);
	//std::cout << aux.x << " " << aux.y << " " << aux.z << std::endl;

	spotlightCUbe.SetPosition(pot1->position.x, pot1->position.y, pot1->position.z);
	spotlightCUbe2.SetPosition(pot2->position.x, pot2->position.y, pot2->position.z);
	lightCUbe.SetPosition(point1->position.x, point1->position.y, point1->position.z);

	//model1->SetMeshPosition(0.1f, auxYTestPatata, 0.1f, 6);
	//auxYTestPatata += 0.2f * DeltaTime();
	if (GetKey(KEYCODE_5)) cameraState = CameraType::free;
	if (GetKey(KEYCODE_6)) cameraState = CameraType::FirstPerson;
	if (GetKey(KEYCODE_7)) cameraState = CameraType::ThridPerson;
		CameraFollowObj(cameraState, model1->GetPosition(), 5);
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
	lightCUbe.Draw();
	spotlightCUbe.Draw();
	spotlightCUbe2.Draw();
	model1->Draw();
	//model2->Draw();
	//model3->Draw();
	//model4->Draw();
	//model5->Draw();
	//model6->Draw();
	//model7->Draw();
	//if (GetKey(KEYCODE_SPACE))
	//{
	//	BSP::DrawPlanes();
	//}

}