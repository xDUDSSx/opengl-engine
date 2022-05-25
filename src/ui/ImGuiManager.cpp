#include "ImGuiManager.h"

#include "pgr.h"

#include "imgui.h"
#include "imgui_impl_glut.h"
#include "imgui_impl_opengl3.h"
#include "../entity/general/GameObject.h"
#include "../Game.h"
#include "../scene/SceneNode.h"
#include "../entity/Camera.h"
#include "../entity/lights/Light.h"
#include "../entity/lights/SunLight.h"
#include "../entity/lights/PointLight.h"
#include "../entity/lights/SpotLight.h"

class GameObject;
bool ImGuiManager::show_demo_window = false;
bool ImGuiManager::show_another_window = false;

void ImGuiManager::init() {
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    // ImGui::StyleColorsClassic();

    // Setup Platform/Renderer backends
    // FIXME: Consider reworking this example to install our own GLUT funcs + forward calls ImGui_ImplGLUT_XXX ones, instead of using ImGui_ImplGLUT_InstallFuncs().
    ImGui_ImplGLUT_Init();
    ImGui_ImplOpenGL3_Init();
}

void ImGuiManager::draw(Scene& scene, Camera& activeCamera)
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGLUT_NewFrame();

    if (show_demo_window)
        ImGui::ShowDemoWindow(&show_demo_window);

    {
        ImGui::Begin("Settings");
        ImGui::Checkbox("Demo Window", &show_demo_window);

        ImGui::Separator();

        ImGui::Checkbox("Draw normals", &Game::drawDebugNormals);
        ImGui::SliderFloat("Normals size", &Game::normalDebugShaderMagnitude, 0.01f, 1.0f);
        ImGui::Checkbox("Disable lighting", &Game::disableLighting);
        ImGui::Checkbox("Disable normal mapping", &Game::disableNormalMapping);
    	ImGui::Checkbox("Camera collision", &Game::cameraCollision);

        ImGui::Separator();

    	ImGui::SliderFloat("Wind strength", &Game::windStrength, 0.01f, 3.0f);
        ImGui::SliderFloat("Animation speed", &Game::animSpeed, 0, 60 * 50);

    	ImGui::Separator();

        ImGui::Checkbox("Fog", &Game::fogEnabled);
        ImGui::ColorEdit3("Fog color", glm::value_ptr(Game::fogColor));
        ImGui::SliderFloat("Fog near", &Game::fogNear, 1, 100);
        ImGui::SliderFloat("Fog far", &Game::fogFar, 5, 150);

        ImGui::Separator();

    	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

        ImGui::End();
    }

    {
        ImGui::Begin("Active camera");

        ImGui::Text("Local coordinates");
        ImGui::BeginDisabled();
        ImGui::DragFloat3("Position###LocalCameraPos", glm::value_ptr(activeCamera.transform.pos), 0.01f);
        ImGui::DragFloat3("Rotation###LocalCameraRot", glm::value_ptr(activeCamera.transform.rot), 0.03f);
        ImGui::DragFloat3("Scale###LocalCameraScale", glm::value_ptr(activeCamera.transform.scale), 0.005f);
        ImGui::EndDisabled();

        ImGui::Separator();

        ImGui::Text("World coordinates");
        ImGui::BeginDisabled();
        ImGui::DragFloat3("Position###WorldCameraPos", glm::value_ptr(activeCamera.worldTransform.pos), 0.01f);
        ImGui::EndDisabled();

        ImGui::Separator();

        ImGui::SliderFloat("FOV", &activeCamera.fov, 10, 130);
    	ImGui::SliderFloat("zNear", &activeCamera.zNear, 0.005f, 0.5f);
        ImGui::SliderFloat("zFar", &activeCamera.zFar, 10.0f, 300);

        ImGui::End();
    }

    {
        ImGui::Begin("Scene graph");
        
        for (const auto& child : scene.root->getChildren()) {
            drawSceneGraphTree(scene, child);    
        }

        ImGui::End();
    }

    {
        Entity* entity = scene.getSelectedEntity(); 
    	if (entity == nullptr) {
            ImGui::Begin("Inspector###Inspector");    
            ImGui::Text("No selection");
    	} else {
            ImGui::Begin(("Inspector - '" + entity->getName() + "'###Inspector").c_str());
    		drawEntityInfo(*entity);
    	}
        ImGui::End();
    }

    // Rendering
    ImGui::Render();
    ImGuiIO& io = ImGui::GetIO();
    glUseProgram(0);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiManager::dispose() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGLUT_Shutdown();
    ImGui::DestroyContext();
}

void ImGuiManager::drawSceneGraphTree(Scene& scene, std::shared_ptr<SceneNode> node)
{
    ImGui::SetNextItemOpen(true, ImGuiCond_Once);
	bool b;
    if (node->getEntity() != nullptr) {
        b = ImGui::TreeNode(node->getEntity()->getName().c_str());
        ImGui::SameLine(ImGui::GetWindowWidth() - 70);
        if (ImGui::Button("Select")) {
            scene.select(node->getEntity()->id);
        }
    } else {
        b = ImGui::TreeNode("Scene node");
    }
    if (b) {
        for (auto& child : node->getChildren()) {
            drawSceneGraphTree(scene, child);
        }
        ImGui::TreePop();
    }
    
}

void ImGuiManager::drawEntityInfo(Entity& entity) {
    // I use "ugly" dynamic_casts here over using OOP simply because I want to strictly
    // decouple GUI from entities. This is the easiest way I can think of to do it.

    ImGui::Text("Local coordinates");
    ImGui::DragFloat3("Position###LocalPos", glm::value_ptr(entity.transform.pos), 0.01f);
    ImGui::DragFloat3("Rotation###LocalRot", glm::value_ptr(entity.transform.rot), 0.03f);
    ImGui::DragFloat3("Scale###LocalScale", glm::value_ptr(entity.transform.scale), 0.005f);

    ImGui::Separator();

    ImGui::Text("World coordinates");
    ImGui::BeginDisabled();
	ImGui::DragFloat3("Position###WorldPos", glm::value_ptr(entity.worldTransform.pos), 0.01f);
    ImGui::EndDisabled();

    ImGui::Separator();

    if (GameObject* gameObject = dynamic_cast<GameObject*>(&entity)) {
        ImGui::Text("Materials");
        int uiIndex = 0;
    	for (auto& material  : gameObject->materials) {
            ImGui::ColorEdit3(("Diffuse###Diffuse" + std::to_string(uiIndex)).c_str(), glm::value_ptr(material->diffuse));
            ImGui::ColorEdit3(("Specular###Specular" + std::to_string(uiIndex)).c_str(), glm::value_ptr(material->specular));
            ImGui::ColorEdit3(("Ambient###Ambient" + std::to_string(uiIndex)).c_str(), glm::value_ptr(material->ambient));
            ImGui::SliderFloat(("Shininess###Shininess" + std::to_string(uiIndex)).c_str(), &material->shininess, 0.01f, 300);
            ImGui::Separator();
            uiIndex++;
    	}

        ImGui::Text("Textures");
        uiIndex = 0;
        for (auto& tSet : gameObject->textureSets) {
	        if (tSet->texture != nullptr) {
		        ImGui::Text("Diffuse:");
		        ImGui::SameLine();
		        ImGui::Text(tSet->texture->path);
	        }
	        if (tSet->specularMap != nullptr) {
		        ImGui::Text("Specular:");
		        ImGui::SameLine();
		        ImGui::Text(tSet->specularMap->path);
	        }
	        if (tSet->normalMap != nullptr) {
		        ImGui::Text("Normal:");
		        ImGui::SameLine();
		        ImGui::Text(tSet->normalMap->path);
                ImGui::SliderFloat(("Normal strength###Normal strength" + std::to_string(uiIndex)).c_str(), &tSet->normalStrength, 0.0f, 1.0f);
	        }
	        if (tSet->aoMap != nullptr) {
		        ImGui::Text("AO:");
		        ImGui::SameLine();
		        ImGui::Text(tSet->aoMap->path);
	        }
	        if (tSet->emissionMap != nullptr) {
		        ImGui::Text("Emission:");
		        ImGui::SameLine();
		        ImGui::Text(tSet->emissionMap->path);
	        }
	        ImGui::Separator();
            uiIndex++;
        }
    }
    if (Light* light = dynamic_cast<Light*>(&entity)) {
        ImGui::ColorEdit3("Color", glm::value_ptr(light->color));
        ImGui::SliderFloat("Intensity", &light->intensity, 0.0f, 5.0f);
        ImGui::Separator();

    	if (PointLight* pointLight = dynamic_cast<PointLight*>(&entity)) {
            ImGui::SliderFloat("Radius", &pointLight->radius, 0.0f, 100.0f);
        }

        if (SunLight* sunLight = dynamic_cast<SunLight*>(&entity)) {
            ImGui::DragFloat3("Direction", glm::value_ptr(sunLight->direction), 0.01f, -1, 1);
        }

        if (SpotLight* spotLight = dynamic_cast<SpotLight*>(&entity)) {
            ImGui::DragFloat3("Direction", glm::value_ptr(spotLight->direction), 0.01f, -1, 1);
            ImGui::SliderFloat("Radius", &spotLight->radius, 0.0f, 100.0f);
            ImGui::SliderFloat("CutoffAngle", &spotLight->cutoffAngle, 0.0f, 180.0f);
            ImGui::SliderFloat("CutoffSoftAngle", &spotLight->cutoffSoftAngle, 0.0f, 180.0f);
        }
    }
}
