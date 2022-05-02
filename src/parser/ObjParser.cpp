#include "ObjParser.h"

#include <iostream>
#include <sstream>
#include <fstream>

#include "../Utils.h"

ObjParser::ObjParser(const char* path) : ObjParser(path, 1.0f)
{
	//Empty
}

ObjParser::ObjParser(const char* path, float uvScale)
{
    parseObj(path, uvScale);
    calculateTangents();
}

// Only parses obj files with triangle faces, so the mesh needs to be triangulated prior to export.
void ObjParser::parseObj(const char* path, float uvScale) {
    // int cwCount = 0;
    // int ccwCount = 0;

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
            float u = std::stof(words[1]) * uvScale;
            float v = std::stof(words[2]) * uvScale;
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
            vertexIndices.push_back({ vs[0], vs[1], vs[2] });
            uvIndices.push_back({ vts[0], vts[1], vts[2] });
            normalIndices.push_back({ vns[0], vns[1], vns[2] });

            // Detect winding (unused)
            // glm::vec3 a = vertices[vs[0] - 1];
            // glm::vec3 b = vertices[vs[1] - 1];
            // glm::vec3 c = vertices[vs[2] - 1];

            // glm::vec3 x = glm::normalize(b - a);
            // glm::vec3 y = glm::normalize(c - a);
            // glm::vec3 z = glm::cross(x, y);

            // glm::mat3 triangleSpaceToStandardBasis = glm::inverse(glm::mat3(x, y, z));
            // glm::vec3 normal = triangleSpaceToStandardBasis * z;
            // if (normal.z > 0.0f) {
            //	// CCW
            //	ccwCount++;
            // } else {
            //	// CW
            //	cwCount++;
            // }
        }
    }
    std::cout << "Loaded obj from file '" << path << "'" << std::endl;
    // std::cout << "CW: " << std::to_string(cwCount) << std::endl;
    // std::cout << "CCW: " << std::to_string(ccwCount) << std::endl;
}

void ObjParser::calculateTangents() {
	tangentIndices.clear();
	tangentIndices.reserve(triangleCount * 3);
	tangents.clear();
	tangents.reserve(triangleCount);

	//Go through each triangle
	for (int i = 0; i < vertexIndices.size(); i++) {
		auto v = vertexIndices[i];
		auto t = uvIndices[i];
		auto n = normalIndices[i];

		//Calculating a tangent vector from vertex positions and uv coordinates
		
		//The method is described here
		//http://www.opengl-tutorial.org/intermediate-tutorials/tutorial-13-normal-mapping/
		//and here
		//https://learnopengl.com/Advanced-Lighting/Normal-Mapping

		glm::vec3 pos1 = vertices[v[0] - 1];
		glm::vec3 pos2 = vertices[v[1] - 1];
		glm::vec3 pos3 = vertices[v[2] - 1];

		glm::vec2 uv1 = uvs[t[0] - 1];
		glm::vec2 uv2 = uvs[t[1] - 1];
		glm::vec2 uv3 = uvs[t[2] - 1];

		glm::vec3 e1 = pos2 - pos1;
		glm::vec3 e2 = pos3 - pos1;
		glm::vec2 d1 = uv2 - uv1;
		glm::vec2 d2 = uv3 - uv1;

		glm::vec3 tangent = glm::vec3(0);

		glm::mat2 dMatInv = glm::inverse(glm::mat2(d1.x, d2.x, d1.y, d2.y));
        glm::mat3x2 eMat = glm::mat3x2(e1.x, e2.x, e1.y, e2.y, e1.z, e2.z);
        glm::mat3x2 result = dMatInv * eMat;
        tangent.x = result[0][0];
        tangent.y = result[1][0];
        tangent.z = result[2][0];

		//Following code is used at learnopengl.com, might perhaps be faster (depends on glm::inverse speed)
		//float d = d1.x * d2.y - d2.x * d1.y;
		//float f = 1.0f / d;
		//tangent.x = f * (d2.y * e1.x - d1.y * e2.x);
		//tangent.y = f * (d2.y * e1.y - d1.y * e2.y);
		//tangent.z = f * (d2.y * e1.z - d1.y * e2.z);

        tangent = glm::normalize(tangent);

		tangents.push_back(tangent);
		// Assign tangent to the triangle. Same for all vertices of a triangle (only store a single index)
		tangentIndices.push_back(i);
	}
}

void ObjParser::getDrawArraysGeo(std::vector<float> &vbo)
{
	vbo.clear();
	vbo.reserve(vertexIndices.size() * 3 * 8);

	for (int i = 0; i < vertexIndices.size(); i++) {
		auto v = vertexIndices[i];
		auto u = uvIndices[i];
		auto n = normalIndices[i];
		auto t = tangentIndices[i];

		for (int k = 0; k < 3; k++) {
			glm::vec3 vertex = vertices[v[k] - 1];
			vbo.push_back(vertex.x);
			vbo.push_back(vertex.y);
			vbo.push_back(vertex.z);

			glm::vec2 uv = uvs[u[k] - 1];
			vbo.push_back(uv.x);
			vbo.push_back(uv.y);

			glm::vec3 normal = normals[n[k] - 1];
			vbo.push_back(normal.x);
			vbo.push_back(normal.y);
			vbo.push_back(normal.z);

			glm::vec3 tangent = tangents[t]; //Same for all vertices of a triangle
			vbo.push_back(tangent.x);
			vbo.push_back(tangent.y);
			vbo.push_back(tangent.z);
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
		auto u = uvIndices[i];
		auto n = normalIndices[i];
		auto t = tangentIndices[i];

		for (int k = 0; k < 3; k++) {
			ObjVertex* vertex = &vboEntries[v[k] - 1];
			ebo.push_back(v[k] - 1);
			vertex->uv = uvs[u[k] - 1];
			vertex->normal = normals[n[k] - 1];
			vertex->tangent = tangents[t]; //Same for all vertices of a triangle
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

		vbo.push_back(e.tangent.x);
		vbo.push_back(e.tangent.y);
		vbo.push_back(e.tangent.z);
	}
}

int ObjParser::getAttributesPerVertex() const {
	return attributesPerVertex;
}

unsigned ObjParser::getTriangleCount() const {
	return triangleCount;
}

