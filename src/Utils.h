#pragma once

#include "pgr.h"
#include "entity/primitives/Arrow.h"

class Utils {
public:
    static void tokenize(std::string const& str, const char delim, std::vector<std::string>& out)
    {
        size_t start;
        size_t end = 0;

        while ((start = str.find_first_not_of(delim, end)) != std::string::npos) {
            end = str.find(delim, start);
            out.push_back(str.substr(start, end - start));
        }
    }

    // Debug

    static void printMat4(glm::mat4 matrix) {
    	printf("\n(%f %f %f %f)\n", matrix[0].x, matrix[0].y, matrix[0].z, matrix[0].w);
        printf("(%f %f %f %f)\n", matrix[1].x, matrix[1].y, matrix[1].z, matrix[1].w);
        printf("(%f %f %f %f)\n", matrix[2].x, matrix[2].y, matrix[2].z, matrix[2].w);
        printf("(%f %f %f %f)\n\n", matrix[3].x, matrix[3].y, matrix[3].z, matrix[3].w);
    }

	static void printVec3(glm::vec3 vec)
    {
        printf("(%f %f %f)\n", vec.x, vec.y, vec.z);
    }

    static void drawArrow(glm::vec3 vector, glm::vec3 color, PhongShader& shader, Camera& camera, glm::mat4 modelMatrix)
    {
        auto arrow = new Arrow(vector, color);
        arrow->create(&shader);
        arrow->render(shader, camera, modelMatrix);
    }

    // 2D transformation matrices

    static glm::mat3 rotate2D(float angle) {
        float s = sin(glm::radians(angle));
        float c = cos(glm::radians(angle));
        return glm::mat3(c, s, 0, -s, c, 0, 0, 0, 1);
    }

    static glm::mat3 translate2D(glm::vec2 vec)
    {
        return glm::mat3(1, 0, 0, 0, 1, 0, vec.x, vec.y, 1);
    }

    static glm::mat3 scale2D(glm::vec2 scale)
    {
        return glm::mat3(scale.x, 0, 0, 0, scale.y, 0, 0, 0, 1);
    }
};

//glm::mat4 rot = glm::mat4(1.0f);
//rot = glm::rotate(rot, glm::radians(81.0f), glm::vec3(1, 0, 0));
//rot = glm::rotate(rot, glm::radians(37.0f), glm::vec3(0, 1, 0));
//rot = glm::rotate(rot, glm::radians(7.0f), glm::vec3(0, 0, 1));
//
//float Yaw;
//float Pitch;
//float Roll;
//
//if (rot[0][0] == 1.0f) {
//    Yaw = atan2f(rot[2][0], rot[3][2]);
//    Pitch = 0;
//    Roll = 0;
//
//} else if (rot[0][0] == -1.0f) {
//    Yaw = atan2f(rot[2][0], rot[3][2]);
//    Pitch = 0;
//    Roll = 0;
//} else {
//    Yaw = atan2(-rot[0][2], rot[0][0]);
//    Pitch = asin(rot[0][1]);
//    Roll = atan2(-rot[2][1], rot[1][1]);
//}
//
//this->transform.rot = glm::vec3(glm::degrees(Yaw), glm::degrees(Pitch), glm::degrees(Roll));
