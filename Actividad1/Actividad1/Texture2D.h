#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <vector>
#include <IL/il.h>


class Texture2D {
public:
	Texture2D();
	~Texture2D();
	void loadTexture(std::string path);
	void bind();
	void unbind();

private:
	GLuint _textureId;
};