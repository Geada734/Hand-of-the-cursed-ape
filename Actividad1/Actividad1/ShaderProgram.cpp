#include "ShaderProgram.h"
#include "Shader.h"
#include <vector>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

ShaderProgram::ShaderProgram() {
	_programHandle = 0;
}

ShaderProgram::~ShaderProgram() {
	deleteProgram();

}

void ShaderProgram::createProgram() {
	_programHandle = glCreateProgram();
}

void ShaderProgram::attachShader(std::string name, GLenum type) {
	std::unique_ptr<Shader> shader(new Shader);
	shader->createShader(name, type);
	_attachedShaders.push_back(std::move(shader));
}

void ShaderProgram::linkProgram() {
	for (size_t i = 0; i < _attachedShaders.size(); i++)
		glAttachShader(_programHandle, _attachedShaders[i]->getHandle());

	glLinkProgram(_programHandle);

	GLint linkSuccess = 0;
	glGetProgramiv(_programHandle, GL_LINK_STATUS, &linkSuccess);
	if (linkSuccess == GL_FALSE)
	{
		GLint logLength = 0;
		glGetProgramiv(_programHandle, GL_INFO_LOG_LENGTH, &logLength);

		if (logLength > 0)
		{
			std::vector<GLchar> linkLog(logLength);

			glGetProgramInfoLog(_programHandle, logLength, &logLength, &linkLog[0]);

			for (size_t i = 0; i < linkLog.size(); i++)
				std::cout << linkLog[i];
			std::cout << std::endl;
		}
		std::cout << "Shaders could not be linked." << std::endl;

		deleteProgram();

		return;
	}

	std::cout << "Build succeeded... " << std::endl;

	deleteAndDetachShaders();
}

void ShaderProgram::activate() {
	glUseProgram(_programHandle);
}

void ShaderProgram::deactivate() {
	glUseProgram(0);
}

void ShaderProgram::setAttribute(GLuint locationIndex, std::string name) {
	glBindAttribLocation(_programHandle, locationIndex, name.c_str());
}

void ShaderProgram::setUniformi(std::string name, int x) {
	GLint uniformLocation = glGetUniformLocation(_programHandle, name.c_str());
	glUniform1i(uniformLocation, x);
}

void ShaderProgram::setUniformf(std::string name, float x) {
	GLint uniformLocation = glGetUniformLocation(_programHandle, name.c_str());
	glUniform1f(uniformLocation, x);
}

void ShaderProgram::setUniformf(std::string name, float x, float y) {
	GLint uniformLocation = glGetUniformLocation(_programHandle, name.c_str());
	glUniform2f(uniformLocation, x, y);
}

void ShaderProgram::setUniformf(std::string name, float x, float y, float z) {
	GLint uniformLocation = glGetUniformLocation(_programHandle, name.c_str());
	glUniform3f(uniformLocation, x, y, z);
}

void ShaderProgram::setUniformf(std::string name, float x, float y, float z, float w) {
	GLint uniformLocation = glGetUniformLocation(_programHandle, name.c_str());
	glUniform4f(uniformLocation, x, y, z, w);
}

void ShaderProgram::setUniformMatrix(std::string name, glm::mat3 matrix) {
	GLint uniformLocation = glGetUniformLocation(_programHandle, name.c_str());
	glUniformMatrix3fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(matrix));
}

void ShaderProgram::setUniformMatrix(std::string name, glm::mat4 matrix) {
	GLint uniformLocation = glGetUniformLocation(_programHandle, name.c_str());
	glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(matrix));

}

void ShaderProgram::deleteAndDetachShaders() {
	for (size_t i = 0; i < _attachedShaders.size(); i++)
		glDetachShader(_programHandle, _attachedShaders[i]->getHandle());

	_attachedShaders.clear();
}

void ShaderProgram::deleteProgram() {
	deleteAndDetachShaders();
	glDeleteProgram(_programHandle);
}