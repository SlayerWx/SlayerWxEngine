#ifndef RENDERER_H
#define RENDERER_H
#include "export/export.h"
#include "glm/glm.hpp"
#include"glm/gtc/type_ptr.hpp"
#include "shader/Shader.h"
#include "camera/Camera.h"
#include "light/Light.h"
#include <iostream>   
#include <string>   
class SlayerWxEngine_API Renderer
{
private:
	unsigned int modelLoc;
	unsigned int projectLoc;
	unsigned int viewLoc;
	unsigned int lightLoc;
public:
	Renderer();
	~Renderer();
	void CreateShaders();
	void Draw(float* vertex, int vertexLength, unsigned int* index, int indexLength, glm::mat4 modelMatrix);
	void SpriteDraw(float* vertex, int vertexLength, unsigned int* index, int indexLength, glm::mat4 modelMatrix, bool alpha);
	void MaterialDraw(float* vertex, int vertexLength, unsigned int* index, int indexLength, glm::mat4 modelMatrix, bool alpha, glm::vec4& color, glm::vec3& ambient, bool diffuse, bool specular, float& shininess);
	unsigned int VBO = 0; // VertexBufferObject
	unsigned int VAO = 0; // VertexArrayObject
	unsigned int EBO = 0; // ElementsBufferObject
	void CreateBuffers();
	void BindBuffers();
	void DefVertexAttribute();
	void DefVertexSpriteAttribute();
	void DefVertexMaterialAttribute();
	void CallUniformShaders(Shader* shader);
	void UpdateModelUniformShaders(glm::mat4 modelMatrix);
	void UpdateProjectUniformShaders(glm::mat4 projectMatrix);
	void UpdateViewUniformShaders(glm::mat4 viewMatrix);
	static Renderer* myRef;
	void SetStaticRenderer(Renderer* newRef);
	Renderer* GetStaticRenderer();
	Shader* pixelShader;
	Shader* textureShader;
	Shader* materialShader;
	Camera* cam;
	Camera* GetCamera();
	void DrawMaterialLight();
	const char* CastStringToChar(std::string str, std::string str2);

	void SetMaterial(Shader* shader, glm::vec4 &color, glm::vec3 &ambient,bool diffuse, bool specular, float &shininess);
};
// settings
//const unsigned int SCR_WIDTH = 800;
//const unsigned int SCR_HEIGHT = 600;

#endif