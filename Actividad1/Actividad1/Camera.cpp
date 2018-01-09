#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera() {
	setPerspective(1.0f, 1000.0f, 60.0f, 1.0f);
	_viewMatrix = glm::inverse(_transform.getModelMatrix());
}

glm::mat4 Camera::getViewProjection() {
	return _projectionMatrix * _viewMatrix;
}

glm::mat4 Camera::getViewMatrix() {
	return _viewMatrix;
}

glm::mat4 Camera::getProjectionMatrix() {
	return _projectionMatrix;
}

glm::vec3 Camera::getPosition() {
	return _transform.getPosition();
}

void Camera::setPosition(float x, float y, float z) {
	_transform.setPosition(x, y, z);
	_viewMatrix = glm::inverse(_transform.getModelMatrix());
}

void Camera::setRotation(float x, float y, float z) {
	_transform.setRotation(x, y, z);
	_viewMatrix = glm::inverse(_transform.getModelMatrix());
}

void Camera::moveForward(float delta, bool world) {
	_transform.moveForward(delta, world);
	_viewMatrix = glm::inverse(_transform.getModelMatrix());
}

void Camera::moveUp(float delta, bool world) {
	_transform.moveUp(delta, world);
	_viewMatrix = glm::inverse(_transform.getModelMatrix());
}

void Camera::moveRight(float delta, bool world) {
	_transform.moveRight(delta, world);
	_viewMatrix = glm::inverse(_transform.getModelMatrix());
}

void Camera::yaw(float degrees) {
	_transform.rotate(0.0f, degrees, 0.0f, false);
	_viewMatrix = glm::inverse(_transform.getModelMatrix());
}

void Camera::roll(float degrees) {
	_transform.rotate(0.0f, 0.0f, degrees, false);
	_viewMatrix = glm::inverse(_transform.getModelMatrix());
}

void Camera::pitch(float degrees) {
	_transform.rotate(degrees, 0.0f, 0.0f, false);
	_viewMatrix = glm::inverse(_transform.getModelMatrix());
}

void Camera::rotate(float x, float y, float z, bool world) {
	_transform.rotate(x, y, z, world);
	_viewMatrix = glm::inverse(_transform.getModelMatrix());
}

void Camera::setPerspective(float nearPlane, float farPlane, float fieldOfView, float aspectRatio) {
	_projectionMatrix = glm::perspective(glm::radians(fieldOfView), aspectRatio, nearPlane, farPlane);
}

void Camera::setOrthigraphic(float size, float aspectRatio) {
	float xSize = aspectRatio *size;
	_projectionMatrix = glm::ortho(-xSize, xSize, -size, size, -size, size);
}