#pragma once  
#include <string>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <vector>
#include <glm/glm.hpp>

class Shader {
public:
	Shader();
	~Shader();
	void createShader(std::string path, GLenum type);
	GLuint getHandle();

private:		
	GLuint _ShaderHandle = 0;
};