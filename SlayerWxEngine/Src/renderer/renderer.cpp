#include "renderer.h"
#include <glew.h>
#include <glfw3.h>

Renderer* Renderer::myRef;
Renderer::Renderer()
{
	modelLoc = 0;
	projectLoc = 0;
	viewLoc = 0;
	projection = glm::mat4(1.0f);
	view = glm::mat4(1.0f);
	cameraProjection = CameraProjection::perspective;
	yaw = YAW;
	pitch = PITCH;
	pixelShader = nullptr;
	textureShader = nullptr;
	UpdateCameraVectors();
}

Renderer::~Renderer()
{
	if (pixelShader) delete pixelShader;
	if (textureShader) delete textureShader;
}

void Renderer::CreateShaders()
{
	pixelShader = new Shader();
	pixelShader->CreateProgram("../SlayerWxEngine/Shader/VertexShader.SWshader", "../SlayerWxEngine/Shader/FragmentShader.SWshader");
	textureShader = new Shader();
	textureShader->CreateProgram("../SlayerWxEngine/Shader/SpriteVertexShader.SWshader", "../SlayerWxEngine/Shader/SpriteFragmentShader.SWshader");
	CallUniformShaders(textureShader);
}

void Renderer::Draw(float* vertex,int vertexLength, unsigned int* index,int indexLength, glm::mat4 modelMatrix)
{

	DefVertexAttribute();
	CallUniformShaders(pixelShader);
	pixelShader->ActiveProgram();
	UpdateModelUniformShaders(modelMatrix);
	UpdateProjectUniformShaders(projection);
	UpdateViewUniformShaders(view);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertexLength, vertex, GL_STATIC_DRAW); //set info to buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * indexLength, index, GL_STATIC_DRAW); //set info to buffer
	glDrawElements(GL_TRIANGLES,indexLength,GL_UNSIGNED_INT,0);
}
void Renderer::SpriteDraw(float* vertex, int vertexLength, unsigned int* index, int indexLength, glm::mat4 modelMatrix,bool alpha)
{

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
	UpdateProjectUniformShaders(projection);
	UpdateViewUniformShaders(view);
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
	UpdateProjection();
	glUniformMatrix4fv(projectLoc, 1, GL_FALSE, glm::value_ptr(projectMatrix)); //update project in the shader

}
void Renderer::UpdateProjection()
{

	switch (cameraProjection)
	{
	default:
	case CameraProjection::perspective:
		//degrees in radians, window resolution, near, far
		projection = glm::perspective(glm::radians(45.0f), 800.0f/ 600.0f, 0.001f, 100.0f);
		break;
	case CameraProjection::ortho:
		//x left, x right, y down, y up, near, far
		projection = glm::ortho(-1.5f, 1.5f, -1.0f, 1.0f, 0.1f, 100.0f);
		break;
	}
}
void Renderer::UpdateViewUniformShaders(glm::mat4 viewMatrix)
{
	UpdateView();
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix)); //update view in the shader

}
void Renderer::UpdateView()
{
	view = glm::lookAt(cameraPos,cameraPos+cameraFront,cameraUp);
}
void Renderer::SetCameraPosition(float x,float y, float z)
{
	cameraPos.x = x;
	cameraPos.y = y;
	cameraPos.z = z;
}
void Renderer::CameraMove(CameraDirection direction,float speed , float deltaTime)
{
	switch (direction)
	{
	case CameraDirection::front:
		cameraPos += (speed * deltaTime) * cameraFront;
		break;
	case CameraDirection::back:
		cameraPos -= (speed * deltaTime) * cameraFront;
		break;
	case CameraDirection::up:
		cameraPos += (speed * deltaTime) * cameraUp;
		break;
	case CameraDirection::down:
		cameraPos -= (speed * deltaTime) * cameraUp;
		break;
	case CameraDirection::left:
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * (speed * deltaTime);
		break;
	case CameraDirection::right:
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * (speed * deltaTime);
		break;
	}
	
}
void Renderer::UpdateCameraVectors()
{
	// calculate the new Front vector
	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(front);
	// also re-calculate the Right and Up vector
	right = glm::normalize(glm::cross(cameraFront, cameraUp));  // normalize the vectors, because their length gets 
									//closer to 0 the more you look up or down which results in slower movement.
	up = glm::normalize(glm::cross(right, cameraFront));
}
void Renderer::CameraRotate(float speedX,float speedY)
{
	yaw += speedX;
	pitch -= speedY;
	if (pitch >= 89.1f)
		pitch = -89.0f;
	if (pitch < -89.1f)
		pitch = 89.0f;
	UpdateCameraVectors();
	
}
void Renderer::SetStaticRenderer(Renderer* newRef)
{
	myRef = newRef;
}
Renderer* Renderer::GetStaticRenderer()
{
	return myRef;
}