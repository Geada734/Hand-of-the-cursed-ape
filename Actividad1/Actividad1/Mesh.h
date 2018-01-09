#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <vector>

class Mesh
{
public:
	Mesh();
	~Mesh();

	void createMesh(GLint vertexCount);
	void draw(GLenum primitive);
	void setPositionAttribute(std::vector<glm::vec2> positions, GLenum usage, GLuint locationIndex);
	void setTexCoordAttribute(std::vector<glm::vec2> positions, GLenum usage, GLuint locationIndex);
	void setPositionAttribute(std::vector<glm::vec3> positions, GLenum usage, GLuint locationIndex);
	void setNormalAttribute(std::vector<glm::vec3> positions, GLenum usage, GLuint locationIndex);
	void setColorAttribute(std::vector<glm::vec3> colors, GLenum usage, GLuint locationIndex);
	void setColorAttribute(std::vector<glm::vec4> colors, GLenum usage, GLuint locationIndex);
	void setIndices(std::vector<unsigned int> indices, GLenum usage);

private:
	void setAttributeData(GLuint& buffer, const GLsizeiptr size, const void* data, GLenum usage, GLuint locationIndex, const GLint components);

	GLuint _vertexArrayObject;
	GLuint _positionsVertexBufferObject;
	GLuint _colorsVertexBufferObject;
	GLuint _normalsVertexBufferObject;

	GLint _vertexCount;
	GLuint _indicesBufferObject;
	GLint _indicesCount;
	GLuint _texCoordsVertexBufferObject;
};