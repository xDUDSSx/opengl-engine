#include "ImGuiManager.h"

#include "pgr.h"

#include "imgui.h"
#include "imgui_impl_glut.h"
#include "imgui_impl_opengl3.h"
#include "../entity/general/GameObject.h"
#include "../Game.h"
#include "../scene/SceneNode.h"
#include "../entity/Camera.h"

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

        // ImGui::SliderFloat("float", &f, 0.0f, 1.0f); // Edit 1 float using a slider from 0.0f to 1.0f
        // ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

        ImGui::Separator();

        ImGui::Checkbox("Draw normals", &Game::drawDebugNormals);
        ImGui::SliderFloat("Normals size", &Game::normalDebugShaderMagnitude, 0.01f, 1.0f);
        ImGui::SliderFloat("Wind strength", &Game::windStrength, 0.01f, 3.0f);
        ImGui::SliderFloat("Animation speed", &Game::animSpeed, 0, 60 * 50);

        ImGui::Separator();

    	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

        ImGui::End();
    }

    {
        ImGui::Begin("Active camera");

        ImGui::Text("Local coordinates");
        ImGui::BeginDisabled();
        ImGui::DragFloat3("Position", glm::value_ptr(activeCamera.transform.pos), 0.01f);
        ImGui::DragFloat3("Rotation", glm::value_ptr(activeCamera.transform.rot), 0.03f);
        ImGui::DragFloat3("Scale", glm::value_ptr(activeCamera.transform.scale), 0.005f);
        ImGui::EndDisabled();

        ImGui::Separator();

        ImGui::Text("World coordinates");
        ImGui::BeginDisabled();
        ImGui::DragFloat3("Position", glm::value_ptr(activeCamera.worldTransform.pos), 0.01f);
        ImGui::EndDisabled();

        ImGui::Separator();

        ImGui::SliderFloat("zNear", &activeCamera.zNear, 0.005f, 0.5f);
        ImGui::SliderFloat("zFar", &activeCamera.zFar, 10.0f, 200.0f);

        ImGui::End();
    }

    {
        ImGui::Begin("Scene graph");
        
        for (const auto& child : scene.root->getChildren()) {
            drawSceneGraphTree(child);    
        }

        ImGui::End();
    }

    {
        ImGui::Begin("Inspector");
        Entity* entity = scene.getSelectedEntity(); 
    	if (entity == nullptr) {
            ImGui::Text("No selection");
    	} else {
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

void ImGuiManager::drawSceneGraphTree(std::shared_ptr<SceneNode> node)
{
    ImGui::SetNextItemOpen(true, ImGuiCond_Once);
	bool b;
    if (node->getEntity() != nullptr) {
        b = ImGui::TreeNode(node->getEntity()->getName().c_str());
    } else {
        b = ImGui::TreeNode("Scene node");
    }
    if (b) {
        for (auto& child : node->getChildren()) {
            drawSceneGraphTree(child);
        }
        ImGui::TreePop();
    }
    
}

void ImGuiManager::drawEntityInfo(Entity& entity) {
    // I use "ugly" dynamic_casts here over using OOP simply because I want to strictly
    // decouple GUI from entities. This is the easiest way I can think of to do it.

    ImGui::Text("Local coordinates");
    ImGui::DragFloat3("Position", glm::value_ptr(entity.transform.pos), 0.01f);
    ImGui::DragFloat3("Rotation", glm::value_ptr(entity.transform.rot), 0.03f);
    ImGui::DragFloat3("Scale", glm::value_ptr(entity.transform.scale), 0.005f);

    ImGui::Separator();

    ImGui::Text("World coordinates");
    ImGui::BeginDisabled();
	ImGui::DragFloat3("Position", glm::value_ptr(entity.worldTransform.pos), 0.01f);
    ImGui::EndDisabled();

    ImGui::Separator();

    if (GameObject* gameObject = dynamic_cast<GameObject*>(&entity)) {
        //ImGui::SliderFloat("test", &gameObject->material->shininess, 0, 300);
    }
}
