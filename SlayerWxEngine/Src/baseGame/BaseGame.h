#ifndef BASEGAME_H
#define BASEGAME_H
#include "window/window.h"
#include "shape/Shape.h"
struct GLFWmonitor;
struct GLFWwindow;
class SlayerWxEngine_API BaseGame
{
protected:
	Window* window;
	Renderer* renderer;
private:
	void UpdateBegin();
	void UpdateEnd();
	void EngineEnd();
public:
	BaseGame();
	~BaseGame();
	int EngineInit(int width, int height, const char* title );// GLFWmonitor* monitor, GLFWwindow* share);
	int WindowInit(int width, int height, const char* title);
	void RendererInit();
	// GLFWmonitor* monitor, GLFWwindow* share);
	//void SetFramebufferSizeCallback();
	
	bool Running();
	void UpdateEngine();
	void virtual Start() = 0;
	void virtual Update() = 0;
};
#endif
