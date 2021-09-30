#include "renderer.h"
#include <glew.h>
#include <glfw3.h>

Renderer::Renderer()
{
}

void Renderer::BeginDraw()
{
	/* Start Render here */
	glClear(GL_COLOR_BUFFER_BIT);

}
