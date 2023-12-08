#include "BaseGame.h"
#include <glew.h>
#include <glfw3.h>
#include "globalUtility/Utility/Utility.h"
BaseGame::BaseGame()
{
		window = new Window();
		renderer = new Renderer();
		renderer->SetStaticRenderer(renderer);
		input = new Input();
		myGui = new MyGui();
}
BaseGame::~BaseGame()
{
	if (window != NULL) delete window;
	if (renderer != NULL) delete renderer;
	if (input != NULL) delete input;
	if (myGui != NULL) delete myGui;
}
int BaseGame::EngineInit(int width, int height, const char* title)// GLFWmonitor* monitor, GLFWwindow* share)
{
	/* Initialize the library */
	if (!glfwInit())
		return -1;
	else if (WindowInit(width, height, title))
		return -1;
	glewInit();
	RendererInit();
	return 0;
}

int BaseGame::WindowInit(int width, int height, const char* title)// GLFWmonitor* monitor, GLFWwindow* share)
{
	window = new Window(width, height, title, NULL, NULL);
	if (!window)
	{
		return -1;
	}
	window->WindowContext();
	myGui->CreateContext(window->GetWindow());
	return 0;
}
void BaseGame::RendererInit()
{
	glEnable(GL_DEPTH_TEST);
	renderer->CreateBuffers();
	renderer->BindBuffers();
	
	renderer->CreateShaders();
	renderer->DefVertexAttribute();

	LoadBSPplanes();
}
bool BaseGame::Running()
{
	return window->ShouldClose();
}

void BaseGame::UpdateBegin()
{
	window->ClearBackground();
	myGui->BeginUpdate();
	UpdateDeltaTime();
	myGui->Inspector();
	myGui->Update();

}

void BaseGame::UpdateEnd()
{
	myGui->EndUpdate();
	window->SwapBuffer();
	/* Poll for and process events
	check what events are occurring: keyboard, mouse, window events, etc.*/
	glfwPollEvents();
}
void BaseGame::UpdateEngine()
{
	Start();
	while (Running())
	{
		UpdateBegin();
		Update();
		BSP::CalculateBSP();
		UpdateEnd();
	}
	EngineEnd();
}
bool BaseGame::GetKey(int keycode)
{
	return input->GetKey(keycode, window->GetWindow());
}
void BaseGame::SetCameraPosition(float x,float y, float z)
{
	renderer->GetCamera()->SetCameraPosition(x,y,z);
}

void BaseGame::CameraMove(CameraDirection direction, float speed)
{
	renderer->GetCamera()->CameraMove(direction,speed, DeltaTime());
}
void BaseGame::CameraRotate(float speedX, float speedY)
{
	renderer->GetCamera()->CameraRotate(speedX,speedY);
}
void BaseGame::SetCameraProjection(CameraProjection selection)
{
	renderer->GetCamera()->cameraProjection = selection;
}
CameraProjection BaseGame::GetCameraProjection()
{
	return renderer->GetCamera()->cameraProjection;
}

/// <summary>
/// if want use the camera in free format then objPosReference dont is used and distanceFromReferene is used in thirdPerson and Isometric
/// </summary>
/// <param name="type"></param>
/// <param name="objPosReference"></param>
void BaseGame::CameraFollowObj(CameraType type, glm::vec3 objPosReference, float distanceFromReferene)
{
	renderer->GetCamera()->CameraFollowObj(type, objPosReference,distanceFromReferene);
}
void BaseGame::SetShowBSP(bool isActive)
{
	Renderer::myRef->ShowBSP = isActive;
}
void BaseGame::LoadBSPplanes()
{
	ModelLoader::LoadModel("../SlayerWxEngine/assets/Planes.fbx", _structure); 
	// esto no va, tenes que cargar 1 sola escena
	//mete todos los modelos en una misma escena de blender
	
}
void BaseGame::EngineEnd()
{
	Delete();

	glfwTerminate();
}

glm::vec3 BaseGame::GetCameraPosition()
{
	return Renderer::myRef->GetCamera()->cameraPos;
}