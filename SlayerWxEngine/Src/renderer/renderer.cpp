#include "renderer.h"
#include <glew.h>
#include <glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
Renderer::Renderer()
{

}

void Renderer::Draw(float* vertex, unsigned int* index, glm::mat4 modelMatrix)
{
	UpdateModelUniformShaders(modelMatrix);
	UpdateProjectUniformShaders(projection);
	UpdateViewUniformShaders(view);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 18, vertex, GL_STATIC_DRAW); //set info to buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * 3, index, GL_STATIC_DRAW); //set info to buffer
	glDrawElements(GL_TRIANGLES,3,GL_UNSIGNED_INT,0);
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

void Renderer::CallUniformShaders()
{
	modelLoc = glGetUniformLocation(program, "model");//search the model in the shader
	projectLoc = glGetUniformLocation(program, "proj");//search the project in the shader
	viewLoc = glGetUniformLocation(program, "view");//search the view in the shader
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
	//degrees in radians, window resolution, near, far
	//projection = glm::perspective(glm::radians(45.0f),800.0f/600.0f,0.1f,100.0f);
	
	//x left, x right, y down, y up, z back, z front
	projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f);// , 1.0f, -1.0f);
}
void Renderer::UpdateViewUniformShaders(glm::mat4 viewMatrix)
{
	UpdateView();
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix)); //update view in the shader

}
void Renderer::UpdateView()
{
	view = glm::lookAt(cameraPos,cameraPos+cameraFront,cameraPos+cameraUp);
}
unsigned int Renderer::CompileShader(unsigned int type, const char* shaderPath) { //first: ShaderType(Fragment, vertex)
																		//second:Dir to archive
	unsigned int id = glCreateShader(type); // Create Shader
	
	std::string sourceShaderCode; //store source archive
	
	std::ifstream sourceShaderFile; // interact to archive
	
	sourceShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	
	try {
	    sourceShaderFile.open(shaderPath); 
	    std::stringstream shaderStream;
	
		shaderStream << sourceShaderFile.rdbuf(); //conversion to StreamString
	
	    sourceShaderFile.close();
	
	    sourceShaderCode = shaderStream.str(); //conversion to string
	}
	catch (std::ifstream::failure& e) {
	    std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
	
	const char* srcCode = sourceShaderCode.c_str(); // conversion to char
	
	glShaderSource(id, 1, &srcCode, nullptr); //Set source to Shader
											// First: Shader, Second: conunt elements in the string
											// three: Specifies an array of pointers to strings containing the source
											// four: Specifies an array of string lengths
	glCompileShader(id); //Complie Shader
	
	return id;
}

void Renderer::CreateProgram(const char* vertexShaderPath, const char* fragmentShaderPath)
{
																					//first: vertex archive
																					//second: fragmentShader
	program = glCreateProgram(); // create program
	unsigned int vertex = CompileShader(GL_VERTEX_SHADER, vertexShaderPath);
	unsigned int fragment = CompileShader(GL_FRAGMENT_SHADER, fragmentShaderPath);

	glAttachShader(program, vertex); //attach with program
	glAttachShader(program, fragment); //attach with program
	glLinkProgram(program); // Link with OpenGL
	glValidateProgram(program); //validate
	glUseProgram(program); 

	glDetachShader(program, vertex); //UnAttach
	glDetachShader(program, fragment);//UnAttach
	glDeleteShader(vertex); //delete
	glDeleteShader(fragment); //delete
}
