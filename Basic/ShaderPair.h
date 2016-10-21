#pragma once
#include <GL\glew.h>

#include <string>

class ShaderPair
{
public:
	ShaderPair(std::string vertexShaderPath, std::string fragmentShaderPath);
	~ShaderPair();

	GLuint getProgramID() { return programID; }

private:
	GLuint vertexShaderID, fragmentShaderID, programID;
	const GLchar* vertexShaderSource;
	const GLchar* fragmentShaderSource;

	std::string getShaderSource(std::string path);
	bool checkShaderCompilationResult(GLuint shaderID);
	bool checkProgramLinkResult(GLuint programID);
	void compileShader(GLuint shaderID, const GLchar* shaderSource);
	void createShaderProgram();
};

