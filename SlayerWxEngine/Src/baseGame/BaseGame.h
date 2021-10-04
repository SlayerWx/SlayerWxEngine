#ifndef BASEGAME_H
#define BASEGAME_H
#include "renderer/renderer.h"
#include "window/window.h"
#include "shape/Shape.h"
#include "input/Input.h"
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
	Input* input;
public:
	BaseGame();
	~BaseGame();
	int EngineInit(int width, int height, const char* title );// GLFWmonitor* monitor, GLFWwindow* share);
	int WindowInit(int width, int height, const char* title);
	void RendererInit();
	
	bool Running();
	void UpdateEngine();
	void virtual Update() = 0;
	void virtual Start() = 0;

	bool GetKey(int keycode);
	void SetCameraPosition(float x, float y, float z);
	void CameraMove(CameraDirection direction);
};
#endif
