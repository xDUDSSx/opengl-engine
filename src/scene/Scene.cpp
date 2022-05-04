#include "Scene.h"

#include <iostream>
#include <stack>

#include "SceneNode.h"

#include "../shader/GrassShader.h"
#include "../entity/Camera.h";

unsigned long Scene::counter = 1;

Scene::Scene()
{
	root = std::make_shared<SceneNode>();
}

void Scene::render(PhongShader* explicitShader, Camera& camera)
{
	matrix();
	delayedRenderEntities.clear();
	for (auto& e : entities) {
		if (!e.second->opaque) {
			delayedRenderEntities.push_back(e.second.get());
		} else {
			renderEntity(*e.second, explicitShader, camera);
		}
	}

	// Sort non opaque entities by distance from camera
	auto sortByDistanceToCamera = [&](Entity* e1, Entity* e2) -> bool {
		const float e1dist = glm::distance(camera.worldTransform.pos, e1->transform.pos);
        const float e2dist = glm::distance(camera.worldTransform.pos, e2->transform.pos);
		return e1dist > e2dist;
	};
	std::sort(delayedRenderEntities.begin(), delayedRenderEntities.end(), sortByDistanceToCamera);

	// Render the non opaque entities in proper order
	for (auto& e : delayedRenderEntities) {
		if (e->backFaceCull) {
			glEnable(GL_CULL_FACE);
			glCullFace(GL_BACK);
		}
		renderEntity(*e, explicitShader, camera);
		if (e->backFaceCull) {
			glDisable(GL_CULL_FACE);
		}
	}
	//glCullFace(GL_FRONT);
	//for (auto& e : delayedRenderEntities) {
	//    renderEntity(*e, explicitShader, camera);
	//}
}

void Scene::render(Camera& camera) {
	render(nullptr, camera);
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

void Scene::dispose()
{
	for (auto& e : entities) {
		e.second->dispose();
	}
}

void Scene::select(unsigned long id) {
	if (id <= 0)
		return;
	const bool alreadySelected = selectedEntities.find(id) != selectedEntities.end();
	clearSelection();
	if (!alreadySelected) {
		selectedEntities.insert(id);
	}
}

void Scene::clearSelection() {
	selectedEntities.clear();
}

Entity* Scene::getSelectedEntity() {
	if (selectedEntities.size() > 0) {
		return entities[*selectedEntities.begin()].get();
	}
	return nullptr;
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

void Scene::renderEntity(Entity& entity, PhongShader* explicitShader, Camera& camera) {
	PhongShader* shader = explicitShader;
	if (explicitShader == nullptr) {
		if (entity.shader != nullptr) {
			shader = entity.shader;
		}
	}
	if (shader == nullptr) {
		pgr::dieWithError("Scene::renderEntity(): shader was null! (entity id: " + std::to_string(entity.id) + ")");
		return;
	}
	shader->use();
	shader->setUniforms();

	glStencilFunc(GL_ALWAYS, entity.id, 0xFF);

	bool selected = selectedEntities.find(entity.id) != selectedEntities.end();

	if (entity.wireframe) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glUniform1i(glGetUniformLocation(shader->id, "selected"), selected);
		entity.render(*shader, camera, entity.worldMatrix);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	} else {
		glUniform1i(glGetUniformLocation(shader->id, "selected"), false);
		entity.render(*shader, camera, entity.worldMatrix);

		if (selected) {
			glUniform1i(glGetUniformLocation(shader->id, "selected"), true);
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			entity.render(*shader, camera, entity.worldMatrix);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
	}
}


