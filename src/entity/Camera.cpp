#include "Camera.h"

#include "../Utils.h"

Camera::Camera(int width, int height, glm::vec3 pivot) {
	setPivot(pivot);

	this->transform.pos = position;

	this->width = width;
	this->height = height;
}

void Camera::matrix(const PhongShader &shader, const glm::mat4 &model)
{
	this->updateMatrix();
	shader.setTransformUniforms(model, view, projection);
}

void Camera::matrix(const SkyboxShader& shader)
{
	this->updateMatrix();
	shader.setTransformUniforms(view, projection);
}

void Camera::updateMatrix() {
	glm::mat4 cameraTransform = glm::mat4(1.0f);

	if (fpsMode) {
		cameraTransform = glm::rotate(cameraTransform, glm::radians(rotationX), glm::vec3(0.0f, 0.0f, 1.0f));
		cameraTransform = glm::rotate(cameraTransform, glm::radians(rotationY), glm::vec3(0.0f, 1.0f, 0.0f));

		const glm::vec4 cameraDir = glm::vec4(-1.0f, 0.0f, 0.0f, 0.0);
		const glm::vec4 cameraUp = glm::vec4(0.0f, 0.0f, 1.0f, 0.0);
		const glm::vec3 cameraDirTransformed = glm::vec3(cameraTransform * cameraDir);
		const glm::vec3 cameraUpTransformed = glm::vec3(cameraTransform * cameraUp);
		const glm::vec3 cameraCenter = transform.pos + cameraDirTransformed;

		const glm::vec3 cameraPosWorld = glm::vec3(parentMatrix * glm::vec4(transform.pos, 1.0));
        const glm::vec3 cameraCenterWorld = glm::vec3(parentMatrix * glm::vec4(cameraCenter, 1.0));
        const glm::vec3 cameraUpWorld = glm::vec3(parentMatrix * glm::vec4(cameraUpTransformed, 0.0));

		projection = glm::perspective(glm::radians(fov), width / (float)height, zNear, zFar);
		view = glm::lookAt(
            cameraPosWorld,
            cameraCenterWorld,
            cameraUpWorld
		);

		position = transform.pos;
		up = glm::normalize(cameraUpTransformed);
		direction = glm::normalize(cameraDirTransformed);
		right = glm::cross(up, direction);

		// Update entity transforms
        worldTransform.pos = cameraPosWorld;
        transform.rot = glm::vec3(rotationX, rotationY, 0);
	} else {
		cameraTransform = glm::translate(cameraTransform, pivot);
        cameraTransform = glm::rotate(cameraTransform, glm::radians(rotationX), glm::vec3(0.0f, 0.0f, 1.0f));
        cameraTransform = glm::rotate(cameraTransform, glm::radians(rotationY), glm::vec3(0.0f, 1.0f, 0.0f));
        cameraTransform = glm::translate(cameraTransform, glm::vec3(radius, 0.0f, 0.0f));

        const glm::vec4 cameraPos = glm::vec4(0.0f, 0.0f, 0.0f, 1.0);
        const glm::vec4 cameraUp = glm::vec4(0.0f, 0.0f, 1.0f, 0.0);
        const glm::vec3 cameraPosTransformed = glm::vec3(cameraTransform * cameraPos);
        const glm::vec3 cameraUpTransformed = glm::vec3(cameraTransform * cameraUp);

		const glm::vec3 cameraPosWorld = glm::vec3(parentMatrix * glm::vec4(cameraPosTransformed, 1.0));
        const glm::vec3 cameraPivotWorld = glm::vec3(parentMatrix * glm::vec4(pivot, 1.0));
        const glm::vec3 cameraUpWorld = glm::vec3(parentMatrix * glm::vec4(cameraUpTransformed, 0.0));

		projection = glm::perspective(glm::radians(fov), width / (float)height, zNear, zFar);
        view = glm::lookAt(
            cameraPosWorld,
            cameraPivotWorld,
            cameraUpWorld
		);

		worldPivot = cameraPivotWorld;

		position = cameraPosTransformed;
		up = glm::normalize(cameraUpTransformed);
        direction = glm::normalize(pivot - glm::vec3(cameraPosTransformed));
		right = glm::cross(up, direction);

		// Update entity transforms
		transform.pos = cameraPosTransformed;
        worldTransform.pos = cameraPosWorld;
        transform.rot = glm::vec3(rotationX, rotationY, 0);
	}
}

void Camera::mouseDrag(int dx, int dy, bool left, bool middle)
{
	if (left) {
		if (fpsMode) {
			rotationX += -dx * fpsRotateSpeed;
			rotationY += -dy * fpsRotateSpeed;
		} else {
			rotationX += -dx * rotateSpeed;
			rotationY += -dy * rotateSpeed;
		}
	}
	if (middle) {
		const float ratio = radius / zNear / 100.0f;
		pivot += glm::vec3(right) * (translateSpeed * dx * ratio);
		pivot += glm::vec3(up) * (translateSpeed * dy * ratio);
	}
}

void Camera::mouseMoved(int dx, int dy)
{
	/*if (fpsMode) {
		rotationX += -dx * fpsRotateSpeed;
		rotationY += -dy * fpsRotateSpeed;
	}*/
}

void Camera::mouseWheel(int direction, int notches) {
	if (fpsMode) {
		if (direction < 0) {
			fpsTranslateSpeed -= fpsMouseWheelSpeedDelta;
		} else {
			fpsTranslateSpeed += fpsMouseWheelSpeedDelta;
		}
		fpsTranslateSpeed = std::abs(fpsTranslateSpeed);
		fpsTranslateSpeed = std::max(fpsTranslateSpeed, 0.001f);
	} else {
		const float ratio = radius / zNear / 100.0f;
		if (direction < 0) {
			radius = radius + notches * zoomSpeed * ratio;
		} else {
			radius = radius - notches * zoomSpeed * ratio;
		}
		if (radius < 0.01f) {
			radius = 0.01f;
		}   
	}
}

void Camera::keyboard(bool w, bool s, bool a, bool d, bool shift) {
	if (fpsMode) {
		float speed = fpsTranslateSpeed;
		if (shift) {
			speed *= fpsSpeedBoostMultiplier;
		}
		if (w) {
            transform.pos += direction * speed;
		}
		if (s) {
            transform.pos -= direction * speed;
		}
		if (a) {
            transform.pos += right * speed;
		}
		if (d) {
            transform.pos -= right * speed;
		}
	}
}


void Camera::toggleFpsMode() {
	enableFpsMode(!fpsMode);
}

void Camera::enableFpsMode(bool b) {
	fpsMode = b;
	if (!fpsMode) {
        pivot = transform.pos + (direction * radius);
	}
}

void Camera::size(int width, int height) {
	this->width = width;
	this->height = height;
}

void Camera::update()
{
	
}

void Camera::render(PhongShader& shader, Camera& camera)
{

}

void Camera::render(PhongShader& shader, Camera& camera, glm::mat4 modelMatrix)
{
	
}

void Camera::create(PhongShader* shader)
{
    this->shader = shader;
}

void Camera::dispose()
{

}

void Camera::updateTransform(glm::mat4 worldMatrix, glm::mat4 parentMatrix) {
    this->worldMatrix = worldMatrix;
    this->parentMatrix = parentMatrix;
}

glm::vec3 Camera::getPivot() const { return pivot; }
void Camera::setPivot(const glm::vec3& pivot) { this->pivot = pivot; }
float Camera::getZNear() const { return zNear; }
void Camera::setZNear(float zNear) { this->zNear = zNear; }
float Camera::getZFar() const { return zFar; }
void Camera::setZFar(float zFar) { this->zFar = zFar; }
float Camera::getFov() const { return fov; }
void Camera::setFov(float fov) { this->fov = fov; }
