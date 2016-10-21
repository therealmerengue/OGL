#pragma once
#include <GL\glew.h>
#include <glm\glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>

class ShaderManager
{
public:
	ShaderManager(std::string vertexShaderPath, std::string fragmentShaderPath);
	~ShaderManager();

	GLuint getProgramID() { return programID; }
	void useProgram() { glUseProgram(programID); }
	
	friend class Renderer;

private:
	GLuint vertexShaderID, fragmentShaderID, programID;
	glm::mat4 view, projection, model; //shader uniforms
	GLint modelLocation, viewLocation, projectionLocation; //uniform locations

	std::string getShaderSource(std::string path);
	bool checkShaderCompilationResult(GLuint shaderID);
	bool checkProgramLinkResult(GLuint programID);
	void compileShader(GLuint shaderID, const GLchar* shaderSource);
	int createAndCompileShader(GLenum shaderType, const GLchar* shaderSource);
	void createShaderProgram();
};

