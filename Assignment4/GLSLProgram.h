#pragma once
#include<GL\glew.h>
#include<string>
#include"Error.h"

class GLSLProgram
{
public:
	GLSLProgram();
	~GLSLProgram();

	void compileShaders(const std::string&	vertexShaderPath, const std::string& fragShaderPath);
	void linkShaders();
	void addAttribute(const std::string& attribName);

	GLint GetUniformLocation(const std::string& uniformName);
	void use();
	void unuse();

private:
	GLuint	_programID, _vertShaderID, _fragShaderID, _numAttrib;

	void compileShader(const std::string& shaderPath, const GLuint id);

};

