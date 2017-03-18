#include "BasicShaderManager.h"

#include <iostream>
#include <fstream>
#include <sstream>

BasicShaderManager::BasicShaderManager(std::string vertexShaderPath, std::string fragmentShaderPath)
{
	vertexShaderID = createAndCompileShader(GL_VERTEX_SHADER, vertexShaderPath.c_str());
	fragmentShaderID = createAndCompileShader(GL_FRAGMENT_SHADER, fragmentShaderPath.c_str());

	createShaderProgram();

	uniformLocations["modelMatrix"] = glGetUniformLocation(programID, "model");
	uniformLocations["viewMatrix"] = glGetUniformLocation(programID, "view");
	uniformLocations["projectionMatrix"] = glGetUniformLocation(programID, "projection");

	useProgram();

	glm::mat4 viewMatrix = glm::translate(viewMatrix, glm::vec3(0.0f, 0.0f, -3.0f));
	glm::mat4 projectionMatrix = glm::perspective(45.0f, (GLfloat)800 / (GLfloat)600, 0.1f, 100.0f);

	glUniformMatrix4fv(uniformLocations["viewMatrix"], 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(uniformLocations["projectionMatrix"], 1, GL_FALSE, glm::value_ptr(projectionMatrix));
}

std::string BasicShaderManager::getShaderSource(std::string path)
{
	std::ifstream shaderFile(path);
	std::stringstream buffer;
	buffer << shaderFile.rdbuf();
	shaderFile.close();
	std::string s = buffer.str();
	return s;
}

bool BasicShaderManager::checkShaderCompilationResult(GLuint shaderID)
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

bool BasicShaderManager::checkProgramLinkResult(GLuint programID)
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

void BasicShaderManager::compileShader(GLuint shaderID, const GLchar* shaderSource)
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

int BasicShaderManager::createAndCompileShader(GLenum shaderType, const GLchar* shaderPath)
{
	int shaderID = glCreateShader(shaderType);
	std::string shaderSource = getShaderSource(shaderPath);
	compileShader(shaderID, shaderSource.c_str());
	return shaderID;
}

void BasicShaderManager::createShaderProgram()
{
	programID = glCreateProgram();
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
	glLinkProgram(programID);
	if (!checkProgramLinkResult(programID))
		throw std::exception("Program link error.");
}
