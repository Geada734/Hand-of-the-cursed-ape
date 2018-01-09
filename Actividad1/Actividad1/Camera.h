#pragma once

#include <glm/glm.hpp>
#include "Transform.h"

class Camera {
public:
	Camera();

	glm::mat4 getViewProjection();
	glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMatrix();
	glm::vec3 getPosition();

	void setPosition(float x, float y, float z);
	void setRotation(float x, float y, float z);

	void moveForward(float delta, bool world = false);
	void moveUp(float delta, bool world = false);
	void moveRight(float delta, bool world = false);

	void yaw(float degrees);	
	void roll(float degrees);	
	void pitch(float degrees);	
	void rotate(float x, float y, float z, bool world = false);

	void setPerspective(float nearPlane, float farPlane, float fieldOfView, float aspectRatio);
	void setOrthigraphic(float size, float aspectRatio);

private:

	Transform _transform;
	glm::mat4 _viewMatrix;
	glm::mat4 _projectionMatrix;


};