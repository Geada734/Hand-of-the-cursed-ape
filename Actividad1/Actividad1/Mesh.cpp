#include <iostream>
#include "Mesh.h"

Mesh::Mesh() {
	_vertexArrayObject = 0;
	GLuint _positionsVertexBufferObject = 0;
	GLuint _colorsVertexBufferObject = 0;
	GLuint _normalsVertexBufferObject = 0;
	GLint _vertexCount = 0;
	_indicesBufferObject = 0;
	GLint _indicesCount = 0;
	GLuint _texCoordsVertexBufferObject = 0;
}

Mesh::~Mesh() {
	glDeleteVertexArrays(1, &_vertexArrayObject);
	glDeleteBuffers(1, &_positionsVertexBufferObject);
	glDeleteBuffers(1, &_colorsVertexBufferObject);
	_vertexCount = 0;
}

void Mesh::createMesh(GLint vertexCount) {
	_vertexCount = vertexCount;
	glGenVertexArrays(1, &_vertexArrayObject);
}

void Mesh::draw(GLenum primitive) {
	glBindVertexArray(_vertexArrayObject);
	if (_indicesCount == 0) {
		glDrawArrays(primitive, 0, _vertexCount);
	}
	else {
		glDrawElements(primitive, _indicesCount, GL_UNSIGNED_INT, nullptr);
	}
	glBindVertexArray(0);
}

void Mesh::setPositionAttribute(std::vector<glm::vec3> positions, GLenum usage, GLuint locationIndex) {
	if (positions.size() > 0 && positions.size() == _vertexCount) {
		setAttributeData(_positionsVertexBufferObject, sizeof(glm::vec3) * positions.size(), positions.data(), usage, locationIndex, 3);
	}
}

void Mesh::setTexCoordAttribute(std::vector<glm::vec2> positions, GLenum usage, GLuint locationIndex) {
	if (positions.size() > 0 && positions.size() == _vertexCount) {
		setAttributeData(_texCoordsVertexBufferObject, sizeof(glm::vec2) * positions.size(), positions.data(), usage, locationIndex, 2);
	}
}

void Mesh::setNormalAttribute(std::vector<glm::vec3> positions, GLenum usage, GLuint locationIndex) {
	if (positions.size() > 0 && positions.size() == _vertexCount) {
		setAttributeData(_normalsVertexBufferObject, sizeof(glm::vec3) * positions.size(), positions.data(), usage, locationIndex, 3);
	}
}

void Mesh::setColorAttribute(std::vector<glm::vec3> colors, GLenum usage, GLuint locationIndex) {
	if (colors.size() > 0 && colors.size() == _vertexCount) {
		setAttributeData(_colorsVertexBufferObject, sizeof(glm::vec3) * colors.size(), colors.data(), usage, locationIndex, 3);
	}
}

void Mesh::setIndices(std::vector<unsigned int> indices, GLenum usage) {
	if (indices.size() == 0)
		return;
	_indicesCount = indices.size();

	if (_indicesBufferObject)
		glDeleteBuffers(1, &_indicesBufferObject);

	glBindVertexArray(_vertexArrayObject);
	glGenBuffers(1, &_indicesBufferObject);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indicesBufferObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), indices.data(), usage);
	glBindVertexArray(0);
}

void Mesh::setAttributeData(GLuint & buffer, const GLsizeiptr size, const void * data, GLenum usage, GLuint locationIndex, const GLint components) {
	if (buffer)
		glDeleteBuffers(1, &buffer);

	glBindVertexArray(_vertexArrayObject);

	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, size, data, usage);
	glEnableVertexAttribArray(locationIndex);
	glVertexAttribPointer(locationIndex, components, GL_FLOAT, GL_FALSE, 0, nullptr);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}