#ifndef MYGUI_H
#define MYGUI_H
#include "export/export.h"
#include "window/window.h"
#include "gui/imgui.h"
#include "gui/imgui_impl_glfw_gl3.h"
#include "glm/glm.hpp"
#include "entity/Entity.h"
#include "dataManager/DataManager.h"
class SlayerWxEngine_API MyGui
{
public:
	MyGui();
	~MyGui();
	void CreateContext(GLFWwindow* window);
	void BeginUpdate();
	void EndUpdate();
	void EndEngine();
	void Update();
	void Inspector();
};
#endif