#include "ShaderManager.h"

#include <iostream>
#include <fstream>
#include <sstream>

ShaderManager::ShaderManager(std::string vertexShaderPath, std::string fragmentShaderPath)
{
	vertexShaderID = createAndCompileShader(GL_VERTEX_SHADER, vertexShaderPath.c_str());
	fragmentShaderID = createAndCompileShader(GL_FRAGMENT_SHADER, fragmentShaderPath.c_str());

	createShaderProgram();

	modelLocation = glGetUniformLocation(programID, "model");
	viewLocation = glGetUniformLocation(programID, "view");
	projectionLocation = glGetUniformLocation(programID, "projection");

	useProgram();

	viewMatrix = glm::translate(viewMatrix, glm::vec3(0.0f, 0.0f, -3.0f));
	projectionMatrix = glm::perspective(45.0f, (GLfloat)800 / (GLfloat)600, 0.1f, 100.0f);

	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
}

ShaderManager::~ShaderManager()
{
}

std::string ShaderManager::getShaderSource(std::string path)
{
	std::ifstream shaderFile(path);
	std::stringstream buffer;
	buffer << shaderFile.rdbuf();
	shaderFile.close();
	std::string s = buffer.str();
	return s;
}

bool ShaderManager::checkShaderCompilationResult(GLuint shaderID)
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

bool ShaderManager::checkProgramLinkResult(GLuint programID)
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

void ShaderManager::compileShader(GLuint shaderID, const GLchar* shaderSource)
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

int ShaderManager::createAndCompileShader(GLenum shaderType, const GLchar* shaderPath)
{
	int shaderID = glCreateShader(shaderType);
	std::string shaderSource = getShaderSource(shaderPath);
	compileShader(shaderID, shaderSource.c_str());
	return shaderID;
}

void ShaderManager::createShaderProgram()
{
	programID = glCreateProgram();
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
	glLinkProgram(programID);
	if (!checkProgramLinkResult(programID))
		throw std::exception("Program link error.");
}
