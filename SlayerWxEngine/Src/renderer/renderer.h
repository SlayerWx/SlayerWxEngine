#ifndef RENDERER_H
#define RENDERER_H
#include "export/export.h"
#include "glm/glm.hpp"
#include"glm/gtc/type_ptr.hpp"
#include "shader/Shader.h"
enum class CameraDirection
{
	left,right,up,down,front,back
};
enum class CameraProjection
{
	perspective, ortho
};
class SlayerWxEngine_API Renderer
{
private:
	unsigned int modelLoc;
	unsigned int projectLoc;
	unsigned int viewLoc;
public:
	Renderer();
	~Renderer();
	void CreateShaders();
	void Draw(float* vertex, int vertexLength, unsigned int* index, int indexLength, glm::mat4 modelMatrix);
	void SpriteDraw(float* vertex, int vertexLength, unsigned int* index, int indexLength, glm::mat4 modelMatrix, bool alpha);
	unsigned int VBO = 0; // VertexBufferObject
	unsigned int VAO = 0; // VertexArrayObject
	unsigned int EBO = 0; // ElementsBufferObject
	void CreateBuffers();
	void BindBuffers();
	void DefVertexAttribute();
	void DefVertexSpriteAttribute();
	void CallUniformShaders(Shader* shader);
	void UpdateModelUniformShaders(glm::mat4 modelMatrix);
	void UpdateProjectUniformShaders(glm::mat4 projectMatrix);
	void UpdateProjection();
	void UpdateViewUniformShaders(glm::mat4 viewMatrix);
	void UpdateView();
	void SetCameraPosition(float x, float y, float z);
	void CameraMove(CameraDirection direction, float speed,float deltaTime);
	glm::mat4 projection; //size/count of pixel inside the viewport
	glm::mat4 view; //move the "camera" but really move all object in the inverse
	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	static Renderer* myRef;
	void SetStaticRenderer(Renderer* newRef);
	Renderer* GetStaticRenderer();
	CameraProjection cameraProjection;
	void UpdateCameraVectors();
	void CameraRotate(float speedX, float speedY);
	const float YAW = -90.0f;
	const float PITCH = 0.0f;
	float yaw = 0.0f;
	float pitch = 0.0f;
	glm::vec3 up = glm::vec3();
	glm::vec3 right = glm::vec3();
	Shader* pixelShader;
	Shader* textureShader;
};
// settings
//const unsigned int SCR_WIDTH = 800;
//const unsigned int SCR_HEIGHT = 600;

#endif