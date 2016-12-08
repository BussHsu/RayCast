#include "GLSLProgram.h"
#include <fstream>
#include <vector>



GLSLProgram::GLSLProgram()
	:_programID(0),
	_vertShaderID(0),
	_fragShaderID(0),
	_numAttrib(0)
{
}


GLSLProgram::~GLSLProgram()
{
}

void GLSLProgram::compileShaders(const std::string&	vertexShaderPath, const std::string& fragShaderPath)
{
	_programID = glCreateProgram();

	_vertShaderID = glCreateShader(GL_VERTEX_SHADER);
	if (_vertShaderID == 0)
		fatalerror("cannot create vert shader");

	_fragShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	if (_fragShaderID == 0)
		fatalerror("cannot create frag shader");

	compileShader(vertexShaderPath, _vertShaderID);
	compileShader(fragShaderPath, _fragShaderID);

}

void GLSLProgram::linkShaders()
{
	//Attach our shaders to our program
	glAttachShader(_programID, _vertShaderID);
	glAttachShader(_programID, _fragShaderID);

	//Link our program
	glLinkProgram(_programID);

	//Note the different functions here: glGetProgram* instead of glGetShader*.
	GLint isLinked = 0;
	glGetProgramiv(_programID, GL_LINK_STATUS, (int *)&isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &maxLength);

		//The maxLength includes the NULL character
		std::vector<char> errLog(maxLength);
		glGetProgramInfoLog(_programID, maxLength, &maxLength, &errLog[0]);

		//We don't need the program anymore.
		glDeleteProgram(_programID);
		//Don't leak shaders either.
		glDeleteShader(_vertShaderID);
		glDeleteShader(_fragShaderID);

		//Use the infoLog as you see fit.
		std::printf("%s\n", &(errLog[0]));
		fatalerror("Shader failed to link!");
		//In this simple program, we'll just leave
		return;
	}

	//Always detach shaders after a successful link.
	glDetachShader(_programID, _vertShaderID);
	glDetachShader(_programID, _fragShaderID);
	glDeleteShader(_vertShaderID);
	glDeleteShader(_fragShaderID);
}

void GLSLProgram::use()
{
	glUseProgram(_programID);
	for (int i = 0; i < _numAttrib; i++)
	{
		glEnableVertexAttribArray(i);
	}
}

void GLSLProgram::unuse()
{
	glUseProgram(0);
	for (int i = 0; i < _numAttrib; i++)
	{
		glDisableVertexAttribArray(i);
	}
}

void GLSLProgram::compileShader(const std::string& shaderPath, const GLuint id)
{
	std::fstream shaderFile(shaderPath);
	if (shaderFile.fail())
		fatalerror("cannot open vert file:" + shaderPath);

	std::string fileContent;
	std::string line;
	while (std::getline(shaderFile, line))
		fileContent += line + "\n";
	shaderFile.close();

	const char* content = fileContent.c_str();

	glShaderSource(id, 1, &content, nullptr);

	glCompileShader(id);

	GLint success = 0;
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);

	if (success == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<char> errLog(maxLength);
		glGetShaderInfoLog(id, maxLength, &maxLength, &errLog[0]);

		glDeleteShader(id);

		std::printf("%s\n", &(errLog[0]));
		fatalerror("Shader " + shaderPath + " failed to compile");
	}
}

GLint GLSLProgram::GetUniformLocation(const std::string& uniformName)
{
	GLint location = glGetUniformLocation(_programID, uniformName.c_str());
	if (location == GL_INVALID_INDEX)
		fatalerror("uniform:" + uniformName + " not found in shader");
	return location;
}

void GLSLProgram::addAttribute(const std::string& attribName)
{
	glBindAttribLocation(_programID, _numAttrib++, attribName.c_str());
}