#ifndef BASEGAME_H
#define BASEGAME_H
#include "renderer/renderer.h"
#include "window/window.h"
#include "shape/Shape.h"
#include "sprite/Sprite.h"
#include "cube/Cube.h"
#include "bsp/BSP.h"
#include "input/Input.h"
#include "export/export.h"
#include "gui/MyGui.h"
#include "model/ModelLoader.h"
#include "model/Model.h"
struct GLFWmonitor;
struct GLFWwindow;
class SlayerWxEngine_API BaseGame
{
private:
	Window* window;
	Renderer* renderer;
	MyGui* myGui;
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
	void virtual Delete() = 0;
	bool GetKey(int keycode);
	void SetCameraPosition(float x, float y, float z);
	void CameraMove(CameraDirection direction, float speed);
	void CameraRotate(float speedX, float speedY);
	void SetCameraProjection(CameraProjection selection);
	CameraProjection GetCameraProjection();
	void CameraFollowObj(CameraType type, glm::vec3 objPosReference, float distanceFromReferene);
	void SetShowBSP(bool isActive);
	void LoadBSPplanes();
	ModelStruct _structure;
	glm::vec3 GetCameraPosition();
};
#endif
