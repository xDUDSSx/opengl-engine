#include "SceneNode.h"

SceneNode::SceneNode() : SceneNode(nullptr) {}

SceneNode::SceneNode(Entity* entity)
    : entity(entity)
	, worldMatrix(glm::mat4(1.0f))
	, localMatrix(glm::mat4(1.0f))
{
    updateLocalMatrix();
}

//void SceneNode::render(PhongShader& shader, Camera& camera) const
//{
//    if (entity != nullptr) {
//        glStencilFunc(GL_ALWAYS, entity->id, 0xFF);
//
//        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//    	glUniform1i(glGetUniformLocation(shader.id, "selected"), false);
//        entity->render(shader, camera, worldMatrix);
//
//        if (entity->selected) {
//            glUniform1i(glGetUniformLocation(shader.id, "selected"), true);
//            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//            entity->render(shader, camera, worldMatrix);
//        }
//    }
//    for (auto& child : children) {
//        child->render(shader, camera);
//    }
//}

void SceneNode::matrix()
{
    updateLocalMatrix();
    updateWorldMatrix();

    if (entity != nullptr) {
        entity->worldMatrix = worldMatrix;
    }

    for (auto& child : children) {
        child->matrix();
    }
}

void SceneNode::update() {
    if (entity != nullptr) {
        entity->update();
    }
}

void SceneNode::add(std::shared_ptr<SceneNode>& node) {
    children.push_back(node);
    node->setParent(this);
}

void SceneNode::updateLocalMatrix() {
    if (entity != nullptr) {
        transform = entity->transform;
    }
    localMatrix = transform.constructMatrix();
}

void SceneNode::updateWorldMatrix() {
    if (parent != nullptr) {
        worldMatrix = parent->worldMatrix * localMatrix;
    } else {
        worldMatrix = localMatrix;
    }
}

Transform SceneNode::getTransform() const { return transform; }
void SceneNode::setTransform(const Transform& transform) { this->transform = transform; }

Entity* SceneNode::getEntity() const { return entity; }
void SceneNode::setEntity(Entity* entity) { this->entity = entity; }

SceneNode* SceneNode::getParent() const { return parent; }
void SceneNode::setParent(SceneNode* parent) { this->parent = parent; }

std::vector<std::shared_ptr<SceneNode>> SceneNode::getChildren() const { return children; }
void SceneNode::setChildren(const std::vector<std::shared_ptr<SceneNode>>& children) { this->children = children; }

