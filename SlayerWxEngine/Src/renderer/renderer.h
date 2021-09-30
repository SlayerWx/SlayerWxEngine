#ifndef RENDERER_H
#define RENDERER_H
#include "export/export.h"
class SlayerWxEngine_API Renderer
{
private:
public:
	Renderer();
	void BeginDraw();
	unsigned int VBO = 0; // VertexBufferObject
	unsigned int VAO = 0; // VertexArrayObject
	unsigned int EBO = 0; // ElementsBufferObject
	unsigned int program = 0; // ProgramShader
	void CreateBuffers();
	void BindBuffers();
	unsigned int CompileShader(unsigned int type, const char* shaderPath);
	void CreateProgram(const char* vertexShaderPath, const char* pixelShaderPath);
};
// settings
//const unsigned int SCR_WIDTH = 800;
//const unsigned int SCR_HEIGHT = 600;

#endif