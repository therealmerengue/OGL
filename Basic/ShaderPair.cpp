#include "ShaderPair.h"

#include <iostream>
#include <fstream>
#include <sstream>

ShaderPair::ShaderPair(std::string vertexShaderPath, std::string fragmentShaderPath)
{
	vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	std::string vShaderSource = getShaderSource(vertexShaderPath);
	vertexShaderSource = vShaderSource.c_str();
	compileShader(vertexShaderID, vertexShaderSource);

	fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	std::string fShaderSource = getShaderSource(fragmentShaderPath);
	fragmentShaderSource = fShaderSource.c_str();
	compileShader(fragmentShaderID, fragmentShaderSource);

	createShaderProgram();
}

ShaderPair::~ShaderPair()
{
}

std::string ShaderPair::getShaderSource(std::string path)
{
	std::ifstream shaderFile(path);
	std::stringstream buffer;
	buffer << shaderFile.rdbuf();
	shaderFile.close();
	std::string s = buffer.str();
	return s;
}

bool ShaderPair::checkShaderCompilationResult(GLuint shaderID)
{
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << '\n';
		return false;
	}
	return true;
}

bool ShaderPair::checkProgramLinkResult(GLuint programID)
{
	GLint success;
	GLchar infoLog[512];
	glGetProgramiv(programID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(programID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		return false;
	}
	
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);

	return true;
}

void ShaderPair::compileShader(GLuint shaderID, const GLchar* shaderSource)
{
	if (shaderSource != "")
	{
		glShaderSource(shaderID, 1, &shaderSource, NULL);
		glCompileShader(shaderID);
		if (!checkShaderCompilationResult(shaderID))
			throw std::exception("Shader compilation error.");
	}
	else
		throw std::exception("Unable to get shader source");
}

void ShaderPair::createShaderProgram()
{
	programID = glCreateProgram();
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
	glLinkProgram(programID);
	if (!checkProgramLinkResult(programID))
		throw std::exception("Program link error.");
}
