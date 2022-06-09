#include "Utility.h"
#include <glew.h>
#include <glfw3.h>
#include <iostream>
float deltaTime = 0.0f;
float lastFrame = 0.0f;
void SlayerWxEngine_API UpdateDeltaTime()
{
	float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
}
float SlayerWxEngine_API DeltaTime()
{
	return deltaTime;
}