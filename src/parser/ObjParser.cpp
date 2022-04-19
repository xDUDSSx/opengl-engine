#include "ObjParser.h"

#include <iostream>
#include <sstream>
#include <fstream>

#include "../Utils.h"

ObjParser::ObjParser(const char* path)
{
    parseObj(path);
}

// Only parses obj files with triangle faces, so the mesh needs to be triangulated prior to export.
void ObjParser::parseObj(const char* path)
{
    std::ifstream file(path);
    std::vector<std::string> words;
    std::string line;
    int index = 0;
    while (std::getline(file, line)) {
        index++;
        std::istringstream iss(line);
        words.clear();
        while (iss) {
            std::string word;
            iss >> word;
            if (!iss) {
                break;
            }
            words.push_back(word);
        }
        if (words.empty()) {
            continue;
        }

        if (words[0] == "v") {
            float x = std::stof(words[1]);
            float y = std::stof(words[2]);
            float z = std::stof(words[3]);
            vertices.push_back(glm::vec3(x, y, z));
        } else if (words[0] == "vt") {
            float u = std::stof(words[1]);
            float v = std::stof(words[2]);
            uvs.push_back(glm::vec2(u, v));
        } else if (words[0] == "vn") {
            float x = std::stof(words[1]);
            float y = std::stof(words[2]);
            float z = std::stof(words[3]);
            normals.push_back(glm::vec3(x, y, z));
        } else if (words[0] == "f") {
            if (words.size() != 4) {
                std::cerr << "Face is not a triangle at index " << index << "!" << std::endl;
                break;
            }
            std::vector<int> vs;
            std::vector<int> vts;
            std::vector<int> vns;
            for (int i = 1; i < words.size(); i++) {
                // Three v/vt/vn or v//vn
                std::vector<std::string> tokens;
                Utils::tokenize(words[i], '/', tokens);
                if (tokens.size() == 3) {
                    vs.push_back(std::stoi(tokens[0]));
                    vts.push_back(std::stoi(tokens[1]));
                    vns.push_back(std::stoi(tokens[2]));
                } else if (tokens.size() == 2) {
                    vs.push_back(std::stoi(tokens[0]));
                    vns.push_back(std::stoi(tokens[1]));
                } else {
                    std::cerr << "Invalid face attribute count (" << tokens.size() << ") at index " << index << "!" << std::endl;
                    break;
                }
            }
            triangleCount++;
            vertexIndices.push_back({ vs[0], vs[1], vs[2]});
            uvIndices.push_back({vts[0], vts[1], vts[2]});
            normalIndices.push_back({vns[0], vns[1], vns[2]});
        }
        //for (auto& w : words) {
        //    std::cout << w << " ";
        //}
        //std::cout << std::endl;
    }
    std::cout << "Loaded obj from file '" << path << "'" << std::endl;
}

void ObjParser::getDrawArraysGeo(std::vector<float> &vbo)
{
    vbo.clear();
    vbo.reserve(vertexIndices.size() * 3 * 8);

    for (int i = 0; i < vertexIndices.size(); i++) {
        auto v = vertexIndices[i];
        auto t = uvIndices[i];
        auto n = normalIndices[i];

        for (int k = 0; k < 3; k++) {
            glm::vec3 vertex = vertices[v[k] - 1];
            vbo.push_back(vertex.x);
            vbo.push_back(vertex.y);
            vbo.push_back(vertex.z);

            glm::vec2 uv = uvs[t[k] - 1];
            vbo.push_back(uv.x);
            vbo.push_back(uv.y);

            glm::vec3 normal = normals[n[k] - 1];
            vbo.push_back(normal.x);
            vbo.push_back(normal.y);
            vbo.push_back(normal.z);
        }
    }
}

void ObjParser::getDrawElementsGeo(std::vector<float>& vbo, std::vector<unsigned int>& ebo) {
	vbo.clear();
    vbo.reserve(vertexIndices.size() * 1 * 8);

    ebo.clear();

    vboEntries.clear();
    vboEntries.reserve(vertices.size());

    //We need to preserve order here so we just set attributes of a fixed order vertex array
    for (auto& v : vertices) {
        vboEntries.push_back(ObjVertex(v));
    }

    for (int i = 0; i < vertexIndices.size(); i++) {
        auto v = vertexIndices[i];
        auto t = uvIndices[i];
        auto n = normalIndices[i];

        for (int k = 0; k < 3; k++) {
            ObjVertex* vertex = &vboEntries[v[k] - 1];
            ebo.push_back(v[k] - 1);
            vertex->uv = uvs[t[k] - 1];
            vertex->normal = normals[n[k] - 1];
        }
    }

    //Transform vboEntries to a vbo vector
    for (auto& e : vboEntries) {
        vbo.push_back(e.vertex.x);
        vbo.push_back(e.vertex.y);
        vbo.push_back(e.vertex.z);

        vbo.push_back(e.uv.x);
        vbo.push_back(e.uv.y);

        vbo.push_back(e.normal.x);
        vbo.push_back(e.normal.y);
        vbo.push_back(e.normal.z);
    }
}

int ObjParser::getAttributesPerVertex() const {
    return attributesPerVertex;
}

unsigned ObjParser::getTriangleCount() const {
    return triangleCount;
}

