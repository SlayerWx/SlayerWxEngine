#ifndef RENDERER_H
#define RENDERER_H
#include "window/window.h"
struct GLFWwindow;
class SlayerWxEngine_API Renderer
{
private:
public:
	Renderer();
	void BeginDraw();
	void SwapBuffer(GLFWwindow* window);
	
};
// settings
//const unsigned int SCR_WIDTH = 800;
//const unsigned int SCR_HEIGHT = 600;

#endif