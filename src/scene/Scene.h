#pragma once
#include <memory>
#include <unordered_map>

class Camera;
class PhongShader;
class SceneNode;
class Entity;

/**
 * \brief Scene that manages entities and provides a scene graph implementation.
 */
class Scene {
	/** \brief Static counter used for entity id generation */
	static unsigned long counter;

    std::vector<Entity*> delayedRenderEntities;

public:
	/** \brief The scene graph root node */
	std::shared_ptr<SceneNode> root;

	/** \brief A map of all managed entities */
    std::unordered_map<unsigned long, std::shared_ptr<Entity>> entities;

	/**
	 * \brief Creates an empty scene.
	 */
	Scene();

	/**
     * \brief Render the scene (non-recursively)
     * \param shader Active shader
     * \param camera Active camera
     */
    void render(PhongShader& shader, Camera& camera);

    /**
     * \brief Recursively update local and world matrices of scene nodes.
     */
    void matrix();

    /**
     * \brief Update the scene (non-recursively)
     */
    void update();

	void add(Entity* entity);
    void add(Entity* parent, Entity* entity);
    void add(SceneNode* parent, Entity* entity);
	void add(SceneNode* parent, SceneNode* child);

	void select(unsigned long id);

private:
	SceneNode* findNodeForEntity(Entity* entity) const;
};