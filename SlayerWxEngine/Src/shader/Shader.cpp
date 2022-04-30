#include "Shader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <glew.h>
using namespace std;
Shader::Shader()
{
	program = 0;
}

Shader::~Shader()
{
}

unsigned int Shader::GetProgram()
{
	return program;
}

unsigned int Shader::CompileShader(unsigned int type, const char* shaderPath) { //first: ShaderType(Fragment, vertex)
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

void Shader::CreateProgram(const char* vertexShaderPath, const char* fragmentShaderPath)
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

void Shader::ActiveProgram()
{
	glUseProgram(program);
}

