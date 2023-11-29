#ifndef RENDERER_H
#define RENDERER_H
#include "export/export.h"
#include "textureImporter/TextureImporter.h"
#include "glm/glm.hpp"
#include"glm/gtc/type_ptr.hpp"
#include "shader/Shader.h"
#include "camera/Camera.h"
#include "light/Light.h"
#include <iostream>   
#include <string>
#include <vector>
#include <array>
#define MAX_BONE_INFLUENCE 4

struct SlayerWxEngine_API Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoord;
	glm::vec3 tangent;
	glm::vec3 bitangent;

	int m_BoneIDs[MAX_BONE_INFLUENCE];
	float m_Weights[MAX_BONE_INFLUENCE];
};


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

	void SetMaterial(Shader* shader, glm::vec4 &color, glm::vec3 &ambient,bool diffuse, bool specular, float &shininess);

	void SetupMesh(unsigned int& vao, unsigned int& vbo, unsigned int& ebo, std::vector<Vertex>& vertices, std::vector<unsigned int>& indices);

	void DrawMesh(unsigned int& vao, unsigned int indexAmount, glm::mat4 model, std::vector<TextureData> textures, float& shininess);


	void draw_bbox(std::vector<Vertex> _vertices, glm::mat4 model, glm::mat4 m, std::array<glm::vec3, 8> verticesBoundingBox);

	//void draw_bbox(std::vector<Vertex> _vertices, glm::mat4 model, glm::mat4 m);


	bool ShowBSP = true;
};
// settings
//const unsigned int SCR_WIDTH = 800;
//const unsigned int SCR_HEIGHT = 600;
#endif