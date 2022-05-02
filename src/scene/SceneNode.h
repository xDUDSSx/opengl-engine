#pragma once

#include "pgr.h"
#include <memory>
#include <vector>

#include "../entity/general/Transform.h"
#include "../entity/general/Entity.h"

class SceneNode {
protected:
    Transform transform;
    Entity* entity = nullptr;

    SceneNode* parent = nullptr;
    std::vector<std::shared_ptr<SceneNode>> children;

    glm::mat4 worldMatrix;
    glm::mat4 localMatrix;
public:
    /**
     * \brief Creates a standalone scene node with its own transform.
     */
    SceneNode();

    /**
     * \brief Creates a scene node representing an entity and holding the entity's transform.
     * \param entity The entity to wrap with a SceneNode
     */
    explicit SceneNode(Entity* entity);

    /**
     * \brief Render the node (non-recursive)
     * \param shader Active shader
     * \param camera Active camera
     */
    void render(PhongShader& shader, Camera& camera) const;

    /**
     * \brief Update local and world matrices using parent and recursively update child nodes.
     */
    void matrix();

    /**
     * \brief Update the node (non-recursive)
     */
    void update();

    //void add(Entity& entity);
    void add(std::shared_ptr<SceneNode>& node);

protected:
    void updateLocalMatrix();
    void updateWorldMatrix();

public:
    Transform getTransform() const;
    void setTransform(const Transform& transform);

    Entity* getEntity() const;
    void setEntity(Entity* entity);

    SceneNode* getParent() const;
    void setParent(SceneNode* parent);

    std::vector<std::shared_ptr<SceneNode>> getChildren() const;
    void setChildren(const std::vector<std::shared_ptr<SceneNode>>& children);
};
