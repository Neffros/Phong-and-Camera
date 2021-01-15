#include "myFile.h"
#include "myShader.h"


GLuint myShader::compile(std::string shader, GLenum type)
{
	GLuint id = glCreateShader(type);
	const char* shaderCode = shader.c_str();

	glShaderSource(id, 1, &shaderCode, NULL);
	glCompileShader(id);

	this->compileStatus(id);

	return id;
}

void myShader::linkProgramme(GLuint vertexShaderId, GLuint fragmentShaderId)
{
	programId = glCreateProgram();
	if (programId == 0 || programId == GL_INVALID_OPERATION)
		printf("SHADER : not able to create the shader object properly.\n Program ID : %d", programId);

	glAttachShader(programId, vertexShaderId);
	glAttachShader(programId, fragmentShaderId);
	glLinkProgram(programId);

	this->linkStatus();

}

void myShader::compileStatus(GLuint shaderId)
{
	int success;
	char infoLog[512];
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shaderId, 512, NULL, infoLog);
		printf("--- SHADER: Shader %d did not compile ! \n===\n\n===\n %s", shaderId, infoLog);
	}
	else
	{
		printf("--- SHADER: Shader %d loaded and compiled proprely\n", shaderId);
	}
}

void myShader::linkStatus()
{
	int success;
	GLint linkStatus;
	char infoLog[512];
	glGetProgramiv(programId, GL_LINK_STATUS, &linkStatus);
	if (!linkStatus)
	{
		glGetProgramInfoLog(programId, 512, NULL, infoLog);
		printf("--- SHADER: Program linking failed : \n===\n\n===\n %s", infoLog);
	}
	else {
		printf("--- SHADER: Program %d link properly\n", programId);
		glGetProgramiv(programId, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(programId, 512, NULL, infoLog);
			printf("--- SHADER: Program did not compile : \n===\n\n===\n %s", infoLog);
		}
		else
		{
			printf("--- SHADER: Program %d loaded and compiled proprely.\n", programId);
		}
	}

}

myShader::myShader(std::string vertex_path, std::string fragment_path)
{
	programId = 0;
	GLuint v_id = this->compile(File::read(vertex_path), GL_VERTEX_SHADER);
	GLuint f_id = this->compile(File::read(fragment_path), GL_FRAGMENT_SHADER);
	this->linkProgramme(v_id, f_id);
}

myShader::myShader()
{

}

void myShader::use()
{
	glUseProgram(programId);
}