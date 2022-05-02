#include "Scene.h"

#include <iostream>
#include <stack>

#include "SceneNode.h"

unsigned long Scene::counter = 0;

Scene::Scene() {
    root = std::make_shared<SceneNode>();
}

void Scene::render(PhongShader& shader, Camera& camera) {
    matrix();
    delayedRenderEntities.clear();
    for (auto& e : entities) {
        if (!e.second->opaque) {
            delayedRenderEntities.push_back(e.second.get());
        } else {
            e.second->render(shader, camera);    
        }
    }

	// Sort non opaque entities by distance from camera
    auto sortByDistanceToCamera = [&](Entity* e1, Entity* e2) -> bool {
        const float e1dist = glm::distance(camera.position, e1->transform.pos);
    	const float e2dist = glm::distance(camera.position, e2->transform.pos);
    	return e1dist >= e2dist;
    };
    std::sort(delayedRenderEntities.begin(), delayedRenderEntities.end(), sortByDistanceToCamera);

    // Render the non opaque entities in proper order
    for (auto& e : delayedRenderEntities) {
        e->render(shader, camera);
    }
}

void Scene::matrix() {
    root->matrix();
}

void Scene::update() {
	for (auto& e : entities) {
        e.second->update();
	}
}

void Scene::add(Entity* entity) {
    add(root.get(), entity);
}

void Scene::add(Entity* parent, Entity* entity)
{
    SceneNode* parentNode = findNodeForEntity(parent);
    if (parentNode != nullptr) {
        add(parentNode, entity);	    
    } else {
	    // Didnt find parent's scene node
        std::cerr << "SceneGraph: Failed to find parent node for entity id " << parent->id << "!" << std::endl;
    }
}

void Scene::add(SceneNode* parent, Entity* entity)
{
    std::shared_ptr<Entity> entityPtr = std::shared_ptr<Entity>(entity);
    auto id = counter++;
    entities[id] = entityPtr;
    entityPtr->id = id;

    add(parent, new SceneNode(entity));
}

void Scene::add(SceneNode* parent, SceneNode* child) {
    auto childPtr = std::shared_ptr<SceneNode>(child);
    parent->add(childPtr);
}

void Scene::select(unsigned long id) {
    if (entities.find(id) != entities.end()) {
        Entity* entity = entities[id].get();
        entity->selected = !entity->selected;
    }
}

SceneNode* Scene::findNodeForEntity(Entity* entity) const {
    std::stack<SceneNode*> stack;
	stack.push(root.get());
    SceneNode* targetNode = nullptr;
    while (!stack.empty()) {
        SceneNode* node = stack.top();
        stack.pop();
        for (auto& child : node->getChildren()) {
            stack.push(child.get());
        }
        if (node->getEntity() != nullptr && node->getEntity() == entity) {
            targetNode = node;
            break;
        }
	}
    return targetNode;
}


