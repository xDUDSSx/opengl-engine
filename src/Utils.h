#pragma once

#include "pgr.h"

class Utils {
public:
    static glm::vec3 getRightVector(glm::mat4 &view)
    {
        return glm::normalize(glm::vec3(view[0]));
    	//return glm::vec3(view.m00(), view.m10(), view.m20()).normalize();
    }

    static glm::vec3 getUpVector(glm::mat4 &view)
    {
        return glm::normalize(glm::vec3(view[1]));
        //return glm::vec3(view.m01(), view.m11(), view.m21()).normalize();
    }

    static glm::vec3 getLookVector(glm::mat4 &view)
    {
        return glm::normalize(glm::vec3(view[2]));
        //return glm::vec3(view.m02(), view.m12(), view.m22()).normalize();
    }

    static glm::vec3 getViewPosition(glm::mat4 &view)
    {
        glm::mat4 invertedView = glm::inverse(view);
        return glm::vec3(invertedView[3][0], invertedView[3][1], invertedView[3][2]);
        //glm::mat4 invertedView = new glm::mat4(view).invertAffine();
        //return new glm::vec3(invertedView.m30(), invertedView.m31(), invertedView.m32());
    }

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

    static void tokenize(std::string const& str, const char delim, std::vector<std::string>& out) {
	    size_t start;
	    size_t end = 0;

	    while ((start = str.find_first_not_of(delim, end)) != std::string::npos) {
		    end = str.find(delim, start);
		    out.push_back(str.substr(start, end - start));
	    }
    }
};
