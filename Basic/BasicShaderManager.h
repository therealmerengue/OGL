#pragma once
#include <GL\glew.h>
#include <glm\glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <map>

class BasicShaderManager
{
public:
	BasicShaderManager(std::string vertexShaderPath, std::string fragmentShaderPath);
	virtual ~BasicShaderManager() {}

	GLuint getProgramID() { return programID; }
	void useProgram() { glUseProgram(programID); }
	GLint getUniformLocation(std::string uniform) { return uniformLocations[uniform]; }

protected:
	std::map<std::string, GLint> uniformLocations;

private:
	GLuint vertexShaderID, fragmentShaderID, programID;

	std::string getShaderSource(std::string path);
	bool checkShaderCompilationResult(GLuint shaderID);
	bool checkProgramLinkResult(GLuint programID);
	void compileShader(GLuint shaderID, const GLchar* shaderSource);
	int createAndCompileShader(GLenum shaderType, const GLchar* shaderSource);
	void createShaderProgram();
};

