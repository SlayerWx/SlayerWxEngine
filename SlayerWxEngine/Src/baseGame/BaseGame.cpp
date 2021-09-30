#include "BaseGame.h"
#include <glew.h>
#include <glfw3.h>
BaseGame::BaseGame()
{
		window = new Window();
		renderer = new Renderer();
}
BaseGame::~BaseGame()
{
	if (window != NULL) delete window;
	if (renderer != NULL) delete renderer;
}
int BaseGame::EngineInit(int width, int height, const char* title)// GLFWmonitor* monitor, GLFWwindow* share)
{
	/* Initialize the library */
	if (!glfwInit())
		return -1;
	else if (WindowInit(width, height, title))
		return -1;
	return 0;
}

int BaseGame::WindowInit(int width, int height, const char* title)// GLFWmonitor* monitor, GLFWwindow* share)
{
	window = new Window(width,height,title,NULL,NULL);
	if (!window)
	{
		return -1;
	}
	window->WindowContext();
	return 0;
}
bool BaseGame::Running()
{
	return window->ShouldClose();
}

void BaseGame::UpdateBegin()
{
	renderer->BeginDraw();
}

void BaseGame::UpdateEnd()
{
	renderer->SwapBuffer(window->GetWindow());
	/* Poll for and process events
	check what events are occurring: keyboard, mouse, window events, etc.*/
	glfwPollEvents();
}
void BaseGame::UpdateEngine()
{
	while (Running())
	{
		UpdateBegin();
		Update();
		UpdateEnd();
	}
	EngineEnd();
}
void BaseGame::EngineEnd()
{
	glfwTerminate();
}