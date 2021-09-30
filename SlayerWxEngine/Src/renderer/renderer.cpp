#include "renderer.h"
#include <glew.h>
#include <glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
Renderer::Renderer()
{
}

void Renderer::BeginDraw()
{

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
unsigned int CompileShader(unsigned int type, const char* shaderPath) { //first: ShaderType(Fragment, vertex)
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

void Renderer::CreateProgram(const char* vertexShaderPath, const char* pixelShaderPath) {
																					//first: vertex archive
																					//second: fragmentShader
	program = glCreateProgram(); // create program
	unsigned int vertex = CompileShader(GL_VERTEX_SHADER, vertexShaderPath);
	unsigned int fragment = CompileShader(GL_FRAGMENT_SHADER, pixelShaderPath);

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
