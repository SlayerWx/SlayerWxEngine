#include "renderer.h"
#include <glew.h>
#include <glfw3.h>

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
	BindBuffers();
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
	BindBuffers();
	DefVertexSpriteAttribute();
	CallUniformShaders(textureShader);
	textureShader->ActiveProgram();
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
	glm::vec4 &color,glm::vec3 &ambient,bool diffuse,bool specular,float &shininess)
{
	BindBuffers();
	DefVertexMaterialAttribute();
	CallUniformShaders(materialShader);
	materialShader->ActiveProgram();
	DrawMaterialLight();
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

#include <stdlib.h>
const char* Renderer::CastStringToChar(std::string str,std::string str2)
{

	std::string auxS = str+str2;
	char* ccx = new char[auxS.length()-1];
	char* a = new char(*(auxS.c_str()));
	//std::copy(auxS.begin(),auxS.end(),ccx); 
#pragma warning(disable : 4996)
	//strcpy(a,auxS.c_str());
		return (const char*)a;
}

void Renderer::DrawMaterialLight() //to MaterialShader
{

	glUniform3fv(glGetUniformLocation(materialShader->GetProgram(), "viewPos"), 1, &cam->cameraPos[0]);
	
	
	if (DirectionalLightning::actualDirectionalLight.enable == 1)
	{
		glUniform3fv(glGetUniformLocation(materialShader->GetProgram(), "dirLight.direction"), 1, &DirectionalLightning::actualDirectionalLight.direction[0]);
		glUniform3fv(glGetUniformLocation(materialShader->GetProgram(), "dirLight.ambient"), 1, &DirectionalLightning::actualDirectionalLight.ambient[0]);
		glUniform3fv(glGetUniformLocation(materialShader->GetProgram(), "dirLight.diffuse"), 1, &DirectionalLightning::actualDirectionalLight.diffuse[0]);
		glUniform3fv(glGetUniformLocation(materialShader->GetProgram(), "dirLight.specular"), 1, &DirectionalLightning::actualDirectionalLight.specular[0]);
		glUniform3fv(glGetUniformLocation(materialShader->GetProgram(), "dirLight.color"), 1, &DirectionalLightning::actualDirectionalLight.color[0]);
		glUniform1i(glGetUniformLocation(materialShader->GetProgram(), "dirLight.enable"), 1);
		
	}
	//int aux = 0;
	//for(PointLight* point : pointLights)
	//{
	//	std::cout << CastStringToChar("light[" + std::to_string(aux), "].position") << std::endl;
	//	if (point->enable == 1)
	//	{
	//		glUniform3fv(glGetUniformLocation(materialShader->GetProgram(), CastStringToChar("light[" + std::to_string(aux), "].position")), 1, &point->position[0]);
	//		glUniform3fv(glGetUniformLocation(materialShader->GetProgram(), CastStringToChar("light["+ std::to_string(aux), "].ambient")), 1, &point->ambient[0]);
	//		glUniform3fv(glGetUniformLocation(materialShader->GetProgram(), CastStringToChar("light["+ std::to_string(aux), "].diffuse")), 1, &point->diffuse[0]);
	//		glUniform3fv(glGetUniformLocation(materialShader->GetProgram(), CastStringToChar("light["+ std::to_string(aux), "].specular")), 1, &point->specular[0]);
	//		glUniform3fv(glGetUniformLocation(materialShader->GetProgram(), CastStringToChar("light["+ std::to_string(aux), "].color")), 1, &point->color[0]);
	//		glUniform1i(glGetUniformLocation(materialShader->GetProgram(), CastStringToChar("light["+ std::to_string(aux), "].enable")), 1);
	//	}
	//	aux++;
	//}
	//aux = 0;
	if (Epoint0->enable == 1)
	{
		glUniform3fv(glGetUniformLocation(materialShader->GetProgram(), "light[0].position"), 1, &Epoint0->position[0]);
		glUniform3fv(glGetUniformLocation(materialShader->GetProgram(), "light[0].ambient"), 1, &Epoint0->ambient[0]);
		glUniform3fv(glGetUniformLocation(materialShader->GetProgram(), "light[0].diffuse"), 1, &Epoint0->diffuse[0]);
		glUniform3fv(glGetUniformLocation(materialShader->GetProgram(), "light[0].specular"), 1, &Epoint0->specular[0]);
		glUniform3fv(glGetUniformLocation(materialShader->GetProgram(), "light[0].color"), 1, &Epoint0->color[0]);
		glUniform1i(glGetUniformLocation(materialShader->GetProgram(), "light[0].enable"), 1);
	}
	//for (SpotLight* spot : spotLights)
	//{
	//	if (spot->enable == 1)
	//	{
	//		glUniform3fv(glGetUniformLocation(materialShader->GetProgram(), CastStringToChar("spotLight[" + aux,"].position")), 1, &spot->position[0]);
	//		glUniform3fv(glGetUniformLocation(materialShader->GetProgram(), CastStringToChar("spotLight[" + aux,"].direction")), 1, &spot->direction[0]);
	//		glUniform3fv(glGetUniformLocation(materialShader->GetProgram(), CastStringToChar("spotLight[" + aux, "].ambient")), 1, &spot->ambient[0]);
	//		glUniform3fv(glGetUniformLocation(materialShader->GetProgram(), CastStringToChar("spotLight[" + aux, "].diffuse")), 1, &spot->diffuse[0]);
	//		glUniform3fv(glGetUniformLocation(materialShader->GetProgram(), CastStringToChar("spotLight[" + aux, "].specular")), 1, &spot->specular[0]);
	//		glUniform3fv(glGetUniformLocation(materialShader->GetProgram(), CastStringToChar("spotLight[" + aux, "].color")), 1, &spot->color[0]);
	//
	//		glUniform1f(glGetUniformLocation(materialShader->GetProgram(), CastStringToChar("spotLight[" + aux, "].cutOff")),spot->cutOff);
	//		glUniform1f(glGetUniformLocation(materialShader->GetProgram(), CastStringToChar("spotLight[" + aux, "].outerCutOff")),spot->outerCutOff);
	//		glUniform1f(glGetUniformLocation(materialShader->GetProgram(), CastStringToChar("spotLight[" + aux, "].constant")), spot->constant);
	//		glUniform1f(glGetUniformLocation(materialShader->GetProgram(), CastStringToChar("spotLight[" + aux, "].linear")), spot->linear);
	//		glUniform1f(glGetUniformLocation(materialShader->GetProgram(), CastStringToChar("spotLight[" + aux, "].quadratic")), spot->quadratic);
	//
	//		glUniform1i(glGetUniformLocation(materialShader->GetProgram(), CastStringToChar("spotLight[" + aux, "].enable")), 1);
	//	}
	//	aux++;
	//}
	if (Epoint0->enable == 1)
	{
		glUniform3fv(glGetUniformLocation(materialShader->GetProgram(), "spotLight[0].position"), 1, &spot0->position[0]);
		glUniform3fv(glGetUniformLocation(materialShader->GetProgram(), "spotLight[0].direction"), 1, &spot0->direction[0]);
		glUniform3fv(glGetUniformLocation(materialShader->GetProgram(), "spotLight[0].ambient"), 1, &spot0->ambient[0]);
		glUniform3fv(glGetUniformLocation(materialShader->GetProgram(), "spotLight[0].diffuse"), 1, &spot0->diffuse[0]);
		glUniform3fv(glGetUniformLocation(materialShader->GetProgram(), "spotLight[0].specular"), 1, &spot0->specular[0]);
		glUniform3fv(glGetUniformLocation(materialShader->GetProgram(), "spotLight[0].color"), 1, &spot0->color[0]);
	
		glUniform1f(glGetUniformLocation(materialShader->GetProgram(), "spotLight[0].cutOff"), spot0->cutOff);
		glUniform1f(glGetUniformLocation(materialShader->GetProgram(), "spotLight[0].outerCutOff"), spot0->outerCutOff);
		glUniform1f(glGetUniformLocation(materialShader->GetProgram(), "spotLight[0].constant"), spot0->constant);
		glUniform1f(glGetUniformLocation(materialShader->GetProgram(), "spotLight[0].linear"), spot0->linear);
		glUniform1f(glGetUniformLocation(materialShader->GetProgram(), "spotLight[0].quadratic"), spot0->quadratic);
																			  
		glUniform1i(glGetUniformLocation(materialShader->GetProgram(), "spotLight[0].enable"), 1);
	}
}
void Renderer::SetMaterial(Shader* shader, glm::vec4 &color, glm::vec3 &ambient, bool diffuse, bool specular, float &shininess)
{
	glUniform4fv(glGetUniformLocation(shader->GetProgram(), "material.color"), 1, &color[0]);
	glUniform3fv(glGetUniformLocation(shader->GetProgram(), "material.ambient"), 1, &ambient[0]);
	
	glUniform1i(glGetUniformLocation(shader->GetProgram(), "material.diffuse"), diffuse);
	
	if(specular) glUniform1i(glGetUniformLocation(shader->GetProgram(), "material.specular"), 2);
	else glUniform1i(glGetUniformLocation(shader->GetProgram(), "material.specular"), 0);

	glUniform1f(glGetUniformLocation(shader->GetProgram(), "material.shininess"), shininess);

}
void Renderer::SetupMesh(unsigned int& vao, unsigned int& vbo, unsigned int& ebo, std::vector<Vertex>& vertices, std::vector<unsigned int>& indices
) {
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	glBindVertexArray(vao);
	// load data into vertex buffers
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	// A great thing about structs is that their memory layout is sequential for all its items.
	// The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
	// again translates to 3/2 floats which translates to a byte array.
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	// set the vertex attribute pointers
	// vertex Positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	// vertex normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	// vertex texture coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));
	// vertex tangent
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tangent));
	// vertex bitangent
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, bitangent));
	// ids
	glEnableVertexAttribArray(5);
	glVertexAttribIPointer(5, 4, GL_INT, sizeof(Vertex), (void*)offsetof(Vertex, m_BoneIDs));

	// weights
	glEnableVertexAttribArray(6);
	glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, m_Weights));
	glBindVertexArray(0);
}

void Renderer::DrawMesh(unsigned int& vao, unsigned int indexAmount, glm::mat4 model, std::vector<TextureData> textures,
	glm::vec4 &color, glm::vec3 &ambient, float &shininess) {
	
	DrawMaterialLight();
	CallUniformShaders(materialShader);
	materialShader->ActiveProgram();
	DrawMaterialLight();
	
	for (unsigned int i = 0; i < textures.size(); i++) {
		std::string name = textures[i].txType;
		if (name == "texture_diffuse") {
			TextureImporter::BindTexture(textures[i].texture);
			TextureImporter::BindTexture1(textures[i].texture);
			glUniform1i(glGetUniformLocation(materialShader->GetProgram(), "material.diffuse"), 1);
		}
		else if (name == "texture_specular") {
			glActiveTexture(GL_TEXTURE2);
			TextureImporter::BindTexture2(textures[i].texture);
			glUniform1i(glGetUniformLocation(materialShader->GetProgram(), "material.specular"), 2);
		}
	}

	
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE,glm::value_ptr(model));
	
	glUniform4fv(glGetUniformLocation(materialShader->GetProgram(), "material.color"), 1, &color[0]);
	glUniform3fv(glGetUniformLocation(materialShader->GetProgram(), "material.ambient"), 1, &ambient[0]);
	glUniform1f(glGetUniformLocation(materialShader->GetProgram(), "material.shininess"), shininess);
	
	glUniform3fv(glGetUniformLocation(materialShader->GetProgram(), "viewPos"), 1, &cam->cameraPos[0]);
	
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, indexAmount, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}