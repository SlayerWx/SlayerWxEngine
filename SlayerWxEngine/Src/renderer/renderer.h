#ifndef RENDERER_H
#define RENDERER_H
#include "export/export.h"
class SlayerWxEngine_API Renderer
{
private:
public:
	Renderer();
	void BeginDraw();
	unsigned int VBO; // VertexBufferObject
	unsigned int VAO; // VertexArrayObject
	unsigned int EBO; // ElementsBufferObject
	unsigned int program; // ProgramShader
	void CreateBuffers();
	void BindBuffers();
};
// settings
//const unsigned int SCR_WIDTH = 800;
//const unsigned int SCR_HEIGHT = 600;

#endif