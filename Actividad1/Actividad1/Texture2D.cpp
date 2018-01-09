#include <iostream>
#include "Texture2D.h"
#include <IL/il.h>

Texture2D::Texture2D() {
	_textureId = 0;
}

Texture2D::~Texture2D() {
	glDeleteTextures(1, &_textureId);
}

void Texture2D::loadTexture(std::string path) {
	ILuint imageId = 0;
	const char *path1 = path.c_str();
	ilGenImages(1, &imageId);
	ilBindImage(imageId);
	ilLoadImage(path1);
	glGenTextures(1, &_textureId);
	glBindTexture(GL_TEXTURE_2D, _textureId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_FORMAT), ilGetInteger(IL_IMAGE_WIDTH),
		ilGetInteger(IL_IMAGE_HEIGHT), 0, ilGetInteger(IL_IMAGE_FORMAT), ilGetInteger(IL_IMAGE_TYPE), ilGetData());
	glBindTexture(GL_TEXTURE_2D, 0);
	ilBindImage(0);
	ilDeleteImages(1, &imageId);
}

void Texture2D::bind() {
	glBindTexture(GL_TEXTURE_2D, _textureId);
}


void Texture2D::unbind() {
	glBindTexture(GL_TEXTURE_2D, 0);
}