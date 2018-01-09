#pragma once  
#include <string>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <vector>
#include <memory>
#include <glm/glm.hpp>
#include "Shader.h"

class ShaderProgram {
public:
	ShaderProgram();
	~ShaderProgram();
	void createProgram();
	void attachShader(std::string name, GLenum type);
	void linkProgram();
	void activate();
	void deactivate();
	void setAttribute(GLuint locationIndex, std::string name);
	void setUniformi(std::string name, int value);
	void setUniformf(std::string name, float value);
	void setUniformf(std::string name, float x, float y);
	void setUniformf(std::string name, float x, float y, float z);
	void setUniformf(std::string name, float x, float y, float z, float w);
	void setUniformMatrix(std::string name, glm::mat3 matrix);
	void setUniformMatrix(std::string name, glm::mat4 matrix);

private:	
	GLuint _programHandle;
	std::vector<std::unique_ptr<Shader>> _attachedShaders;
	void deleteAndDetachShaders();
	void deleteProgram();
};