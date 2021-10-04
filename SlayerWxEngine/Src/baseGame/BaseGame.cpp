#include "BaseGame.h"
#include <glew.h>
#include <glfw3.h>
BaseGame::BaseGame()
{
		window = new Window();
		renderer = new Renderer();
		renderer->SetStaticRenderer(renderer);
		input = new Input();
}
BaseGame::~BaseGame()
{
	if (window != NULL) delete window;
	if (renderer != NULL) delete renderer;
	if (input != NULL) delete input;
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
	return 0;
}
void BaseGame::RendererInit()
{
	renderer->CreateBuffers();
	renderer->BindBuffers();
	
	renderer->CreateProgram("../SlayerWxEngine/Shader/VertexShader.SWshader","../SlayerWxEngine/Shader/FragmentShader.SWshader");
	renderer->DefVertexAttribute();

	renderer->CallUniformShaders();
}
bool BaseGame::Running()
{
	return window->ShouldClose();
}

void BaseGame::UpdateBegin()
{
	window->ClearBackground();
}

void BaseGame::UpdateEnd()
{
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
		UpdateEnd();
	}
	EngineEnd();
}
bool BaseGame::GetKey(int keycode)
{
	//return input->GetKey(GLFW_KEY_A, window->GetWindow());
	//return input->GetKey(KEYCODE_A, window->GetWindow());
	return input->GetKey(keycode, window->GetWindow());
}
void BaseGame::SetCameraPosition(float x,float y, float z)
{
	renderer->SetCameraPosition(x,y,z);
}

void BaseGame::CameraMove(CameraDirection direction)
{
	renderer->CameraMove(direction);
}

void BaseGame::EngineEnd()
{
	glfwTerminate();
}
