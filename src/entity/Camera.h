#pragma once

#include "pgr.h";
#include "../shader/PhongShader.h"

class Camera {
public:
	// Controls
    glm::vec3 pivot = glm::vec3(0.0f, 0.0f, 0.0f);

    float radius = 3.0f;
    float rotationX = 0.0f;
    float rotationY = 0.0f;

    float zoomSpeed = 1.0f;
    float rotateSpeed = 0.42f;
    float translateSpeed = 0.12f;

    // Matrices
    glm::mat4 view;
    glm::mat4 projection;

    // Info
    glm::vec3 position;
    glm::vec3 direction = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 up = glm::vec3(0.0f, 0.0f, 1.0f);
    glm::vec3 right = glm::vec3(0.0f, 1.0f, 0.0f);

    int width;
    int height;

    float zNear = 0.1f;
    float zFar = 100.0f;
    float fov = 90.0f;

    Camera(int width, int height, glm::vec3 pivot);

    void matrix(const PhongShader& shader, const glm::mat4 &model);

    void mouseDrag(int dx, int dy, bool left, bool middle);

    void mouseWheel(int direction, int notches);

    void size(int width, int height);

private:
    void update();

public:
	glm::vec3 getPivot() const;
	void setPivot(const glm::vec3& pivot);
	float getZNear() const;
	void setZNear(float zNear);
	float getZFar() const;
	void setZFar(float zFar);
	float getFov() const;
	void setFov(float fov);private:
};
