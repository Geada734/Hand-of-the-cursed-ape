#include "Transform.h"

Transform::Transform()
{
	_position = glm::vec3(0.0f, 0.0f, 0.0f);
	_rotation = glm::quat(glm::vec3(0.0f, 0.0f, 0.0f));
	_scale = glm::vec3(1.0f, 1.0f, 1.0f);

	_modelMatrix = glm::mat4(1.0f);

	_forward = WORLD_FORWARD_VECTOR;
	_up = WORLD_UP_VECTOR;
	_right = WORLD_RIGHT_VECTOR;
}

glm::mat4 Transform::getModelMatrix() {
	return _modelMatrix;
}

glm::vec3 Transform::getPosition() {
	return _position;
}

glm::quat Transform::getRotation() {
	return _rotation;
}

glm::vec3 Transform::getScale() {
	return _scale;
}

void Transform::setPosition(float x, float y, float z) {
	_position = glm::vec3(x, y, z);
	updateModelMatrixPosition();
}
void Transform::setRotation(float x, float y, float z) {
	_rotation = glm::quat(glm::radians(glm::vec3(x, y, z)));
	updateModelMatrixRotationScale();
}

void Transform::setScale(float x, float y, float z) {
	_scale = glm::vec3(x, y, z);
	updateModelMatrixRotationScale();
}

void Transform::translate(float x, float y, float z, bool world) {
	if (world)
		_position += glm::vec3(x, y, z);
	else {
		_position += _forward * z;
		_position += _up * y;
		_position += _right * x;
	}
}

void Transform::moveForward(float delta, bool world) {
	if (world)
		_position += WORLD_FORWARD_VECTOR * delta;
	else
		_position += _forward * delta;
	updateModelMatrixPosition();
}

void Transform::moveUp(float delta, bool world) {
	if (world)
		_position += WORLD_UP_VECTOR * delta;
	else
		_position += _up * delta;

	updateModelMatrixPosition();
}
void Transform::moveRight(float delta, bool world) {
	if (world)
		_position += WORLD_RIGHT_VECTOR * delta;
	else
		_position += _right * delta;

	updateModelMatrixPosition();
}
void Transform::rotate(float x, float y, float z, bool world) {
	glm::quat newRotation = glm::quat(glm::radians(glm::vec3(x, y, z)));

	if (world)
		_rotation = newRotation * _rotation;
	else
		_rotation = _rotation * newRotation;
	updateModelMatrixRotationScale();
}

void Transform::updateLocalVectors() {
	glm::mat4 rotationMatrix = glm::mat4_cast(_rotation);
	_forward = glm::vec3(_modelMatrix* glm::vec4(WORLD_FORWARD_VECTOR, 0.0f));
	_up = glm::vec3(_modelMatrix* glm::vec4(WORLD_UP_VECTOR, 0.0f));
	_right = glm::cross(_up, _forward);
}

void Transform::updateModelMatrixPosition() {
	_modelMatrix[3][0] = _position.x;
	_modelMatrix[3][1] = _position.y;
	_modelMatrix[3][2] = _position.z;
}
void Transform::updateModelMatrixRotationScale() {
	_modelMatrix = glm::mat4_cast(_rotation);
	_modelMatrix[0] = _modelMatrix[0] * _scale.x;
	_modelMatrix[1] = _modelMatrix[1] * _scale.y;
	_modelMatrix[2] = _modelMatrix[2] * _scale.z;
	updateModelMatrixPosition();
	updateLocalVectors();
}