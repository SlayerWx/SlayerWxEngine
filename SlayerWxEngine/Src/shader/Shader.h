#ifndef SHADER_H
#define SHADER_H
#include "export/export.h"
class SlayerWxEngine_API Shader
{
public:
	Shader();
	~Shader();
	unsigned int GetProgram();
	void CreateProgram(const char* vertexShaderPath, const char* fragmentShaderPath);
	void ActiveProgram();
private:
	unsigned int program;
	unsigned int CompileShader(unsigned int type, const char* shaderPath);
};
#endif