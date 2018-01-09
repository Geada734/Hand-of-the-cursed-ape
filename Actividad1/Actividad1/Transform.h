#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

class Transform
{
public:
	Transform();

	glm::mat4 getModelMatrix();
	glm::vec3 getPosition();
	glm::quat getRotation();
	glm::vec3 getScale();

	void setPosition(float x, float y, float z);
	void setRotation(float x, float y, float z);
	void setScale(float x, float y, float z);

	void translate(float x, float y, float z, bool world);
	void moveForward(float delta, bool world);
	void moveUp(float delta, bool world);
	void moveRight(float delta, bool world);
	void rotate(float x, float y, float z, bool world);


	static constexpr glm::vec3 WORLD_FORWARD_VECTOR = glm::vec3(0.0f, 0.0f, 1.0f);
	static constexpr glm::vec3 WORLD_UP_VECTOR = glm::vec3(0.0f, 1.0f, 0.0f);
	static constexpr glm::vec3 WORLD_RIGHT_VECTOR = glm::vec3(1.0f, 0.0f, 0.0f);

private:
	void updateLocalVectors();
	void updateModelMatrixPosition();
	void updateModelMatrixRotationScale();

	glm::mat4 _modelMatrix;

	glm::vec3 _position;
	glm::quat _rotation;
	glm::vec3 _scale;

	glm::vec3 _forward;
	glm::vec3 _up;
	glm::vec3 _right;
};