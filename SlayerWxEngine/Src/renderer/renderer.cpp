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


void Renderer::DrawMaterialLight() //to MaterialShader
{
	glUniform3fv(glGetUniformLocation(materialShader->GetProgram(), "viewPos"), 1, &cam->cameraPos[0]);
	
	glUniform3fv(glGetUniformLocation(materialShader->GetProgram(), "dirLight.direction"), 1, &DirectionalLightning::actualDirectionalLight.direction[0]);
	glUniform3fv(glGetUniformLocation(materialShader->GetProgram(), "dirLight.ambient"), 1, &DirectionalLightning::actualDirectionalLight.ambient[0]);
	glUniform3fv(glGetUniformLocation(materialShader->GetProgram(), "dirLight.diffuse"), 1, &DirectionalLightning::actualDirectionalLight.diffuse[0]);
	glUniform3fv(glGetUniformLocation(materialShader->GetProgram(), "dirLight.specular"), 1, &DirectionalLightning::actualDirectionalLight.specular[0]);
	glUniform3fv(glGetUniformLocation(materialShader->GetProgram(), "dirLight.color"), 1, &DirectionalLightning::actualDirectionalLight.color[0]);
	glUniform1i(glGetUniformLocation(materialShader->GetProgram(), "dirLight.enable"), 1);
		
	
	
	if (pointLights.size() > 0)
	{
		std::string aux;
		int i = 0;
		for (PointLight*  point : pointLights)
		{
			aux = "light[" + std::to_string(i);
			glUniform3fv(glGetUniformLocation(materialShader->GetProgram(), (aux + "].position").c_str()), 1, &point->position[0]);
			glUniform3fv(glGetUniformLocation(materialShader->GetProgram(), (aux + "].ambient").c_str()), 1, &point->ambient[0]);
			glUniform3fv(glGetUniformLocation(materialShader->GetProgram(), (aux + "].diffuse").c_str()), 1, &point->diffuse[0]);
			glUniform3fv(glGetUniformLocation(materialShader->GetProgram(), (aux + "].specular").c_str()), 1, &point->specular[0]);
			glUniform3fv(glGetUniformLocation(materialShader->GetProgram(), (aux + "].color").c_str()), 1, &point->color[0]);
			glUniform1i(glGetUniformLocation(materialShader->GetProgram(), (aux + "].enable").c_str()), point->enable);
			i++;
		}
	}

	if (spotLights.size() > 0)
	{
		std::string aux;
		int i = 0;
		for (SpotLight* spot : spotLights)
		{
			aux = "spotLight[" + std::to_string(i);
			glUniform3fv(glGetUniformLocation(materialShader->GetProgram(), (aux + "].position").c_str()), 1, &spot->position[0]);
			glUniform3fv(glGetUniformLocation(materialShader->GetProgram(), (aux + "].direction").c_str()), 1, &spot->direction[0]);
			glUniform3fv(glGetUniformLocation(materialShader->GetProgram(), (aux + "].ambient").c_str()), 1, &spot->ambient[0]);
			glUniform3fv(glGetUniformLocation(materialShader->GetProgram(), (aux + "].diffuse").c_str()), 1, &spot->diffuse[0]);
			glUniform3fv(glGetUniformLocation(materialShader->GetProgram(), (aux + "].specular").c_str()), 1, &spot->specular[0]);
			glUniform3fv(glGetUniformLocation(materialShader->GetProgram(), (aux + "].color").c_str()), 1, &spot->color[0]);

			glUniform1f(glGetUniformLocation(materialShader->GetProgram(), (aux + "].cutOff").c_str()), spot->cutOff);
			glUniform1f(glGetUniformLocation(materialShader->GetProgram(), (aux + "].outerCutOff").c_str()), spot->outerCutOff);
			glUniform1f(glGetUniformLocation(materialShader->GetProgram(), (aux + "].constant").c_str()), spot->constant);
			glUniform1f(glGetUniformLocation(materialShader->GetProgram(), (aux + "].linear").c_str()), spot->linear);
			glUniform1f(glGetUniformLocation(materialShader->GetProgram(), (aux + "].quadratic").c_str()), spot->quadratic);

			glUniform1i(glGetUniformLocation(materialShader->GetProgram(), (aux + "].enable").c_str()), spot->enable);
			i++;
		}
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

void Renderer::DrawMesh(unsigned int& vao, unsigned int indexAmount, glm::mat4 model, std::vector<TextureData> textures, float &shininess) {
	

	TextureImporter::BindClean();
	DrawMaterialLight();
	CallUniformShaders(materialShader);
	materialShader->ActiveProgram();
	DrawMaterialLight();
	
	for (unsigned int i = 0; i < textures.size(); i++) {
		std::string name = textures[i].txType;
		if (name == "texture_diffuse") {
			TextureImporter::BindTexture1(textures[i].texture);
			glUniform1i(glGetUniformLocation(materialShader->GetProgram(), "material.diffuse"), 1);
		}
		else if (name == "texture_specular") {
			glActiveTexture(GL_TEXTURE2);
			TextureImporter::BindTexture2(textures[i].texture);
			glUniform1i(glGetUniformLocation(materialShader->GetProgram(), "material.specular"), 2);
		}
	}

	UpdateModelUniformShaders(model);
	UpdateProjectUniformShaders(cam->projection);
	UpdateViewUniformShaders(cam->view);
	
	glUniform1f(glGetUniformLocation(materialShader->GetProgram(), "material.shininess"), shininess);
	
	glUniform3fv(glGetUniformLocation(materialShader->GetProgram(), "viewPos"), 1, &cam->cameraPos[0]);

	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, indexAmount, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Renderer::draw_bbox(glm::mat4 model) {
	if (!ShowBSP)
		return;

	// Cube 1x1x1, centered on origin
	GLfloat vertices[] = {
	  -0.5, -0.5, -0.5, 1.0,
	   0.5, -0.5, -0.5, 1.0,
	   0.5,  0.5, -0.5, 1.0,
	  -0.5,  0.5, -0.5, 1.0,
	  -0.5, -0.5,  0.5, 1.0,
	   0.5, -0.5,  0.5, 1.0,
	   0.5,  0.5,  0.5, 1.0,
	  -0.5,  0.5,  0.5, 1.0,
	};
	GLuint vbo_vertices;
	glGenBuffers(1, &vbo_vertices);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	GLushort elements[] = {
	  0, 1, 2, 3,
	  4, 5, 6, 7,
	  0, 4, 1, 5, 2, 6, 3, 7
	};
	GLuint ibo_elements;
	glGenBuffers(1, &ibo_elements);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_elements);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	
	glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
	int attribute_v_coord = 0;
	glEnableVertexAttribArray(attribute_v_coord);
	glVertexAttribPointer(attribute_v_coord, 4, GL_FLOAT, GL_FALSE, 0, 0 );
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_elements);
	glDrawElements(GL_LINE_LOOP, 4, GL_UNSIGNED_SHORT, 0);
	glDrawElements(GL_LINE_LOOP, 4, GL_UNSIGNED_SHORT, (GLvoid*)(4 * sizeof(GLushort)));
	glDrawElements(GL_LINES, 8, GL_UNSIGNED_SHORT, (GLvoid*)(8 * sizeof(GLushort)));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	
	glDisableVertexAttribArray(attribute_v_coord);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	
	
	glDeleteBuffers(1, &vbo_vertices);
	glDeleteBuffers(1, &ibo_elements);


}