#include "renderer.h"
#include <glew.h>
#include <glfw3.h>

#include <iostream>
Renderer* Renderer::myRef;
Renderer::Renderer()
{
	modelLoc = 0;
	projectLoc = 0;
	viewLoc = 0;
	lightLoc = 0;
	pixelShader = nullptr;
	textureShader = nullptr;
	cam = new Camera();
}

Renderer::~Renderer()
{
	if (pixelShader) delete pixelShader;
	if (textureShader) delete textureShader;
	if (materialShader) delete materialShader;
	if (cam) delete cam;
}

void Renderer::CreateShaders()
{
	pixelShader = new Shader();
	pixelShader->CreateProgram("../SlayerWxEngine/Shader/VertexShader.SWshader", "../SlayerWxEngine/Shader/FragmentShader.SWshader");
	textureShader = new Shader();
	textureShader->CreateProgram("../SlayerWxEngine/Shader/SpriteVertexShader.SWshader", "../SlayerWxEngine/Shader/SpriteFragmentShader.SWshader");
	materialShader = new Shader();
	materialShader->CreateProgram("../SlayerWxEngine/Shader/MaterialVertexShader.SWshader", "../SlayerWxEngine/Shader/MaterialFragmentShader.SWshader");
	CallUniformShaders(textureShader);
}

void Renderer::Draw(float* vertex,int vertexLength, unsigned int* index,int indexLength, glm::mat4 modelMatrix)
{

	DefVertexAttribute();
	CallUniformShaders(pixelShader);
	pixelShader->ActiveProgram();
	UpdateModelUniformShaders(modelMatrix);
	UpdateProjectUniformShaders(cam->projection);
	UpdateViewUniformShaders(cam->view);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertexLength, vertex, GL_STATIC_DRAW); //set info to buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * indexLength, index, GL_STATIC_DRAW); //set info to buffer
	glDrawElements(GL_TRIANGLES,indexLength,GL_UNSIGNED_INT,0);
}
void Renderer::SpriteDraw(float* vertex, int vertexLength, unsigned int* index, int indexLength, glm::mat4 modelMatrix,bool alpha)
{
	DefVertexSpriteAttribute();
	CallUniformShaders(textureShader);
	textureShader->ActiveProgram();
	DrawLight(textureShader);
	if (alpha) // TODO: clean pls
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	}
	else
	{

		glDisable(GL_BLEND);
	}
	UpdateModelUniformShaders(modelMatrix);
	UpdateProjectUniformShaders(cam->projection);
	UpdateViewUniformShaders(cam->view);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertexLength, vertex, GL_STATIC_DRAW); //set info to buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * indexLength, index, GL_STATIC_DRAW); //set info to buffer
	glDrawElements(GL_TRIANGLES, indexLength, GL_UNSIGNED_INT, 0);
}
void Renderer::MaterialDraw(float* vertex, int vertexLength, unsigned int* index, int indexLength, glm::mat4 modelMatrix, bool alpha,
	glm::vec4 &color,glm::vec3 &ambient,glm::vec3 &diffuse,glm::vec3 &specular,float &shininess)
{
	DefVertexMaterialAttribute();
	CallUniformShaders(materialShader);
	materialShader->ActiveProgram();
	DrawLight(materialShader);
	SetMaterial(materialShader,color,ambient,diffuse,specular,shininess);
	if (alpha) // TODO: clean pls
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	else
	{

		glDisable(GL_BLEND);
	}
	UpdateModelUniformShaders(modelMatrix);
	UpdateProjectUniformShaders(cam->projection);
	UpdateViewUniformShaders(cam->view);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertexLength, vertex, GL_STATIC_DRAW); //set info to buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * indexLength, index, GL_STATIC_DRAW); //set info to buffer
	glDrawElements(GL_TRIANGLES, indexLength, GL_UNSIGNED_INT, 0);
}
void Renderer::CreateBuffers()
{
	glGenVertexArrays(1, &VAO); // first: Specifies the number of vertex array object
								// second: the generated vertex array object names are stored
	glGenBuffers(1, &VBO); //first: the number of buffer object
	glGenBuffers(1, &EBO); //second: an array in which the generated buffer object names are stored
}

void Renderer::BindBuffers()
{
	glBindVertexArray(VAO);// Specifies the name of the vertex array to bind
	glBindBuffer(GL_ARRAY_BUFFER, VBO); //first: type buffer to bound
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); //second: the buffer
}
void Renderer::DefVertexAttribute()
{
	//first: defPosMemoryShader(Layout),second:countData, three: TypeDataAttribute, four: Normalize
	//five: countDataForVertex * SizeOf(typeData), six:StartCount (void*)0) the first point in data to count
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0); //activate first: defPosMemoryShader(Layout)

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
}
void Renderer::DefVertexSpriteAttribute()
{
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(7 * sizeof(float)));
	glEnableVertexAttribArray(2);
}
void Renderer::DefVertexMaterialAttribute()
{
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
}
void Renderer::CallUniformShaders(Shader* shader)
{
	modelLoc = glGetUniformLocation(shader->GetProgram(), "model");//search the model in the shader
	projectLoc = glGetUniformLocation(shader->GetProgram(), "proj");//search the project in the shader
	viewLoc = glGetUniformLocation(shader->GetProgram(), "view");//search the view in the shader
}
void Renderer::UpdateModelUniformShaders(glm::mat4 modelMatrix)
{
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix)); //update model in the shader
	
}
void Renderer::UpdateProjectUniformShaders(glm::mat4 projectMatrix)
{
	cam->UpdateProjection();
	glUniformMatrix4fv(projectLoc, 1, GL_FALSE, glm::value_ptr(projectMatrix)); //update project in the shader

}

void Renderer::UpdateViewUniformShaders(glm::mat4 viewMatrix)
{
	cam->UpdateView();
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix)); //update view in the shader

}

void Renderer::SetStaticRenderer(Renderer* newRef)
{
	myRef = newRef;
}
Renderer* Renderer::GetStaticRenderer()
{
	return myRef;
}

Camera* Renderer::GetCamera()
{
	return cam;
}

void Renderer::DrawLight(Shader* shader)
{
	glUniform3fv(glGetUniformLocation(shader->GetProgram(), "ambient.color"), 1, &Light::ambient[0]);
	glUniform1f(glGetUniformLocation(shader->GetProgram(), "ambient.str"), Light::ambientStrength);
	SetDirectionalLight(shader);
}
#include <iostream>
using namespace std;
void Renderer::SetMaterial(Shader* shader, glm::vec4 &color, glm::vec3 &ambient, glm::vec3 &diffuse, glm::vec3 &specular, float &shininess)
{
	glUniform4fv(glGetUniformLocation(shader->GetProgram(), "material.color"), 1, &color[0]);
	glUniform3fv(glGetUniformLocation(shader->GetProgram(), "material.ambient"), 1, &ambient[0]);
	glUniform3fv(glGetUniformLocation(shader->GetProgram(), "material.diffuse"), 1, &diffuse[0]);
	glUniform3fv(glGetUniformLocation(shader->GetProgram(), "material.specular"), 1, &specular[0]);
	glUniform1f(glGetUniformLocation(shader->GetProgram(), "material.shininess"), shininess);
}
void Renderer::SetDirectionalLight(Shader* shader)
{
	glUniform3fv(glGetUniformLocation(shader->GetProgram(), "directionalLight.direction"), 1, &Light::actualDirectionalLight.direction[0]);
	glUniform3fv(glGetUniformLocation(shader->GetProgram(), "directionalLight.color"), 1, &Light::actualDirectionalLight.color[0]);
	glUniform1f(glGetUniformLocation(shader->GetProgram(), "directionalLight.diffuseIntensity"), Light::actualDirectionalLight.diffuseIntensity);
}