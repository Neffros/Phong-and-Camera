#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

class myShader {

private:
	GLuint programId, vertId, fragId;

	GLuint compile(std::string shader, GLenum type);
	void linkProgramme(GLuint vertexShaderId, GLuint fragmentShaderId);
	void compileStatus(GLuint shaderId);
	void linkStatus();

public:
	myShader(std::string vertex_path, std::string fragment_path);
	myShader();
	void use();
	GLuint getProgramId() { return programId; }
	void terminate();

	void setFloat(const char* key, GLfloat value) { glUniform1f(glGetUniformLocation(programId, key), value); }
	void setColor(const char* key, GLfloat x, GLfloat y, GLfloat z) { glUniform3f(glGetUniformLocation(programId, key), x, y, z); }
};

