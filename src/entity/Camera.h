#pragma once

#include "pgr.h"
#include "../shader/PhongShader.h"
#include "../shader/SkyboxShader.h"
#include "general/Entity.h"

class Camera : public Entity {
public:
	// Controls
	bool fpsMode = false;

	glm::vec3 pivot = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 worldPivot = glm::vec3(0.0f, 0.0f, 0.0f);

	float radius = 3.0f;
	float rotationX = 0.0f;
	float rotationY = 0.0f;

	float zoomSpeed = 1.0f;
	float rotateSpeed = 0.42f;
	float translateSpeed = 0.12f;

	float fpsTranslateSpeed = 0.05f;
	float fpsMouseWheelSpeedDelta = 0.001f;
	float fpsRotateSpeed = 0.2f;
	float fpsSpeedBoostMultiplier = 3.0f;
	
	// Matrices
	glm::mat4 view;
	glm::mat4 projection;

	// Info
	glm::vec3 position = glm::vec3(3.0f, 0.0f, 0.0f);
	glm::vec3 direction = glm::vec3(1.0f, 0.0f, 0.0f);
	glm::vec3 up = glm::vec3(0.0f, 0.0f, 1.0f);
	glm::vec3 right = glm::vec3(0.0f, 1.0f, 0.0f);

	int width;
	int height;

	float zNear = 0.2f;
	float zFar = 100.0f;
	float fov = 90.0f;

	Camera(int width, int height, glm::vec3 pivot);

	void matrix(const PhongShader& shader, const glm::mat4 &model);
	void matrix(const SkyboxShader& shader);

	void mouseDrag(int dx, int dy, bool left, bool middle);
	void mouseMoved(int x, int y);
	void mouseWheel(int direction, int notches);

	void keyboard(bool w, bool s, bool a, bool d, bool shift);

	void enableFpsMode(bool b);
	void toggleFpsMode();

	void size(int width, int height);

	// Entity overrides
    void render(PhongShader& shader, Camera& camera) override;
    void render(PhongShader& shader, Camera& camera, glm::mat4 modelMatrix) override;
    void update() override;
    void create(PhongShader* shader) override;
    void dispose() override;

	void updateTransform(glm::mat4 worldMatrix, glm::mat4 parentMatrix) override;

private:
	void updateMatrix();

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
