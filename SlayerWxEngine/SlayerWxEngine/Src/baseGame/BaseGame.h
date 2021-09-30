#ifndef BASEGAME_H
#define BASEGAME_H
#include "renderer/renderer.h"
struct GLFWmonitor;
struct GLFWwindow;
class SlayerWxEngine_API BaseGame
{
private:
	Window* window;
	Renderer* renderer;
	void UpdateBegin();
	void UpdateEnd();
	void EngineEnd();
public:
	BaseGame();
	int EngineInit();
	int WindowInit(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share);
	//void SetFramebufferSizeCallback();
	bool Running();
	void UpdateEngine();
	void virtual Update() = 0;
	void virtual Draw() = 0;
};
#endif

