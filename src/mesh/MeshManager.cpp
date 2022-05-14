#include "MeshManager.h"
#include "../parser/ObjParser.h"

Mesh* MeshManager::load(const char* path, bool arraysOrElements, float uvScale, PhongShader& shader)
{
    std::string meshKey = (path + std::string("#") + std::to_string(arraysOrElements) + "#" + std::to_string(uvScale));
    if (meshes.find(meshKey) == meshes.end()) {
        // Mesh is not registered
        ObjParser parser(path, uvScale);
        int triangles = parser.getTriangleCount();
        std::vector<float> vbo;
        std::shared_ptr<Mesh> mesh = nullptr;
        if (arraysOrElements) {
            parser.getDrawArraysGeo(vbo);
            mesh = std::make_shared<Mesh>(MeshType::TRIANGLES_ARRAYS, vbo.data(), vbo.size(), triangles, shader);
        } else {
            std::vector<unsigned int> ebo;
            parser.getDrawElementsGeo(vbo, ebo);
            mesh = std::make_shared<Mesh>(MeshType::TRIANGLES_ELEMENTS, vbo.data(), vbo.size(), ebo.data(), ebo.size(), triangles, shader);
        }

        meshes[meshKey] = mesh;
        printf("[MESH] Registered mesh '%s'\n", meshKey.c_str());
    }
    return meshes[meshKey].get();
}
